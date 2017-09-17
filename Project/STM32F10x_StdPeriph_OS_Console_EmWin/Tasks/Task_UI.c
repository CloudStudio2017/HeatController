#include "Task_UI.h"
#include "stdio.h"
#include "CsUI.h"
#include "FlashControl.h"
#include "CslRTC.h"
#include "HeatControlSys.h"


TCsUI_Frame xFrame1;
TCsUI_Frame xChildFrame1;
TCsUI_Frame xChildFrame2;
TCsUI_Frame xChildFrame3;
TCsUI_Frame xChildFrame4;

TCsUI_BaseObjectTable xFrame1_ChildTable[]={&xChildFrame1.Obj, &xChildFrame2.Obj, &xChildFrame3.Obj, &xChildFrame4.Obj,};

static char string_buf[50];
//static uint32_t InitCount = INIT_TOTAL_COUNT;

uint8_t UI_Mode = 0;   //0:Main   1:Config


void static UI_ShowStartupLogo(void)
{
	/*显示   易暖科技 */
}

void static UI_Init(void)
{
//	uint32_t Qv;
//	uint32_t Qr;
	
	CsUI_Init();
	
	xFrame1.BackColor = 0x5500;
	xFrame1.Parent = NULL;
	xFrame1.Childs = xFrame1_ChildTable;
	xFrame1.ChildCount = sizeof(xFrame1_ChildTable) / sizeof(TCsUI_BaseObjectTable);
	xFrame1.Obj.Rect.Left = 0;
	xFrame1.Obj.Rect.Right = 480;
	xFrame1.Obj.Rect.Top = 0;
	xFrame1.Obj.Rect.Bottom = 320;
	xFrame1.Obj.Draw = (TCsUI_Draw)TCsUI_Frame_Draw;
	
	xChildFrame1.BackColor = 0x3300;
	xChildFrame1.Parent = &xFrame1;
	xChildFrame1.Childs = NULL;
	xChildFrame1.Obj.Rect.Left = 10;
	xChildFrame1.Obj.Rect.Top = 20;
	xChildFrame1.Obj.Rect.Right = 30;
	xChildFrame1.Obj.Rect.Bottom = 40;
	xChildFrame1.Obj.Draw = (TCsUI_Draw)TCsUI_Frame_Draw;
	
	xChildFrame2.BackColor = 0x0000;
	xChildFrame2.Parent = &xFrame1;
	xChildFrame2.Childs = NULL;
	xChildFrame2.Obj.Rect.Left = 100;
	xChildFrame2.Obj.Rect.Top = 20;
	xChildFrame2.Obj.Rect.Right = 120;
	xChildFrame2.Obj.Rect.Bottom = 40;
	xChildFrame2.Obj.Draw = (TCsUI_Draw)TCsUI_Frame_Draw;
	
	xChildFrame3.BackColor = 0xF1FF;
	xChildFrame3.Parent = &xFrame1;
	xChildFrame3.Childs = NULL;
	xChildFrame3.Obj.Rect.Left = 210;
	xChildFrame3.Obj.Rect.Top = 40;
	xChildFrame3.Obj.Rect.Right = 330;
	xChildFrame3.Obj.Rect.Bottom = 80;
	xChildFrame3.Obj.Draw = (TCsUI_Draw)TCsUI_Frame_Draw;
	
	xChildFrame4.BackColor = 0xFF00;
	xChildFrame4.Parent = &xFrame1;
	xChildFrame4.Childs = NULL;
	xChildFrame4.Obj.Rect.Left = 300;
	xChildFrame4.Obj.Rect.Top = 5;
	xChildFrame4.Obj.Rect.Right = 480;
	xChildFrame4.Obj.Rect.Bottom = 90;
	xChildFrame4.Obj.Draw = (TCsUI_Draw)TCsUI_Frame_Draw;
	
	UI_ShowStartupLogo();
	
	xFrame1.Obj.Draw(&xFrame1);
	
	TCsUI_Lable_Draw(NULL);
}


void UI_MainShow(void)
{
	CslLCD_FillRect(100,100,400,200, 0x10f0);
	CslLCD_FillRect(100,100,400,200, ~0x10f0);
	CslLCD_FillRect(100,100,400,200, 0x10f0);
	CslLCD_FillRect(100,100,400,200, ~0x10f0);
	CslLCD_FillRect(100,100,400,200, 0x10f0);
	CslLCD_FillRect(100,100,400,200, ~0x10f0);
	CslLCD_FillRect(100,100,400,200, 0x10f0);
	CslLCD_FillRect(100,100,400,200, ~0x10f0);
	CslLCD_FillRect(100,100,400,200, 0x10f0);
	CslLCD_FillRect(100,100,400,200, ~0x10f0);
	CslLCD_FillRect(100,100,400,200, 0x10f0);
	CslLCD_FillRect(100,100,400,200, ~0x10f0);
	CslLCD_FillRect(100,100,400,200, 0x10f0);
	CslLCD_FillRect(100,100,400,200, ~0x10f0);
	CslLCD_FillRect(100,100,400,200, 0x10f0);
	CslLCD_FillRect(100,100,400,200, ~0x10f0);
	CslLCD_FillRect(100,100,400,200, 0x10f0);
	CslLCD_FillRect(100,100,400,200, ~0x10f0);
	CslLCD_FillRect(100,100,400,200, 0x10f0);
	CslLCD_FillRect(100,100,400,200, ~0x10f0);
}

void vTask_UI( void *pvParameters )
{
	unsigned int UI_Tick = 0;
	UI_Init();
	
//	uint32_t iTime=0;
//	CslRTC_Time ui_time;
//	CslRTC_Date ui_date;
	
	//uint8_t Last_UI_Mode = UI_Mode;
	UI_MainShow();
	
	while(1)
	{
		UI_Tick++;
	}
}
