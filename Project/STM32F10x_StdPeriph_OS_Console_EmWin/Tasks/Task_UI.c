#include "Task_UI.h"
#include "GUI.h"
#include "Dialog.h"
#include "Frames.h"
#include "stdio.h"

#include "FlashControl.h"

WM_HWIN wm_main;

static char string_buf[50];
static WM_HWIN hItem;
static uint32_t InitCount = INIT_TOTAL_COUNT;



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
			//while(1);
		}
		GUI_Delay(200);
	}
	vQueueDelete(InitQueue);
	
	//Test Read Flash ID
	do
	{
		if(FlashControl_Init())
		{
			GUI_DispString("Flash init fail\n");
			break;
		}
		GUI_DispString("Flash init done\n");
		
		uint32_t flashID;
		flashID = FlashControl_ReadID();
		GUI_DispString("Flash ID = 0x");
		GUI_DispHex(flashID, 8);
		
		//FlashControl_Erase(0x00, 0x1000);
		//GUI_DispString(" Erase 0 ");
		
		//uint8_t tmpBuf[512] = {0x34, 0x56, 0x78, 0x12};
		//tmpBuf[254] = 0x11;
		//tmpBuf[255] = 0x22;
		//tmpBuf[256] = 0x33;
		//tmpBuf[257] = 0x44;
		//tmpBuf[511] = 0x55;
		//FlashControl_Write(tmpBuf, 0x00, 512);
		//GUI_DispString(" Wrtie 4B \n");
		
		uint8_t tmpBuf2[4];
		FlashControl_Read(tmpBuf2, 0x100, 4);
		GUI_DispString("Read 4B: 0x");
		GUI_DispHex(tmpBuf2[0], 2);
		GUI_DispHex(tmpBuf2[1], 2);
		GUI_DispHex(tmpBuf2[2], 2);
		GUI_DispHex(tmpBuf2[3], 2);
		
		GUI_Delay(4000);
		GUI_DispString("\n");
	}while(0);
	
	GUI_DispString("Run\n");
	GUI_Delay(500);
	//GUI_FillRect(10,100, 100, 200);
	//GUI_SetColor(1 << 24 | GUI_BLUE);
	//GUI_FillRect(40,140, 140, 240);
	//GUI_DispStringAt("Hello", 20, 120);
	//GUI_Delay(2000);
	
	
	/* GUI BMP DRAW TEST */
	do
	{
		uint32_t tmpBMP_Index = 0;
		
		GUI_BMP_DrawEx(GetUISourceData, &tmpBMP_Index, 100, 100);
	}while(0);
	
	GUI_Delay(4000);
	
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
