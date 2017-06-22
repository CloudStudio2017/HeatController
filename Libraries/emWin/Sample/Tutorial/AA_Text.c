/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.32 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The software has been licensed to  ARM LIMITED whose registered office
is situated at  110 Fulbourn Road,  Cambridge CB1 9NJ,  England solely
for  the  purposes  of  creating  libraries  for  ARM7, ARM9, Cortex-M
series,  and   Cortex-R4   processor-based  devices,  sublicensed  and
distributed as part of the  MDK-ARM  Professional  under the terms and
conditions  of  the   End  User  License  supplied  with  the  MDK-ARM
Professional. 
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information

Licensor:                 SEGGER Software GmbH
Licensed to:              ARM Ltd, 110 Fulbourn Road, CB1 9NJ Cambridge, UK
Licensed SEGGER software: emWin
License number:           GUI-00181
License model:            LES-SLA-20007, Agreement, effective since October 1st 2011 
Licensed product:         MDK-ARM Professional
Licensed platform:        ARM7/9, Cortex-M/R4
Licensed number of seats: -
----------------------------------------------------------------------
File        : AA_Text.c
Purpose     : Shows text with different antialiasing qualities
Requirements: WindowManager - ( )
              MemoryDevices - ( )
              AntiAliasing  - (x)
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )
----------------------------------------------------------------------
*/

#include <stddef.h>
#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 10)

