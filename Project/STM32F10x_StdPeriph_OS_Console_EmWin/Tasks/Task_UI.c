#include "Task_UI.h"
#include "stdio.h"
#include "CsUI.h"
#include "CsUI_Font.h"
#include "FlashControl.h"
#include "CslRTC.h"
#include "Math.h"
#include "stdlib.h"
#include "ui_source_bitmap.h"
#include "ui_FrmMain.h"
#include "ui_FrmConfig1.h"
#include "ui_FrmConfig2.h"
#include "ui_FrmTest.h"


static char string_buf[50];
//static uint32_t InitCount = INIT_TOTAL_COUNT;

volatile uint8_t UI_Index = 0xFF;   //0:Main   1:Config1  2:Config2  3:Test  0x80:Logo  0xFF none

CS_BITMAP(Bmp_Caption, NULL, 130, 100, 10, 10, CSUI_BLUE, CSUI_WHITE, xBitmapCaption);


void ui_ShowPowerOff(void)
{
	CslLCD_BLK(0);               //LCD light off
	CsLCD_DisplayControl(1);
	CslLCD_Clear(0x0);
}

void ui_PowerOff_Process(void)
{
	//noting to do when power is off
}

void ui_ShowStartupLogo(void)
{
	/*显示   易暖科技 */
	CsLCD_DisplayControl(0);
	CslLCD_FillRect(0,0, 480,320, CSUI_WHITE);
	Bmp_Caption.Obj.Draw(&Bmp_Caption);
	CslLCD_BLK(1);               //LCD light on
}

void ui_StartupLogo_Process(void)
{
	vTaskDelay(1500);
	UI_Index = 0;
}

void UI_Init(void)
{
	CsUI_Init();
}

void UI_Reset(void)
{
	UI_Index = 0xFF;
}

void UI_Start(void)
{
	UI_Index = 0x80;
}

void vTask_UI( void *pvParameters )
{
	unsigned int UI_Tick = 0;
	unsigned char UI_CurrentIndex = 0xFF;
	
	UI_Init();
	
	ui_FrmMain_Init();
	ui_FrmConfig1_Init();
	ui_FrmConfig2_Init();
	ui_FrmTest_Init();
	
	while(1)
	{
		UI_Tick++;
		vTaskDelay(100);
		
		if(UI_CurrentIndex != UI_Index)
		{
			switch(UI_Index)
			{
				case 0:
					ui_FrmMain_ShowFrame();
					break;
				case 1:
					ui_FrmConfig1_ShowFrame();
					break;
				case 2:
					ui_FrmConfig2_ShowFrame();
					break;
				case 3:
					ui_FrmTest_ShowFrame();
					break;
				case 0x80:
					ui_ShowStartupLogo();
					break;
				case 0xFF:
					ui_ShowPowerOff();
					break;
			}
			UI_CurrentIndex = UI_Index;
		}
		switch(UI_CurrentIndex)
		{
			case 0:
				ui_FrmMain_Process();
				break;
			case 1:
				ui_FrmConfig1_Process();
				break;
			case 2:
				ui_FrmConfig2_Process();
				break;
			case 3:
				ui_FrmTest_Process();
				break;
			case 0x80:
				ui_StartupLogo_Process();
				break;
			case 0xFF:
				ui_PowerOff_Process();
				break;
		}
	}
}
