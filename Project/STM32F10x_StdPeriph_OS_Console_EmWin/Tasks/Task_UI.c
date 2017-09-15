#include "Task_UI.h"
#include "stdio.h"
#include "CslLCD.h"
#include "FlashControl.h"
#include "CslRTC.h"
#include "HeatControlSys.h"



static char string_buf[50];
static uint32_t InitCount = INIT_TOTAL_COUNT;

uint8_t UI_Mode = 0;   //0:Main   1:Config


void static UI_ShowStartupLogo(void)
{
	/*显示   易暖科技 */
}

void static UI_Init(void)
{
	uint32_t Qv;
	uint32_t Qr;
	
	CslLCD_Init();
	
	UI_ShowStartupLogo();
}


void UI_MainShow(void)
{
	CslLCD_FillRect(0,0,400,300, 0x10f0);
	CslLCD_FillRect(0,0,400,300, ~0x10f0);
	CslLCD_FillRect(0,0,400,300, 0x10f0);
	CslLCD_FillRect(0,0,400,300, ~0x10f0);
	CslLCD_FillRect(0,0,400,300, 0x10f0);
	CslLCD_FillRect(0,0,400,300, ~0x10f0);
	CslLCD_FillRect(0,0,400,300, 0x10f0);
	CslLCD_FillRect(0,0,400,300, ~0x10f0);
	CslLCD_FillRect(0,0,400,300, 0x10f0);
	CslLCD_FillRect(0,0,400,300, ~0x10f0);
}

void vTask_UI( void *pvParameters )
{
	unsigned int UI_Tick = 0;
	UI_Init();
	
	uint32_t iTime=0;
	CslRTC_Time ui_time;
	CslRTC_Date ui_date;
	
	uint8_t Last_UI_Mode = UI_Mode;
	UI_MainShow();
	
	while(1)
	{
		UI_Tick++;
	}
}
