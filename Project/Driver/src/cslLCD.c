#include "cslLCD.h"

//LCD_FSMC_D0   D14
//LCD_FSMC_D1   D15
//LCD_FSMC_D2   D0
//LCD_FSMC_D3   D1
//LCD_FSMC_D4   E7
//LCD_FSMC_D5   E8
//LCD_FSMC_D6   E9
//LCD_FSMC_D7   E10
//LCD_FSMC_D8   E11
//LCD_FSMC_D9   E12
//LCD_FSMC_D10  E13
//LCD_FSMC_D11  E14
//LCD_FSMC_D12  E15
//LCD_FSMC_D13  D8
//LCD_FSMC_D14  D9
//LCD_FSMC_D15  D10
//LCD_RD        D4
//LCD_WR        D5
//LCD_RS        D11
//LCD_CS        D7

static void Delay(unsigned int time)                                                                       
{
	volatile unsigned int i;
	
	while(time--)
	{
		for(i=0;i<1000;i++);
	}
}

void CslLCD_lowlevel_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
#if BOARD_TYPE == RELEASE_BOARD_V1
	RCC_APB2PeriphClockCmd(GPIO2RCC(_LCD_BLK_GPIO), ENABLE);
#endif
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_4  | GPIO_Pin_5  |
                             GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
	                           GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
                             GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
	                           GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 1;
	FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 1;
	FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 2;
	FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 1;
	FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 1;
	
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
	
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}

void CslLCD_BLK(unsigned char NewStatus)
{
#if BOARD_TYPE == RELEASE_BOARD_V1
	if(NewStatus)
	{
		GPIO_SetBits(_LCD_BLK_GPIO, _LCD_BLK_PIN);
	}
	else
	{
		GPIO_ResetBits(_LCD_BLK_GPIO, _LCD_BLK_PIN);
	}
#endif
}

void CslLCD_Init(void)
{
	CslLCD_lowlevel_Init();
	CSL_LCD_WriteComm(0x01);
	Delay(1200);
	CSL_LCD_WriteComm(0xE0);
	CSL_LCD_WriteData(0x00);
	CSL_LCD_WriteData(0x07);
	CSL_LCD_WriteData(0x0f);
	CSL_LCD_WriteData(0x0D);
	CSL_LCD_WriteData(0x1B);
	CSL_LCD_WriteData(0x0A);
	CSL_LCD_WriteData(0x3c);
	CSL_LCD_WriteData(0x78);
	CSL_LCD_WriteData(0x4A);
	CSL_LCD_WriteData(0x07);
	CSL_LCD_WriteData(0x0E);
	CSL_LCD_WriteData(0x09);
	CSL_LCD_WriteData(0x1B);
	CSL_LCD_WriteData(0x1e);
	CSL_LCD_WriteData(0x0f); 
	
	CSL_LCD_WriteComm(0xE1);
	CSL_LCD_WriteData(0x00);
	CSL_LCD_WriteData(0x22);
	CSL_LCD_WriteData(0x24);
	CSL_LCD_WriteData(0x06);
	CSL_LCD_WriteData(0x12);
	CSL_LCD_WriteData(0x07);
	CSL_LCD_WriteData(0x36);
	CSL_LCD_WriteData(0x47);
	CSL_LCD_WriteData(0x47);
	CSL_LCD_WriteData(0x06);
	CSL_LCD_WriteData(0x0a);
	CSL_LCD_WriteData(0x07);
	CSL_LCD_WriteData(0x30);
	CSL_LCD_WriteData(0x37);
	CSL_LCD_WriteData(0x0f);
	
	CSL_LCD_WriteComm(0xC0);
	CSL_LCD_WriteData(0x10);
	CSL_LCD_WriteData(0x10);
	
	CSL_LCD_WriteComm(0xC1);
	CSL_LCD_WriteData(0x41);
	
	CSL_LCD_WriteComm(0xC5);
	CSL_LCD_WriteData(0x00);
	CSL_LCD_WriteData(0x22);
	CSL_LCD_WriteData(0x80);
	
	CSL_LCD_WriteComm(0x36);
	//CSL_LCD_WriteData(0x68);
	//CSL_LCD_WriteData(0x48);
	CSL_LCD_WriteData(0x28);
	
	CSL_LCD_WriteComm(0x3A);//Interface Mode Control
	CSL_LCD_WriteData(0x55);
	
	CSL_LCD_WriteComm(0xB0);//Interface Mode Control  
	CSL_LCD_WriteData(0x00);
	CSL_LCD_WriteComm(0xB1);//Frame rate 70HZ  
	CSL_LCD_WriteData(0xB0);
	CSL_LCD_WriteData(0x11);
	CSL_LCD_WriteComm(0xB4);
	CSL_LCD_WriteData(0x02);  
	CSL_LCD_WriteComm(0xB6);//RGB/MCU Interface Control
	CSL_LCD_WriteData(0x02);
	CSL_LCD_WriteData(0x02);
	
	CSL_LCD_WriteComm(0xB7);
	CSL_LCD_WriteData(0xC6);
	
	//WriteComm(0xBE);
	//WriteData(0x00);
	//WriteData(0x04);
	
	CSL_LCD_WriteComm(0xE9); 
	CSL_LCD_WriteData(0x00);

	CSL_LCD_WriteComm(0xF7);
	CSL_LCD_WriteData(0xA9);
	CSL_LCD_WriteData(0x51);
	CSL_LCD_WriteData(0x2C); 
	CSL_LCD_WriteData(0x82);

	CSL_LCD_WriteComm(0x11);
	Delay(120);
	CSL_LCD_WriteComm(0x29);
	
	CslLCD_BLK(1);
}

