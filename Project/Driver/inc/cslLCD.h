#ifndef __CSL_LCD_H__
#define __CSL_LCD_H__

#include "stm32f10x.h"


#define LCD_REG  *(volatile u16*)(0x60000000)
#define LCD_RAM  *(volatile u16*)(0x60020000)

#define WriteComm(x)  LCD_REG = x
#define WriteData(x)  LCD_RAM = x

extern void CslLCD_Init(void);
extern void PutPixel(unsigned int x,unsigned int y,unsigned int color);
extern void CslLCD_Clear(uint16_t BackColor);

#endif
