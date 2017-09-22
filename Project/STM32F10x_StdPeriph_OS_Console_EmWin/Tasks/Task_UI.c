#include "Task_UI.h"
#include "stdio.h"
#include "CsUI.h"
#include "CsUI_Font.h"
#include "FlashControl.h"
#include "CslRTC.h"
#include "HeatControlSys.h"
#include "Math.h"
#include "stdlib.h"
#include "ui_source_bitmap.h"


CS_FRAME(xChildFrame1, NULL, 10, 30, 20, 40, 0x001F, NULL);
CS_FRAME(xChildFrame2, NULL, 100, 120, 20, 40, 0x0000, NULL);
CS_FRAME(xChildFrame3, NULL, 210, 330, 40, 80, 0xF1FF, NULL);


CS_BITMAP(xBitmap1, NULL,   0,  50,  30,  60, 0xFF00, 0x00, xBitmapdata1);
CS_BITMAP(xBitmap2, NULL, 140, 400,  50, 300, 0xFFFF, 0x00, xBitmapdata2);

CS_BITMAP(Title_Bitmap1, NULL, 0, 100, 0, 100, 0x001F, 0x0000, xBitmapdata3);

CS_LABLE(xLable1, NULL, 50, 100, 50, 70, 0xFFFF, 0x0000 ,"ABCD12345", NULL);

TCsUI_BaseObjectTable xChildFrame4_ChildTable[]={&xLable1.Obj};

CS_FRAME(xChildFrame4, NULL, 300, 480, 5, 90, 0xFF00, xChildFrame4_ChildTable);

TCsUI_BaseObjectTable xFrame1_ChildTable[]={&xChildFrame1.Obj, &xChildFrame2.Obj, &xChildFrame3.Obj, &xChildFrame4.Obj, &xBitmap1.Obj, &xBitmap2.Obj, &Title_Bitmap1.Obj};

CS_FRAME(xFrame1, NULL, 0, 480, 0, 320, 0x5500, xFrame1_ChildTable);

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
	extern TCsUI_TypeBase TCsUI_Bitmap_Draw2(TCsUI_Bitmap* Self);
	CsUI_Init();
	
	FlashControl_Init();
		
	xChildFrame1.Parent = &xFrame1;
	xChildFrame2.Parent = &xFrame1;
	xChildFrame3.Parent = &xFrame1;
	xChildFrame4.Parent = &xFrame1;
	
	xLable1.Parent = &xChildFrame4;
	xLable1.Font = CsUI_Font_ASCII_1218;
	
	xBitmap1.Parent = &xFrame1;
	xBitmap2.Parent = &xFrame1;
	//xBitmap2.Obj.Draw = (TCsUI_Draw)TCsUI_Bitmap_Draw_Ext;
	Title_Bitmap1.Parent = &xFrame1;
	
	UI_ShowStartupLogo();
	
	xFrame1.Obj.Draw(&xFrame1);
	
	//TCsUI_Lable_Draw(NULL);
}


void UI_MainShow(void)
{
	return;
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
	//xx0 = 80 * cos(i * 3.1415 / 180);
	//yy0 = 100 * sin(i * 3.1415 / 180);
	xx = 0;
	yy = 0;
	xx0 = sizeof(TBitmap_Head);
	yy0 = 0;
	
	#if 0
	while(1)
	{
		xx = rand() % (480 -100) + 50;
		yy = rand() % (320 -100) + 50;
		CsUI_FillCircle(xx, yy, 25, rand() % 65536);
		xx0 = xx;
		yy0 = yy;
		
		UI_Tick++;
		if(UI_Tick == 100)
			break;
	}
	#endif
	
	while(1)
	{
		UI_Tick++;
		sprintf(string_buf, "%06d", UI_Tick);
		xLable1.Text = string_buf;
		xLable1.Obj.Draw(&xLable1);
		vTaskDelay(100);
	}
}
