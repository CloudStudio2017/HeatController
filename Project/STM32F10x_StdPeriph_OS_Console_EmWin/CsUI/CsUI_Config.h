#ifndef __CSUI_CONFIG_H__
#define __CSUI_CONFIG_H__

#include "CslLCD.h"


#define CsUI_LowDeviceInit()                               CslLCD_Init()
#define CsUI_SetPixel(x, y, Color)                         SetPixel(x, y, Color)
#define CsUI_FillRect(Left, Top, Right, Bottom, Color)     CslLCD_FillRect(Left, Top, Right, Bottom, Color)
#define CsUI_BlockBegin(Left, Top, Right, Bottom)          BlockWrite(Left, Right, Top, Bottom)
#define CsUI_BlockEnd()
#define CsUI_BlockWriteData(Color)                         CSL_LCD_WriteData(Color)




#endif

