#include "Task_UI.h"
#include "GUI.h"
#include "Dialog.h"
#include "Frames.h"
#include "stdio.h"

WM_HWIN wm_main;

static char string_buf[50];
static WM_HWIN hItem;
static uint32_t InitCount = 3;

void vTask_UI( void *pvParameters )
{
	uint32_t Qv;
	uint32_t Qr;
	
	GUI_Init();
	GUI_Clear();
	
	
	GUI_SetFont(GUI_FONT_COMIC24B_1);
	GUI_SetBkColor(GUI_BLACK);
	GUI_SetColor(GUI_WHITE);
	GUI_DispString("System init.");
	GUI_Delay(200);
	GUI_DispString(".");
	GUI_Delay(200);
	GUI_DispString(".");
	GUI_Delay(200);
	GUI_DispString(".");
	GUI_Delay(200);
	GUI_DispString(".\n");
	
	while(InitCount--)
	{
		Qr = xQueueReceive(InitQueue, &Qv, 2000);
		if(Qr == pdPASS)
		{
			switch(Qv)
			{
				case CONSOLE_INIT_DONE:
					GUI_DispString("Console OK\n");
					break;
				case CONTROL_INIT_DONE:
					GUI_DispString("Control OK\n");
					break;
				case KEYBOARD_INIT_DONE:
					GUI_DispString("KeyBoard OK\n");
					break;
				//case UI_INIT_DONE:
				//	GUI_DispString("\n");
				//	break;
			}
		}
		else
		{
			GUI_DispString("Sys init fail\n");
			while(1);
		}
		GUI_Delay(200);
	}
	vQueueDelete(InitQueue);
	
	GUI_DispString("Run\n");
	GUI_Delay(500);
	//GUI_FillRect(10,100, 100, 200);
	//GUI_SetColor(1 << 24 | GUI_BLUE);
	//GUI_FillRect(40,140, 140, 240);
	//GUI_DispStringAt("Hello", 20, 120);
	//GUI_Delay(2000);
	
	wm_main = CreateWindow_Main();
	
	uint32_t iTime=0;
	while(1)
	{
		GUI_Delay(500);
		
		
		sprintf(string_buf, "xx--%d", iTime++);
		hItem = WM_GetDialogItem(wm_main, (GUI_ID_USER + 0x03));
		TEXT_SetText(hItem, string_buf);
	}
}
