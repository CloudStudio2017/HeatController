/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.32                          *
*        Compiled Oct  8 2015, 11:59:02                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_TEXT_0 (GUI_ID_USER + 0x01)
#define ID_TEXT_1 (GUI_ID_USER + 0x02)
#define ID_TEXT_2 (GUI_ID_USER + 0x03)
#define ID_TEXT_3 (GUI_ID_USER + 0x04)
#define ID_TEXT_4 (GUI_ID_USER + 0x05)
#define ID_TEXT_5 (GUI_ID_USER + 0x06)
#define ID_TEXT_6 (GUI_ID_USER + 0x07)
#define ID_TEXT_7 (GUI_ID_USER + 0x08)
#define ID_TEXT_8 (GUI_ID_USER + 0x09)
#define ID_TEXT_9 (GUI_ID_USER + 0x0A)
#define ID_TEXT_10 (GUI_ID_USER + 0x0B)
#define ID_TEXT_11 (GUI_ID_USER + 0x0C)
#define ID_TEXT_12 (GUI_ID_USER + 0x0D)
#define ID_TEXT_13 (GUI_ID_USER + 0x0E)
#define ID_TEXT_14 (GUI_ID_USER + 0x0F)
#define ID_TEXT_15 (GUI_ID_USER + 0x10)
#define ID_TEXT_16 (GUI_ID_USER + 0x11)
#define ID_TEXT_17 (GUI_ID_USER + 0x12)
#define ID_TEXT_18 (GUI_ID_USER + 0x13)
#define ID_TEXT_19 (GUI_ID_USER + 0x14)
#define ID_TEXT_20 (GUI_ID_USER + 0x15)
#define ID_TEXT_21 (GUI_ID_USER + 0x16)
#define ID_TEXT_22 (GUI_ID_USER + 0x17)
#define ID_TEXT_23 (GUI_ID_USER + 0x18)
#define ID_TEXT_24 (GUI_ID_USER + 0x19)
#define ID_TEXT_25 (GUI_ID_USER + 0x1A)
#define ID_TEXT_26 (GUI_ID_USER + 0x1B)
#define ID_TEXT_27 (GUI_ID_USER + 0x1C)
#define ID_TEXT_28 (GUI_ID_USER + 0x1D)
#define ID_TEXT_29 (GUI_ID_USER + 0x1E)
#define ID_TEXT_30 (GUI_ID_USER + 0x1F)
#define ID_TEXT_31 (GUI_ID_USER + 0x20)
#define ID_TEXT_32 (GUI_ID_USER + 0x21)
#define ID_TEXT_33 (GUI_ID_USER + 0x22)
#define ID_TEXT_34 (GUI_ID_USER + 0x23)
#define ID_TEXT_35 (GUI_ID_USER + 0x24)
#define ID_TEXT_36 (GUI_ID_USER + 0x25)
#define ID_TEXT_37 (GUI_ID_USER + 0x26)
#define ID_TEXT_38 (GUI_ID_USER + 0x27)
#define ID_TEXT_39 (GUI_ID_USER + 0x28)
#define ID_TEXT_40 (GUI_ID_USER + 0x29)
#define ID_TEXT_41 (GUI_ID_USER + 0x2A)
#define ID_TEXT_42 (GUI_ID_USER + 0x2B)
#define ID_TEXT_43 (GUI_ID_USER + 0x2C)
#define ID_TEXT_44 (GUI_ID_USER + 0x2D)
#define ID_TEXT_45 (GUI_ID_USER + 0x2E)
#define ID_TEXT_46 (GUI_ID_USER + 0x2F)
#define ID_TEXT_47 (GUI_ID_USER + 0x30)
#define ID_TEXT_48 (GUI_ID_USER + 0x31)


