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
#include "ui_FrmMain.h"
#include "ui_FrmConfig1.h"
#include "ui_FrmConfig2.h"


static char string_buf[50];
//static uint32_t InitCount = INIT_TOTAL_COUNT;

volatile uint8_t UI_Index = 0;   //0:Main   1:Config1  2:Config2


void static UI_ShowStartupLogo(void)
{
	/*显示   易暖科技 */
}

void static UI_Init(void)
{
	CsUI_Init();
	
	FlashControl_Init();
	
	UI_ShowStartupLogo();
}

void vTask_UI( void *pvParameters )
{
	unsigned int UI_Tick = 0;
	unsigned char UI_CurrentIndex = 0;
	UI_Init();
	
	ui_FrmMain_Init();
	ui_FrmConfig1_Init();
	ui_FrmConfig2_Init();
	
	ui_FrmMain_ShowFrame();
	
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
		}
	}
}
