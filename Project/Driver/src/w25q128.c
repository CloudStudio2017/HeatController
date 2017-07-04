#include "w25q128.h"
#include "stm32f10x.h"

#define flash_CMD_WREN   0x06    //Write Enable
#define flash_CMD_READ   0x03    //Read Memory
#define flash_CMD_WRITE  0x02    //Write Memory
#define flash_CMD_RDSR   0x05    //Read Status Register
#define flash_CMD_WRSR   0x01    //Write Status Register
#define flash_CMD_RDID   0x9F    ///Read ID
#define flash_CMD_SE     0x20    //Sector Erase
#define flash_CMD_BE     0xC7    //Bulk Erase

#define flash_WIP_FLAG   0x01    //Write In Progress Flag

#define flash_DUMMY_BYTE 0xA5


#define flash_PAGESIZE   0x100   //256Bytes per page
#define flash_SECTORSIZE 0x1000  //4KB a sector

#define flash_SendByte    flash_spi_SendByte
#define flash_ReadByte    flash_spi_ReadByte
/****************Flash low level function***************/
//CS A04
//CLK A05
//DO A06
//DI A07
//WP B00

static inline void flash_CS_HIGH(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}

static inline void flash_CS_LOW(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}

static inline void flash_WP_HIGH(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

static inline void flash_WP_LOW(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}

static void flash_spi_LowlevelInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//CLK
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//MOSI
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//MISO
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//CS
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//WP
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}
static void flash_spi_Init(void)
{
	SPI_InitTypeDef SPI_InitStruct;
	
	flash_spi_LowlevelInit();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	flash_CS_HIGH();
	
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStruct);
	SPI_Cmd(SPI1, ENABLE);
}

static uint8_t flash_spi_SendByte(uint8_t Data)
{
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, Data);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	
	return SPI_I2S_ReceiveData(SPI1);
}

static inline uint8_t flash_spi_ReadByte(void)
{
	return flash_spi_SendByte(flash_DUMMY_BYTE);
}

static uint16_t flash_spi_SendHalfWord(uint16_t Data)
{
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, Data);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	
	return SPI_I2S_ReceiveData(SPI1);
}

void flash_WriteEnable(void)
{
	flash_CS_LOW();
	
	flash_SendByte(flash_CMD_WREN);
	
	flash_CS_HIGH();
}

void flash_WaitForWriteEnd(void)
{
	uint8_t flashstatus = 0;
	
	flash_CS_LOW();
	
	flash_SendByte(flash_CMD_RDSR);
	do
	{
		flashstatus = flash_ReadByte();
	}while((flashstatus & flash_WIP_FLAG) == SET);
	
	flash_CS_HIGH();
}

void flash_DeInit(void)
{
	//
}

void flash_Init(void)
{
	flash_spi_Init();
	
	flash_WP_HIGH();
}

void flash_EraseSector(uint32_t SectorAddr)
{
	flash_WriteEnable();
	flash_CS_LOW();
	
	flash_SendByte(flash_CMD_SE);
	flash_SendByte((SectorAddr & 0xFF0000) >> 16);
  flash_SendByte((SectorAddr & 0xFF00) >> 8);
  flash_SendByte(SectorAddr & 0xFF);
	
	flash_CS_HIGH();
	flash_WaitForWriteEnd();
}

void flash_EraseBulk(void)
{
	flash_WriteEnable();
	flash_CS_LOW();
	
	flash_SendByte(flash_CMD_BE);
	
	flash_CS_HIGH();
	flash_WaitForWriteEnd();
}

void flash_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
	flash_WriteEnable();
	flash_CS_LOW();
	
	flash_SendByte(flash_CMD_WRITE);
	flash_SendByte((WriteAddr & 0xFF0000) >> 16);
	flash_SendByte((WriteAddr & 0xFF00) >> 8);
  flash_SendByte(WriteAddr & 0xFF);
	
	while(NumByteToWrite--)
	{
		flash_SendByte(*pBuffer++);
	}
	
	flash_CS_HIGH();
	flash_WaitForWriteEnd();
}

uint32_t flash_ReadID(void)
{
	uint8_t tmpdata[3];
	uint8_t i;
	
	flash_CS_LOW();
	
	flash_SendByte(flash_CMD_RDID);
	for(i=0;i<3;i++)
	{
		tmpdata[i] = flash_ReadByte();
	}
	
	flash_CS_HIGH();
	
	return tmpdata[0] * 65536 + tmpdata[1] * 256 + tmpdata[2];
}

void flash_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
	flash_CS_LOW();
	
	flash_SendByte(flash_CMD_READ);
	flash_SendByte((ReadAddr & 0xFF0000) >> 16);
	flash_SendByte((ReadAddr & 0xFF00) >> 8);
	flash_SendByte(ReadAddr & 0xFF);
	while(NumByteToRead--)
	{
		*pBuffer++ = flash_ReadByte();
	}
	
	flash_CS_HIGH();
}

void flash_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
	uint32_t Count;
	uint32_t Addr;
	
	Addr = WriteAddr / flash_PAGESIZE * flash_PAGESIZE;
	if(Addr != WriteAddr)
	{
		Count = flash_PAGESIZE - (WriteAddr - Addr);
		if(Count >= NumByteToWrite)
		{
			Count = NumByteToWrite;
		}
		flash_WritePage(pBuffer, WriteAddr, Count);
		pBuffer += Count;
		WriteAddr += Count;
		NumByteToWrite -= Count;
	}
	while(NumByteToWrite >= flash_PAGESIZE)
	{
		flash_WritePage(pBuffer, WriteAddr, flash_PAGESIZE);
		pBuffer += flash_PAGESIZE;
		WriteAddr += flash_PAGESIZE;
		NumByteToWrite -= flash_PAGESIZE;
	}
	if(NumByteToWrite)
	{
		flash_WritePage(pBuffer, WriteAddr, NumByteToWrite);
	}
	
	return;
}

void flash_Erase(uint32_t EraseAddr, uint32_t NumByteToErase)
{
	uint32_t SectorBegin, SectorEnd;
	
	SectorBegin = EraseAddr / flash_SECTORSIZE * flash_SECTORSIZE;
	SectorEnd   = (EraseAddr + NumByteToErase - 1) / flash_SECTORSIZE * flash_SECTORSIZE;
	
	while(SectorBegin <= SectorEnd)
	{
		flash_EraseSector(SectorBegin);
		SectorBegin += flash_SECTORSIZE;
	}
}


