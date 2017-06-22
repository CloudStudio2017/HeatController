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
File        : WM_Redraw.c
Purpose     : Demonstrates the redrawing mechanism of the window manager
Requirements: WindowManager - (x)
              MemoryDevices - ( )
              AntiAliasing  - ( )
              VNC-Server    - ( )
              PNG-Library   - ( )
              TrueTypeFonts - ( )

----------------------------------------------------------------------
*/

#include "GUI.h"
#include "WM.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 5)

/*******************************************************************
*
*       static code
*
********************************************************************
*/
/*******************************************************************
*
*       _cbBkWindow
*/
static void _cbBkWindow(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_ClearRect(0, 50, 319, 239);
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _cbWindow
*/
static void _cbWindow(WM_MESSAGE* pMsg) {
  GUI_RECT Rect;

  switch (pMsg->MsgId) {
  case WM_PAINT:
    WM_GetInsideRect(&Rect);
    GUI_SetBkColor(GUI_RED);
    GUI_SetColor(GUI_YELLOW);
    GUI_ClearRectEx(&Rect);
    GUI_DrawRectEx(&Rect);
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_Font8x16);
    GUI_DispStringHCenterAt("Foreground window", 75, 40);
    break;
  default:
    WM_DefaultProc(pMsg);
  }
}

/*******************************************************************
*
*       _MoveWindow
*/
static void _MoveWindow(const char* pText) {
  WM_HWIN hWnd;
  int     i;

  //
  // Create foreground window
  //
  hWnd = WM_CreateWindow(10, 50, 150, 100, WM_CF_SHOW, _cbWindow, 0);
  GUI_Delay(500);
  //
  // Move foreground window
  //
  for (i = 0; i < 40; i++) {
    WM_MoveWindow(hWnd, 2, 2);
    GUI_Delay(10);
  }
  //
  // Show text before deleting window if we have one
  //
  if (pText) {
    GUI_DispStringAt(pText, 5, 50);
    GUI_Delay(2500);
  }
  //
  // Delete foreground window
  //
  WM_DeleteWindow(hWnd);
  WM_Invalidate(WM_HBKWIN);
  GUI_Exec();
}

/*******************************************************************
*
*       _DemoRedraw
*/
static void _DemoRedraw(void) {
  WM_CALLBACK * _cbOldBk;

  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();
  GUI_SetColor(GUI_WHITE);
  GUI_SetFont(&GUI_Font24_ASCII);
  GUI_DispStringHCenterAt("WM_Redraw - Sample", 160, 5);
  GUI_SetFont(&GUI_Font8x16);
  while(1) {
    //
    // Move a window over background
    //
    _MoveWindow("Background has not been redrawn");
    //
    // Clear background
    //
    GUI_ClearRect(0, 50, 319, 239);
    GUI_Delay(1000);
    //
    // Set callback for background window
    //
    _cbOldBk = WM_SetCallback(WM_HBKWIN, _cbBkWindow);
    //
    // Move a window over background
    //
    _MoveWindow("Background has been redrawn");
    //
    // Delete callback for Background window
    //
    WM_SetCallback(WM_HBKWIN, _cbOldBk);
  }
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
void MainTask(void) {
  GUI_Init();
  //
  // Check if recommended memory for the sample is available
  //
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  _DemoRedraw();
}

/*************************** End of file ****************************/