/*********************************************************************
*
*       Static const data
*
**********************************************************************
*/
/*********************************************************************
*
*       _bmSeggerLogo_50x25
*/
static GUI_CONST_STORAGE GUI_COLOR _ColorsSeggerLogo_50x25[] = {
     0xFFFFFF,0x292929,0xCACACA,0x96433D
    ,0xB0726E,0x5F5F5F,0x949494,0x9D4F49
    ,0xF8F3F3,0xD7D7D7,0x363636,0xA1A1A1
    ,0xCBA19E,0xD1ADAA,0xDEC4C2,0xF2E8E7
    ,0x515151,0x6C6C6C,0xB77E7A,0xAFAFAF
    ,0xBCBCBC,0xEBDCDB,0xE4E4E4,0xF2F2F2
    ,0x878787,0xC49592,0x000000,0x444444
    ,0x797979,0xA35B55,0xAA6661,0xE5D0CF
    ,0xBD8A86,0xD8B9B6
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalSeggerLogo_50x25 = {
  34,	// number of entries
  0, 	// No transparency
  &_ColorsSeggerLogo_50x25[0]
};

static GUI_CONST_STORAGE unsigned char _acSeggerLogo_50x25[] = {
  0x1A, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1A,
  0x01, 0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x06, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x1F, 0x12, 0x08, 0x00, 0x00, 0x20, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x0D, 0x03, 0x12, 0x00, 0x00, 0x07, 0x03, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x1E, 0x03, 0x0D, 0x00, 0x0E, 0x03, 0x07, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x0F, 0x07, 0x03, 0x15, 0x00, 0x19, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x0E, 0x03, 0x1D, 0x08, 0x00, 0x04, 0x03, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x0E, 0x08, 0x00, 0x19, 0x03, 0x12, 0x00, 0x08, 0x07, 0x03, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x0C, 0x12, 0x00, 0x00, 0x1E, 0x03, 0x0D, 0x00, 0x1F, 0x03, 0x07, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x0C, 0x03, 0x0D, 0x00, 0x0F, 0x07, 0x03, 0x15, 0x00, 0x0D, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
        0x03, 0x03, 0x03, 0x03, 0x07, 0x0F, 0x02, 0x01,
  0x01, 0x02, 0x0C, 0x03, 0x03, 0x15, 0x00, 0x0E, 0x03, 0x1D, 0x08, 0x00, 0x19, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x0F, 0x02, 0x01,
  0x01, 0x02, 0x0C, 0x03, 0x03, 0x04, 0x00, 0x00, 0x04, 0x03, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x0C, 0x03, 0x03, 0x15, 0x00, 0x0E, 0x03, 0x1D, 0x08, 0x00, 0x19, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
        0x04, 0x04, 0x04, 0x04, 0x04, 0x0F, 0x02, 0x01,
  0x01, 0x02, 0x0C, 0x03, 0x0D, 0x00, 0x0F, 0x07, 0x03, 0x15, 0x00, 0x0D, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
        0x03, 0x03, 0x03, 0x03, 0x07, 0x0F, 0x02, 0x01,
  0x01, 0x02, 0x0C, 0x12, 0x00, 0x00, 0x1E, 0x03, 0x0D, 0x00, 0x1F, 0x03, 0x07, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x0E, 0x08, 0x00, 0x19, 0x03, 0x12, 0x00, 0x08, 0x07, 0x03, 0x0E, 0x00, 0x14, 0x06, 0x13, 0x17, 0x00, 0x02, 0x02, 0x02, 0x02, 0x17, 0x00, 0x14, 0x06, 0x13, 0x17, 0x00, 0x00, 0x09, 0x06, 0x0B, 0x16, 0x00, 0x16, 0x02, 0x02, 0x02, 0x09, 0x17, 
        0x02, 0x02, 0x02, 0x09, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x0E, 0x03, 0x1D, 0x08, 0x00, 0x04, 0x03, 0x0C, 0x00, 0x18, 0x0A, 0x1C, 0x0A, 0x11, 0x02, 0x01, 0x10, 0x05, 0x05, 0x09, 0x11, 0x01, 0x05, 0x0A, 0x0A, 0x00, 0x18, 0x01, 0x05, 0x1B, 0x01, 0x16, 0x06, 0x0A, 0x05, 0x05, 0x11, 0x0B, 
        0x01, 0x05, 0x10, 0x01, 0x13, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x0F, 0x07, 0x03, 0x15, 0x00, 0x19, 0x03, 0x04, 0x00, 0x00, 0x11, 0x0A, 0x18, 0x0B, 0x02, 0x02, 0x01, 0x1C, 0x06, 0x0B, 0x09, 0x01, 0x0B, 0x00, 0x16, 0x0B, 0x00, 0x01, 0x1C, 0x00, 0x17, 0x06, 0x17, 0x06, 0x1B, 0x06, 0x06, 0x02, 0x06, 
        0x01, 0x02, 0x14, 0x01, 0x0B, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x1E, 0x03, 0x0D, 0x00, 0x0E, 0x03, 0x07, 0x08, 0x00, 0x00, 0x17, 0x18, 0x05, 0x01, 0x0A, 0x02, 0x01, 0x10, 0x05, 0x1C, 0x02, 0x01, 0x14, 0x13, 0x01, 0x01, 0x02, 0x01, 0x06, 0x09, 0x01, 0x01, 0x06, 0x06, 0x0A, 0x05, 0x05, 0x13, 0x06, 
        0x01, 0x01, 0x01, 0x01, 0x09, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x0D, 0x03, 0x12, 0x00, 0x00, 0x07, 0x03, 0x15, 0x00, 0x00, 0x00, 0x11, 0x10, 0x02, 0x18, 0x01, 0x13, 0x01, 0x0B, 0x02, 0x02, 0x09, 0x0A, 0x10, 0x02, 0x18, 0x01, 0x02, 0x05, 0x0A, 0x14, 0x0B, 0x01, 0x06, 0x06, 0x10, 0x02, 0x02, 0x02, 0x06, 
        0x01, 0x00, 0x16, 0x01, 0x14, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x1F, 0x12, 0x08, 0x00, 0x00, 0x20, 0x21, 0x00, 0x00, 0x00, 0x00, 0x09, 0x11, 0x01, 0x1B, 0x06, 0x16, 0x05, 0x05, 0x05, 0x05, 0x14, 0x09, 0x05, 0x01, 0x10, 0x10, 0x09, 0x16, 0x11, 0x01, 0x1B, 0x11, 0x0B, 0x13, 0x05, 0x05, 0x05, 0x05, 0x14, 
        0x05, 0x00, 0x00, 0x05, 0x13, 0x00, 0x02, 0x01,
  0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01,
  0x01, 0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x06, 0x01,
  0x1A, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1A
};

static GUI_CONST_STORAGE GUI_BITMAP _bmSeggerLogo_50x25 = {
  50, // XSize
  25, // YSize
  50, // BytesPerLine
  8, // BitsPerPixel
  _acSeggerLogo_50x25,  // Pointer to picture data (indices)
  &_PalSeggerLogo_50x25  // Pointer to palette
};

/*********************************************************************
*
*       _FontAA4_32
*/
static GUI_CONST_STORAGE unsigned char acGUI_FontAA4_32_0041[180] = { // code 0041, LATIN CAPITAL LETTER A
  0x00, 0x00, 0x00, 0x3F, 0xFF, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x8F, 0xFF, 0x70, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xEF, 0xFF, 0xD0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x04, 0xFF, 0xFF, 0xF3, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x09, 0xFF, 0xEF, 0xF8, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0E, 0xFF, 0x6F, 0xFD, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x5F, 0xFD, 0x0D, 0xFF, 0x40, 0x00, 0x00,
  0x00, 0x00, 0xAF, 0xF7, 0x07, 0xFF, 0x90, 0x00, 0x00,
  0x00, 0x01, 0xEF, 0xF2, 0x02, 0xFF, 0xE0, 0x00, 0x00,
  0x00, 0x05, 0xFF, 0xC0, 0x00, 0xCF, 0xF5, 0x00, 0x00,
  0x00, 0x0A, 0xFF, 0x70, 0x00, 0x7F, 0xFA, 0x00, 0x00,
  0x00, 0x1F, 0xFF, 0x20, 0x00, 0x1F, 0xFF, 0x10, 0x00,
  0x00, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x50, 0x00,
  0x00, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB0, 0x00,
  0x02, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF1, 0x00,
  0x07, 0xFF, 0xB0, 0x00, 0x00, 0x00, 0xAF, 0xF6, 0x00,
  0x0B, 0xFF, 0x50, 0x00, 0x00, 0x00, 0x5F, 0xFB, 0x00,
  0x2F, 0xFF, 0x10, 0x00, 0x00, 0x00, 0x0E, 0xFF, 0x20,
  0x7F, 0xFA, 0x00, 0x00, 0x00, 0x00, 0x0A, 0xFF, 0x70,
  0xCF, 0xF5, 0x00, 0x00, 0x00, 0x00, 0x04, 0xFF, 0xC0
};

static GUI_CONST_STORAGE unsigned char acGUI_FontAA4_32_0042[140] = { // code 0042, LATIN CAPITAL LETTER B
  0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xB6, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x90,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5,
  0xFF, 0xF0, 0x00, 0x00, 0x13, 0xCF, 0xFC,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x2F, 0xFF,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0xFF,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x3F, 0xFC,
  0xFF, 0xF0, 0x00, 0x00, 0x14, 0xDF, 0xF7,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x50,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF2,
  0xFF, 0xF0, 0x00, 0x00, 0x26, 0xEF, 0xF9,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x5F, 0xFD,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0xFF,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0xFF,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x4F, 0xFD,
  0xFF, 0xF0, 0x00, 0x00, 0x14, 0xEF, 0xFA,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x60,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xB4, 0x00
};

static GUI_CONST_STORAGE unsigned char acGUI_FontAA4_32_0043[140] = { // code 0043, LATIN CAPITAL LETTER C
  0x00, 0x00, 0x5B, 0xEF, 0xEB, 0x60, 0x00,
  0x00, 0x1B, 0xFF, 0xFF, 0xFF, 0xFC, 0x10,
  0x00, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0,
  0x07, 0xFF, 0xF7, 0x10, 0x3A, 0xFF, 0xF7,
  0x0E, 0xFF, 0x50, 0x00, 0x00, 0xAF, 0xFD,
  0x5F, 0xFB, 0x00, 0x00, 0x00, 0x2D, 0x83,
  0x9F, 0xF6, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xCF, 0xF3, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xEF, 0xF1, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xEF, 0xF1, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xDF, 0xF3, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xAF, 0xF6, 0x00, 0x00, 0x00, 0x2D, 0x83,
  0x6F, 0xFB, 0x00, 0x00, 0x00, 0x7F, 0xFD,
  0x1F, 0xFF, 0x40, 0x00, 0x01, 0xEF, 0xF8,
  0x08, 0xFF, 0xE7, 0x10, 0x4D, 0xFF, 0xF2,
  0x00, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80,
  0x00, 0x1C, 0xFF, 0xFF, 0xFF, 0xF9, 0x00,
  0x00, 0x00, 0x6B, 0xEF, 0xEA, 0x40, 0x00
};

static GUI_CONST_STORAGE GUI_CHARINFO_EXT GUI_FontAA4_32_CharInfo[3] = {
   {  17,  20,   0,   6,  17, acGUI_FontAA4_32_0041 } // code 0041, LATIN CAPITAL LETTER A
  ,{  14,  20,   2,   6,  17, acGUI_FontAA4_32_0042 } // code 0042, LATIN CAPITAL LETTER B
  ,{  14,  20,   1,   6,  17, acGUI_FontAA4_32_0043 } // code 0043, LATIN CAPITAL LETTER C
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontAA4_32_Prop1 = {
   0x0041 // first character
  ,0x0043 // last character 
  ,&GUI_FontAA4_32_CharInfo[  0] // address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP_EXT *)0 // pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT _FontAA4_32 = {
   GUI_FONTTYPE_PROP_AA4_EXT // type of font   
  ,33 // height of font 
  ,33 // space of font y
  ,1 // magnification x
  ,1 // magnification y
  ,{&GUI_FontAA4_32_Prop1}
  ,33 // Baseline
  ,15 // Height of lowercase characters
  ,20 // Height of capital characters
};

/*********************************************************************
*
*       _FontAA2_32
*/
static GUI_CONST_STORAGE unsigned char acGUI_FontAA2_32_0041[100] = { // code 0041, LATIN CAPITAL LETTER A
  0x00, 0x03, 0xF0, 0x00, 0x00,
  0x00, 0x0B, 0xF4, 0x00, 0x00,
  0x00, 0x0F, 0xFC, 0x00, 0x00,
  0x00, 0x1F, 0xFC, 0x00, 0x00,
  0x00, 0x2F, 0xFE, 0x00, 0x00,
  0x00, 0x3F, 0x7F, 0x00, 0x00,
  0x00, 0x7F, 0x3F, 0x40, 0x00,
  0x00, 0xBD, 0x1F, 0x80, 0x00,
  0x00, 0xFC, 0x0F, 0xC0, 0x00,
  0x01, 0xFC, 0x0F, 0xD0, 0x00,
  0x02, 0xF4, 0x07, 0xE0, 0x00,
  0x03, 0xF0, 0x03, 0xF0, 0x00,
  0x07, 0xFF, 0xFF, 0xF4, 0x00,
  0x0B, 0xFF, 0xFF, 0xF8, 0x00,
  0x0F, 0xFF, 0xFF, 0xFC, 0x00,
  0x1F, 0x80, 0x00, 0xBD, 0x00,
  0x3F, 0x40, 0x00, 0x7F, 0x00,
  0x3F, 0x00, 0x00, 0x3F, 0x00,
  0x7E, 0x00, 0x00, 0x2F, 0x40,
  0xFD, 0x00, 0x00, 0x1F, 0xC0
};

static GUI_CONST_STORAGE unsigned char acGUI_FontAA2_32_0042[ 80] = { // code 0042, LATIN CAPITAL LETTER B
  0xFF, 0xFF, 0xF9, 0x00,
  0xFF, 0xFF, 0xFF, 0x80,
  0xFF, 0xFF, 0xFF, 0xD0,
  0xFC, 0x00, 0x0F, 0xF0,
  0xFC, 0x00, 0x03, 0xF0,
  0xFC, 0x00, 0x03, 0xF0,
  0xFC, 0x00, 0x03, 0xF0,
  0xFC, 0x00, 0x1F, 0xD0,
  0xFF, 0xFF, 0xFF, 0xC0,
  0xFF, 0xFF, 0xFF, 0x40,
  0xFF, 0xFF, 0xFF, 0xC0,
  0xFC, 0x00, 0x1F, 0xE0,
  0xFC, 0x00, 0x07, 0xF0,
  0xFC, 0x00, 0x03, 0xF0,
  0xFC, 0x00, 0x03, 0xF0,
  0xFC, 0x00, 0x07, 0xF0,
  0xFC, 0x00, 0x1F, 0xE0,
  0xFF, 0xFF, 0xFF, 0xC0,
  0xFF, 0xFF, 0xFF, 0x40,
  0xFF, 0xFF, 0xF9, 0x00
};

static GUI_CONST_STORAGE unsigned char acGUI_FontAA2_32_0043[ 80] = { // code 0043, LATIN CAPITAL LETTER C
  0x00, 0x6F, 0xE4, 0x00,
  0x02, 0xFF, 0xFF, 0x00,
  0x0F, 0xFF, 0xFF, 0xC0,
  0x1F, 0xD0, 0x2F, 0xD0,
  0x3F, 0x40, 0x0B, 0xF0,
  0x7E, 0x00, 0x03, 0x80,
  0xBD, 0x00, 0x00, 0x00,
  0xFC, 0x00, 0x00, 0x00,
  0xFC, 0x00, 0x00, 0x00,
  0xFC, 0x00, 0x00, 0x00,
  0xFC, 0x00, 0x00, 0x00,
  0xFC, 0x00, 0x00, 0x00,
  0xFC, 0x00, 0x00, 0x00,
  0xBD, 0x00, 0x03, 0x80,
  0x7E, 0x00, 0x07, 0xF0,
  0x3F, 0x40, 0x0F, 0xE0,
  0x2F, 0xD0, 0x7F, 0xC0,
  0x0F, 0xFF, 0xFF, 0x80,
  0x03, 0xFF, 0xFE, 0x00,
  0x00, 0x7F, 0xE0, 0x00
};

static GUI_CONST_STORAGE GUI_CHARINFO_EXT GUI_FontAA2_32_CharInfo[3] = {
   {  17,  20,   0,   6,  17, acGUI_FontAA2_32_0041 } // code 0041, LATIN CAPITAL LETTER A
  ,{  14,  20,   2,   6,  17, acGUI_FontAA2_32_0042 } // code 0042, LATIN CAPITAL LETTER B
  ,{  14,  20,   1,   6,  17, acGUI_FontAA2_32_0043 } // code 0043, LATIN CAPITAL LETTER C
};

static GUI_CONST_STORAGE GUI_FONT_PROP_EXT GUI_FontAA2_32_Prop1 = {
   0x0041 // first character
  ,0x0043 // last character 
  ,&GUI_FontAA2_32_CharInfo[  0] // address of first character
  ,(GUI_CONST_STORAGE GUI_FONT_PROP_EXT *)0 // pointer to next GUI_FONT_PROP_EXT
};

static GUI_CONST_STORAGE GUI_FONT _FontAA2_32 = {
   GUI_FONTTYPE_PROP_AA2_EXT // type of font   
  ,33 // height of font 
  ,33 // space of font y
  ,1 // magnification x
  ,1 // magnification y
  ,{&GUI_FontAA2_32_Prop1}
  ,33 // Baseline
  ,15 // Height of lowercase characters
  ,20 // Height of capital characters
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _DrawAlphaCircles
*/
static void _DrawAlphaCircles(int mx, int my, int r, int a, int FactorAA) {
  const GUI_COLOR aColor[] = {
    0xC00FFF38,
    0xC000FF8E,
    0xC000FCEA,
    0xC000B4FF,
    0xC0004EFF,
    0xC01304FF,
    0xC06E00FF,
    0xC0D200FF,
    0xC0FF00D2,
    0xC0FF006E,
    0xC0FF0413,
    0xC0FF4E00,
    0xC0FFB400,
    0xC0EAFC00,
    0xC08EFF00,
    0xC038FF0F
  };
  I32 x;
  I32 y;
  int Index;
  I32 SinHQ;
  I32 CosHQ;
  U32 i;
  U32 a1000;

  mx *= FactorAA;
  my *= FactorAA;
  r  *= FactorAA;
  a1000 = a * -1000;
  for (i = 0, Index = 0; i < 360000; i += 22500, Index++) {
    SinHQ = GUI__SinHQ(i + a1000);
    CosHQ = GUI__CosHQ(i + a1000);
    x = (r * CosHQ) >> 16;
    y = (r * SinHQ) >> 16;
    GUI_SetColor(aColor[Index % GUI_COUNTOF(aColor)]);
    GUI_AA_EnableHiRes();
    GUI_AA_SetFactor(FactorAA);
    GUI_AA_FillCircle(mx + x, my + y, r);
    GUI_AA_DisableHiRes();
  }
}

/*********************************************************************
*
*       _DrawSample
*/
static void _DrawSample(GUI_RECT * pRect, int yd) {
  GUI_RECT Rect;

  Rect = *pRect;
  //
  // Use application defined clip rectangle
  //
  GUI_SetClipRect(&Rect);
  //
  // Move clip rectangle
  //
  GUI_MoveRect(&Rect, 65, 0);
  //
  // Draw sample
  //
  _DrawAlphaCircles((Rect.x0 + Rect.x1) >> 1, (Rect.y0 + Rect.y1) >> 1, 35,   0, 4);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringInRectWrap("ABC\nABC\nABC", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
  //
  // Move clip rectangle
  //
  GUI_MoveRect(&Rect, 65, 0);

  GUI_DrawGradientH(Rect.x0, Rect.y0, Rect.x1, Rect.y1, GUI_BLACK, GUI_WHITE);
  Rect.y1 = Rect.y0 + yd;
  GUI_SetColor(GUI_RED);
  GUI_DispStringInRect("ABC", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
  GUI_MoveRect(&Rect, 0, yd);
  GUI_SetColor(GUI_GREEN);
  GUI_DispStringInRect("ABC", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
  GUI_MoveRect(&Rect, 0, yd);
  GUI_SetColor(GUI_BLUE);
  GUI_DispStringInRect("ABC", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
  GUI_MoveRect(&Rect, 0, -yd * 2);
  Rect.y1 = Rect.y0 + yd * 3;
  //
  // Move clip rectangle
  //
  GUI_MoveRect(&Rect, 65, 0);
  //
  // Draw sample
  //
  Rect.y1 = Rect.y0 + yd;
  GUI_SetBkColor(GUI_RED);
  GUI_Clear();
  GUI_MoveRect(&Rect, 0, yd);
  GUI_SetBkColor(GUI_GREEN);
  GUI_Clear();
  GUI_MoveRect(&Rect, 0, yd);
  GUI_SetBkColor(GUI_BLUE);
  GUI_Clear();
  GUI_MoveRect(&Rect, 0, -yd * 2);
  Rect.y1 = Rect.y0 + yd * 3;
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringInRectWrap("ABC\nABC\nABC", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
  //
  // Move clip rectangle
  //
  GUI_MoveRect(&Rect, 65, 0);
  //
  // Draw sample
  //
  Rect.y1 = Rect.y0 + yd;
  GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, GUI_RED,   GUI_BLACK);
  GUI_MoveRect(&Rect, 0, yd);
  GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, GUI_GREEN, GUI_BLACK);
  GUI_MoveRect(&Rect, 0, yd);
  GUI_DrawGradientV(Rect.x0, Rect.y0, Rect.x1, Rect.y1, GUI_BLUE,  GUI_BLACK);
  GUI_MoveRect(&Rect, 0, -yd * 2);
  Rect.y1 = Rect.y0 + yd * 3;
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringInRectWrap("ABC\nABC\nABC", &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
  //
  // Disable application defined clip rectangle
  //
  GUI_SetClipRect(NULL);
}

/*********************************************************************
*
*       _DrawText
*/
static void _DrawText(char * s, GUI_RECT * pRect) {
  GUI_SetFont(GUI_FONT_13_ASCII);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringInRectWrap(s, pRect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
  GUI_SetTextMode(GUI_TM_TRANS);
}

/*********************************************************************
*
*       _DrawScreen
*/
static void _DrawScreen(void) {
  GUI_RECT Rect;
  int      yd;

  GUI_DrawBitmap(&_bmSeggerLogo_50x25, 10, 10);
  GUI_SetFont(GUI_FONT_20B_ASCII);
  GUI_DispStringHCenterAt("Antialiased text sample", 190, 5);
  GUI_SetFont(GUI_FONT_13_ASCII);
  GUI_DispStringHCenterAt("Shows antialiased text on different backgrounds.", 190, 25);
  Rect.x0 = 0;
  Rect.y0 = 43;
  Rect.x1 = 59;
  Rect.y1 = Rect.y0 + 95;
  yd = (Rect.y1 - Rect.y0) / 3;
  //
  // 4 bit antialiasing sample
  //
  _DrawText("Antialiased text\n (4 bpp)", &Rect);
  GUI_SetFont(&_FontAA4_32);
  _DrawSample(&Rect, yd);
  //
  // 2 bit antialiasing sample
  //
  GUI_MoveRect(&Rect, 0, 101);
  _DrawText("Antialiased text\n (2 bpp)", &Rect);
  GUI_SetFont(&_FontAA2_32);
  _DrawSample(&Rect, yd);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void);
void MainTask(void) {
  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  GUI_EnableAlpha(1);
  _DrawScreen();
  while (1) {
    GUI_Delay(100);
  }
}

/*************************** End of file ****************************/
