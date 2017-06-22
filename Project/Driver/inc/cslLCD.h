#ifndef __CSL_LCD_H__
#define __CSL_LCD_H__

#include "stm32f10x.h"


#define CSL_LCD_REG  *(volatile u16*)(0x60000000)
#define CSL_LCD_RAM  *(volatile u16*)(0x60020000)

#define CSL_LCD_WriteComm(x)  CSL_LCD_REG = x
#define CSL_LCD_WriteData(x)  CSL_LCD_RAM = x

extern void CslLCD_Init(void);
extern void PutPixel(unsigned int x,unsigned int y,unsigned int color);
extern void CslLCD_Clear(uint16_t BackColor);
extern void CslLCD_FillRect(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd, uint16_t Color);

extern void CslLCD_WR_REG(uint16_t Reg);
extern void CslLCD_WR_DATA(uint16_t Data);
extern void CslLCD_MRD_DATA(uint16_t* Reg, int Count);
extern void CslLCD_MWR_DATA(uint16_t* Data, int Count);

#endif
