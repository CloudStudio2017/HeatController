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

void CslLCD_Init(void)
{
	CslLCD_lowlevel_Init();
	WriteComm(0x01);
	Delay(1200);
	WriteComm(0xE0);
	WriteData(0x00);
	WriteData(0x07);
	WriteData(0x0f);
	WriteData(0x0D);
	WriteData(0x1B);
	WriteData(0x0A);
	WriteData(0x3c);
	WriteData(0x78);
	WriteData(0x4A);
	WriteData(0x07);
	WriteData(0x0E);
	WriteData(0x09);
	WriteData(0x1B);
	WriteData(0x1e);
	WriteData(0x0f); 
	
	WriteComm(0xE1);
	WriteData(0x00);
	WriteData(0x22);
	WriteData(0x24);
	WriteData(0x06);
	WriteData(0x12);
	WriteData(0x07);
	WriteData(0x36);
	WriteData(0x47);
	WriteData(0x47);
	WriteData(0x06);
	WriteData(0x0a);
	WriteData(0x07);
	WriteData(0x30);
	WriteData(0x37);
	WriteData(0x0f);
	
	WriteComm(0xC0);
	WriteData(0x10);
	WriteData(0x10);
	
	WriteComm(0xC1);
	WriteData(0x41);
	
	WriteComm(0xC5);
	WriteData(0x00);
	WriteData(0x22);
	WriteData(0x80);
	
	WriteComm(0x36);
	WriteData(0x68);
	//WriteData(0x48);
	
	WriteComm(0x3A);//Interface Mode Control
	WriteData(0x55);
	
	WriteComm(0xB0);//Interface Mode Control  
	WriteData(0x00);
	WriteComm(0xB1);//Frame rate 70HZ  
	WriteData(0xB0);
	WriteData(0x11);
	WriteComm(0xB4);
	WriteData(0x02);  
	WriteComm(0xB6);//RGB/MCU Interface Control
	WriteData(0x02);
	WriteData(0x02);
	
	WriteComm(0xB7);
	WriteData(0xC6);
	
	//WriteComm(0xBE);
	//WriteData(0x00);
	//WriteData(0x04);
	
	WriteComm(0xE9); 
	WriteData(0x00);

	WriteComm(0xF7);
	WriteData(0xA9);
	WriteData(0x51);
	WriteData(0x2C); 
	WriteData(0x82);

	WriteComm(0x11);
	Delay(120);
	WriteComm(0x29);
}

void BlockWrite(unsigned int Xstart,unsigned int Xend,unsigned int Ystart,unsigned int Yend)
{
	WriteComm(0x2a);
	WriteData(Xstart>>8);
	WriteData(Xstart&0xff);
	WriteData(Xend>>8);
	WriteData(Xend&0xff);

	WriteComm(0x2b);
	WriteData(Ystart>>8);
	WriteData(Ystart&0xff);
	WriteData(Yend>>8);
	WriteData(Yend&0xff);

	WriteComm(0x2c);
}

void PutPixel(unsigned int x,unsigned int y,unsigned int color)
{
	BlockWrite(x,x+1,y,y+1);
	WriteData(color & 0xFFFF);
}

void CslLCD_Clear(uint16_t BackColor)
{
	uint32_t i;
	
	BlockWrite(0, 480, 0, 320);
	for(i=0;i<480*320;i++)
	{
		WriteData(BackColor);
	}
}