void BlockWrite(unsigned int Xstart, unsigned int Xend, unsigned int Ystart, unsigned int Yend)
{
	CSL_LCD_WriteComm(0x2a);
	CSL_LCD_WriteData(Xstart>>8);
	CSL_LCD_WriteData(Xstart&0xff);
	CSL_LCD_WriteData(Xend>>8);
	CSL_LCD_WriteData(Xend&0xff);

	CSL_LCD_WriteComm(0x2b);
	CSL_LCD_WriteData(Ystart>>8);
	CSL_LCD_WriteData(Ystart&0xff);
	CSL_LCD_WriteData(Yend>>8);
	CSL_LCD_WriteData(Yend&0xff);

	CSL_LCD_WriteComm(0x2c);
}

void SetPixel(unsigned int x,unsigned int y, unsigned int color)
{
	BlockWrite(x,x+1,y,y+1);
	CSL_LCD_WriteData(color & 0xFFFF);
}

unsigned int GetPixel(unsigned int x, unsigned int y)
{
	return 0;
}

void CslLCD_WR_REG(uint16_t Reg)
{
	CSL_LCD_WriteComm(Reg);
}

void CslLCD_WR_DATA(uint16_t Data)
{
	CSL_LCD_WriteData(Data);
}

void CslLCD_MRD_DATA(uint16_t* pData, int Count)
{
	volatile uint16_t dummy;
	uint16_t read1,read2,read3;
	uint16_t r1,g1,b1,r2,g2,b2;
	
	dummy = CSL_LCD_RAM;
	while(Count>1)
	{
		read1 = CSL_LCD_RAM;
		read2 = CSL_LCD_RAM;
		read3 = CSL_LCD_RAM;
		r1 = read1 >> 11;
		g1 = read1 >> 2 & 0x3F;
		b1 = read2 >> 11;
		r2 = read2 >> 3 & 0x1F;
		g2 = read3 >> 10;
		b2 = read3 >> 3 & 0x1F;
		*pData++ = (r1<<11) + (g1<<5) + b1;
		*pData++ = (r2<<11) + (g2<<5) + b2;
		Count-=2;
	}
	if(Count)
	{
		read1 = CSL_LCD_RAM;
		read2 = CSL_LCD_RAM;
		r1 = read1 >> 11;
		g1 = read1 >> 2 & 0x3F;
		b1 = read2 >> 11;
		*pData++ = (r1<<11) + (g1<<5) + b1;
	}
}

void CslLCD_MWR_DATA(uint16_t* pData, int Count)
{
	while(Count--)
		CSL_LCD_WriteData(*pData++);
}

void CslLCD_Clear(uint16_t BackColor)
{
	uint32_t i;
	
	BlockWrite(0, 480, 0, 320);
	for(i=0;i<480*320;i++)
	{
		CSL_LCD_WriteData(BackColor);
	}
}

void CslLCD_FillRect(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t Color)
{
	uint32_t i;
	
	BlockWrite(xStart, xEnd, yStart, yEnd);
	for(i=0;i<(xEnd-xStart+2)*(yEnd-yStart+2);i++)
	{
		CSL_LCD_WriteData(Color);
	}
}
