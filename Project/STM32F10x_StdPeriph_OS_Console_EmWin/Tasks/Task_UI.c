#include "Task_UI.h"
#include "stdio.h"
#include "CsUI.h"
#include "CsUI_Font.h"
#include "FlashControl.h"
#include "CslRTC.h"
#include "HeatControlSys.h"
#include "Math.h"
#include "stdlib.h"

TCsUI_Frame xFrame1;
TCsUI_Frame xChildFrame1;
TCsUI_Frame xChildFrame2;
TCsUI_Frame xChildFrame3;
TCsUI_Frame xChildFrame4;
TCsUI_Lable xLable1;

TCsUI_BaseObjectTable xFrame1_ChildTable[]={&xChildFrame1.Obj, &xChildFrame2.Obj, &xChildFrame3.Obj, &xChildFrame4.Obj};
TCsUI_BaseObjectTable xChildFrame4_ChildTable[]={&xLable1.Obj};

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
	xChildFrame4.Childs = xChildFrame4_ChildTable;
	xChildFrame4.ChildCount = sizeof(xChildFrame4_ChildTable) / sizeof(TCsUI_BaseObjectTable);
	xChildFrame4.Obj.Rect.Left = 300;
	xChildFrame4.Obj.Rect.Top = 5;
	xChildFrame4.Obj.Rect.Right = 480;
	xChildFrame4.Obj.Rect.Bottom = 90;
	xChildFrame4.Obj.Draw = (TCsUI_Draw)TCsUI_Frame_Draw;
	
	xLable1.BackColor = 0x0000;
	xLable1.FrontColor = 0xFFFF;
	xLable1.Parent = &xChildFrame4;
	xLable1.Text = "ABCD99213";
	xLable1.Font = CsUI_Font_ASCII_1218;
	xLable1.Obj.Rect.Left = 50;
	xLable1.Obj.Rect.Top = 50;
	xLable1.Obj.Rect.Right = 100;
	xLable1.Obj.Rect.Bottom = 70;
	xLable1.Obj.Draw = (TCsUI_Draw)TCsUI_Lable_Draw;
	
	UI_ShowStartupLogo();
	
	xFrame1.Obj.Draw(&xFrame1);
	
	//TCsUI_Lable_Draw(NULL);
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
	
	CsUI_DrawLine(20, 40, 40, 20, 0x1234);
	
	float i=0;
	int xx,yy;
	int xx0,yy0;
	srand(9999);
	xx0 = 80 * cos(i * 3.1415 / 180);
	yy0 = 100 * sin(i * 3.1415 / 180);
	while(1)
	{
		i+=0.01;
		xx = 80 * cos(i * 3.1415 / 180);
		yy = 100 * sin(i * 3.1415 / 180);
		CsUI_DrawLine(200,200, 200 + xx0, 200 + yy0, 0);
		CsUI_DrawLine(200,200, 200 + xx, 200 + yy, 0xfff1);
		xx0 = xx;
		yy0 = yy;
	}
	for(i=0;i<45;i++)
	{
		xx = 100 * cos(i * 3.1415 / 180);
		yy = 100 * sin(i * 3.1415 / 180);
		CsUI_DrawLine(200,200, 200 + xx, 200 + yy, 0x1111);
	}
	for(i=45;i<90;i++)
	{
		xx = 100 * cos(i * 3.1415 / 180);
		yy = 100 * sin(i * 3.1415 / 180);
		CsUI_DrawLine(200,200, 200 + xx, 200 + yy, 0x2222);
	}
	for(i=90;i<135;i++)
	{
		xx = 100 * cos(i * 3.1415 / 180);
		yy = 100 * sin(i * 3.1415 / 180);
		CsUI_DrawLine(200,200, 200 + xx, 200 + yy, 0x3333);
	}
	for(i=135;i<180;i++)
	{
		xx = 100 * cos(i * 3.1415 / 180);
		yy = 100 * sin(i * 3.1415 / 180);
		CsUI_DrawLine(200,200, 200 + xx, 200 + yy, 0x4444);
	}
	for(i=180;i<225;i++)
	{
		xx = 100 * cos(i * 3.1415 / 180);
		yy = 100 * sin(i * 3.1415 / 180);
		CsUI_DrawLine(200,200, 200 + xx, 200 + yy, 0x5555);
	}
	for(i=225;i<270;i++)
	{
		xx = 100 * cos(i * 3.1415 / 180);
		yy = 100 * sin(i * 3.1415 / 180);
		CsUI_DrawLine(200,200, 200 + xx, 200 + yy, 0x6666);
	}
	for(i=270;i<315;i++)
	{
		xx = 100 * cos(i * 3.1415 / 180);
		yy = 100 * sin(i * 3.1415 / 180);
		CsUI_DrawLine(200,200, 200 + xx, 200 + yy, 0x7777);
	}
	for(i=315;i<360;i++)
	{
		xx = 100 * cos(i * 3.1415 / 180);
		yy = 100 * sin(i * 3.1415 / 180);
		CsUI_DrawLine(200,200, 200 + xx, 200 + yy, 0x8888);
	}
	
	while(1)
	{
		UI_Tick++;
	}
}
