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
File        : 320_Bubbles.c
Content     : Bitmap 15 * 12
---------------------------END-OF-HEADER------------------------------
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif


static GUI_CONST_STORAGE unsigned short ac320_Bubbles[] = {
  0x0B1F, 0x3F5D, 0x3F5D, 0x233E, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F,
  0x3F5D, 0x6B9D, 0x63BD, 0x739C, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F,
  0x739C, 0x63BD, 0x57BF, 0x739C, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F,
  0x3F5D, 0x739C, 0x739C, 0x577D, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x233E, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F,
  0x0B1F, 0x0B1F, 0x233E, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x3F5D, 0x63BD, 0x233E, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F,
  0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x233E, 0x3F5D, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F,
  0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F,
  0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F,
  0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F,
  0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x233E, 0x0B1F, 0x0B1F,
  0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x3F5D, 0x63BD, 0x233E, 0x0B1F,
  0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x0B1F, 0x233E, 0x3F5D, 0x0B1F, 0x0B1F
};

extern GUI_CONST_STORAGE GUI_BITMAP bm320_Bubbles;

GUI_CONST_STORAGE GUI_BITMAP bm320_Bubbles = {
  15, /* XSize */
  12, /* YSize */
  30, /* BytesPerLine */
  16, /* BitsPerPixel */
  (unsigned char *)ac320_Bubbles,  /* Pointer to picture data */
  NULL  /* Pointer to palette */
 ,GUI_DRAW_BMP555
};

/*************************** End of file ****************************/