// USER START (Optionally insert additional defines)
extern GUI_CONST_STORAGE GUI_FONT GUI_FontCNFonts;
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window_Config", ID_WINDOW_0, 0, 0, 480, 320, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 181, 6, 123, 28, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_1, 20, 40, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_2, 20, 66, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_3, 20, 92, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_4, 20, 118, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_5, 20, 144, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_6, 20, 170, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_7, 20, 196, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_8, 20, 222, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_9, 250, 40, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_10, 250, 66, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_11, 250, 92, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_12, 250, 118, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_13, 250, 144, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_14, 250, 170, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_15, 250, 196, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_16, 250, 222, 100, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_17, 200, 40, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_18, 200, 66, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_19, 200, 92, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_20, 200, 118, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_21, 200, 144, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_22, 200, 170, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_23, 200, 196, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_24, 200, 222, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_25, 430, 40, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_26, 430, 66, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_27, 430, 92, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_28, 430, 117, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_29, 430, 144, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_30, 430, 170, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_31, 430, 196, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_32, 430, 222, 36, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_33, 130, 40, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_34, 130, 66, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_35, 130, 92, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_36, 130, 118, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_37, 130, 144, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_38, 130, 170, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_39, 130, 196, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_40, 130, 222, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_41, 360, 40, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_42, 360, 66, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_43, 360, 92, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_44, 360, 118, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_45, 360, 144, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_46, 360, 170, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_47, 360, 196, 60, 24, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_48, 360, 222, 60, 24, 0, 0x64, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Window_Config'
    //
    hItem = pMsg->hWin;
    WINDOW_SetBkColor(hItem, GUI_MAKE_COLOR(0x00ED5E27));
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetText(hItem, "\xe7\xb3\xbb\xe7\xbb\x9f\xe8\xae\xbe\xe7\xbd\xae");
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetText(hItem, "\xe9\xbc\x93\xe9\xa3\x8e\xe5\x89\x8d\xe5\x90\xb9\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetText(hItem, "\xe5\xbc\x95\xe9\xa3\x8e\xe5\x89\x8d\xe5\x90\xb9\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetText(hItem, "\xe9\xa2\x84\xe6\x96\x99\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetText(hItem, "\xe9\xa2\x84\xe7\x83\xad\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetText(hItem, "\xe7\x82\xb9\xe7\x81\xab\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetText(hItem, "\xe8\xbf\x9b\xe6\x96\x99\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetText(hItem, "\xe5\x81\x9c\xe6\x96\x99\xe6\x97\xb6\xe9\x97\xb4\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetText(hItem, "\xe9\xbc\x93\xe9\xa3\x8e\xe5\x90\x8e\xe5\x90\xb9\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetText(hItem, "\xe5\xbc\x95\xe9\xa3\x8e\xe5\x90\x8e\xe5\x90\xb9\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
    TEXT_SetText(hItem, "\xe4\xbf\x9d\xe7\x81\xab\xe9\x80\x81\xe6\x96\x99\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
    TEXT_SetText(hItem, "\xe4\xbf\x9d\xe7\x81\xab\xe5\x81\x9c\xe6\x96\x99\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
    TEXT_SetText(hItem, "\xe5\xbc\x80\xe6\x9c\xba\xe6\xb8\xa9\xe5\xba\xa6\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
    TEXT_SetText(hItem, "\xe5\x81\x9c\xe6\x9c\xba\xe6\xb8\xa9\xe5\xba\xa6\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_14);
    TEXT_SetText(hItem, "\xe4\xbf\x9d\xe7\x81\xab\xe6\xb8\xa9\xe5\xba\xa6\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_15);
    TEXT_SetText(hItem, "\xe5\xbc\x80\xe6\xb3\xb5\xe6\xb8\xa9\xe5\xba\xa6\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_16);
    TEXT_SetText(hItem, "\xe5\x81\x9c\xe6\xb3\xb5\xe6\xb8\xa9\xe5\xba\xa6\xef\xbc\x9a");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_17);
    TEXT_SetText(hItem, "\xe7\xa7\x92");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_18);
    TEXT_SetText(hItem, "\xe7\xa7\x92");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_19);
    TEXT_SetText(hItem, "\xe7\xa7\x92");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_20);
    TEXT_SetText(hItem, "\xe7\xa7\x92");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_21);
    TEXT_SetText(hItem, "\xe7\xa7\x92");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_22);
    TEXT_SetText(hItem, "\xe7\xa7\x92");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_23);
    TEXT_SetText(hItem, "\xe7\xa7\x92");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_24);
    TEXT_SetText(hItem, "\xe7\xa7\x92");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_25);
    TEXT_SetText(hItem, "\xe7\xa7\x92");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_26);
    TEXT_SetText(hItem, "\xe7\xa7\x92");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_27);
    TEXT_SetText(hItem, "\xe7\xa7\x92");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_28);
    TEXT_SetText(hItem, "\xe5\xba\xa6");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_29);
    TEXT_SetText(hItem, "\xe5\xba\xa6");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_30);
    TEXT_SetText(hItem, "\xe5\xba\xa6");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_31);
    TEXT_SetText(hItem, "\xe5\xba\xa6");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_32);
    TEXT_SetText(hItem, "\xe5\xba\xa6");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_33);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_34);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_35);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_36);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_37);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_38);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_39);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_40);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_41);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_42);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_43);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_44);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_45);
    TEXT_SetText(hItem, "00:00");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_46);
    TEXT_SetText(hItem, "000");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_47);
    TEXT_SetText(hItem, "000");
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_48);
    TEXT_SetText(hItem, "000");
    // USER START (Optionally insert additional code for further widget initialization)
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_13);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_14);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_15);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_16);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_17);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_18);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_19);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_20);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_21);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_22);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_23);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_24);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_25);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_26);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_27);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_28);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_29);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_30);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_31);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_32);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_33);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_34);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_35);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_36);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_37);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_38);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_39);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_40);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_41);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_42);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_43);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_44);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_45);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_46);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_47);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_48);
    TEXT_SetFont(hItem, &GUI_FontCNFonts);
		    // USER END
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
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
*       CreateWindow_Config
*/
WM_HWIN CreateWindow_Config(void);
WM_HWIN CreateWindow_Config(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
