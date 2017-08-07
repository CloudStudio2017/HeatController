#include "Task_UI.h"
#include "GUI.h"
#include "Dialog.h"
#include "Frames.h"
#include "stdio.h"

#include "FlashControl.h"
#include "CslRTC.h"
#include "HeatControlSys.h"

extern GUI_CONST_STORAGE GUI_FONT GUI_FontCNFonts;
extern GUI_CONST_STORAGE GUI_FONT GUI_FontCNFonts_StartupLog;

WM_HWIN wm_main;
WM_HWIN wm_config;

static char string_buf[50];
static WM_HWIN hItem;
static uint32_t InitCount = INIT_TOTAL_COUNT;

uint8_t UI_Mode = 0;   //0:Main   1:Config


static void UI_Main_StatusUpdate(void)
{
	hItem = WM_GetDialogItem(wm_main, (GUI_ID_USER + 0x02));
	switch(HCS_Struct.Status)
	{
		case HCS_STATUS_STANDBY:
			//TEXT_SetText(hItem, "Standby");
			TEXT_SetText(hItem, "\xe5\xbe\x85\xe6\x9c\xba");
			break;
		case HCS_STATUS_STARTUP:
			//TEXT_SetText(hItem, "Startup");
			TEXT_SetText(hItem, "\xe5\x90\xaf\xe5\x8a\xa8");
			break;
		case HCS_STATUS_PREBLOW:
			//TEXT_SetText(hItem, "PreBlow");
			TEXT_SetText(hItem, "\xe5\x89\x8d\xe5\x90\xb9");
			break;
		case HCS_STATUS_PREMATERIAL:
			//TEXT_SetText(hItem, "PreMaterial");
			TEXT_SetText(hItem, "\xe9\xa2\x84\xe6\x96\x99");
			break;
		case HCS_STATUS_WARMEDUP:
			//TEXT_SetText(hItem, "WarmedUp");
			TEXT_SetText(hItem, "\xe9\xa2\x84\xe7\x83\xad");
			break;
		case HCS_STATUS_FIREUP:
			//TEXT_SetText(hItem, "FireUp");
			TEXT_SetText(hItem, "\xe7\x82\xb9\xe7\x81\xab");
			break;
		case HCS_STATUS_RUNNING:
			//TEXT_SetText(hItem, "Running");
			TEXT_SetText(hItem, "\xe8\xbf\x90\xe8\xa1\x8c");
			break;
		case HCS_STATUS_FIREPROTECT:
			//TEXT_SetText(hItem, "FireProtect");
			TEXT_SetText(hItem, "\xe4\xbf\x9d\xe7\x81\xab");
			break;
		case HCS_STATUS_POWEROFF:
			//TEXT_SetText(hItem, "PowerOff");
			TEXT_SetText(hItem, "\xe5\x85\xb3\xe6\x9c\xba");
			break;
	}
	hItem = WM_GetDialogItem(wm_main, (GUI_ID_USER + 0x0B));   //Material
	if(HCS_Struct.MaterialMachine)
	{
		//TEXT_SetText(hItem, "ON");
		TEXT_SetText(hItem, "\xe8\xbf\x90\xe8\xa1\x8c");
	}
	else
	{
		//TEXT_SetText(hItem, "OFF");
		TEXT_SetText(hItem, "\xe5\x81\x9c\xe6\xad\xa2");
	}
	hItem = WM_GetDialogItem(wm_main, (GUI_ID_USER + 0x0C));  //Fire up
	if(HCS_Struct.FireUp)
	{
		//TEXT_SetText(hItem, "ON");
		TEXT_SetText(hItem, "\xe8\xbf\x90\xe8\xa1\x8c");
	}
	else
	{
		//TEXT_SetText(hItem, "OFF");
		TEXT_SetText(hItem, "\xe5\x81\x9c\xe6\xad\xa2");
	}
	hItem = WM_GetDialogItem(wm_main, (GUI_ID_USER + 0x0D));  //Water pump
	if(HCS_Struct.WaterPump)
	{
		//TEXT_SetText(hItem, "ON");
		TEXT_SetText(hItem, "\xe8\xbf\x90\xe8\xa1\x8c");
	}
	else
	{
		//TEXT_SetText(hItem, "OFF");
		TEXT_SetText(hItem, "\xe5\x81\x9c\xe6\xad\xa2");
	}
	hItem = WM_GetDialogItem(wm_main, (GUI_ID_USER + 0x0E));  //Lead fan
	if(HCS_Struct.LeadFan)
	{
		//TEXT_SetText(hItem, "ON");
		TEXT_SetText(hItem, "\xe8\xbf\x90\xe8\xa1\x8c");
	}
	else
	{
		//TEXT_SetText(hItem, "OFF");
		TEXT_SetText(hItem, "\xe5\x81\x9c\xe6\xad\xa2");
	}
	hItem = WM_GetDialogItem(wm_main, (GUI_ID_USER + 0x0F));  //Air blower
	if(HCS_Struct.AirBlower)
	{
		//TEXT_SetText(hItem, "ON");
		TEXT_SetText(hItem, "\xe8\xbf\x90\xe8\xa1\x8c");
	}
	else
	{
		//TEXT_SetText(hItem, "OFF");
		TEXT_SetText(hItem, "\xe5\x81\x9c\xe6\xad\xa2");
	}
	hItem = WM_GetDialogItem(wm_main, (GUI_ID_USER + 0x10));  //Pressure
	if(HCS_Struct.WaterHot)
	{
		//TEXT_SetText(hItem, "--");
		TEXT_SetText(hItem, "- -");
	}
	else
	{
		//TEXT_SetText(hItem, "Normal");
		TEXT_SetText(hItem, "\xe6\xad\xa3\xe5\xb8\xb8");
	}
	hItem = WM_GetDialogItem(wm_main, (GUI_ID_USER + 0x11));  //Water level
	if(HCS_Struct.WaterLow)
	{
		//TEXT_SetText(hItem, "Not enough");
		TEXT_SetText(hItem, "\xe4\xb8\x8d\xe8\xb6\xb3");
	}
	else
	{
		//TEXT_SetText(hItem, "Normal");
		TEXT_SetText(hItem, "\xe6\xad\xa3\xe5\xb8\xb8");
	}
}

static void UI_Config_Update(void)
{
	uint16_t tmpValue;
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x22));
	tmpValue = HCS_Struct.Params[HCS_PARAM_GFQC];
	sprintf(string_buf, "%02d:%02d", tmpValue/60, tmpValue%60);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x23));
	tmpValue = HCS_Struct.Params[HCS_PARAM_YFQC];
	sprintf(string_buf, "%02d:%02d", tmpValue/60, tmpValue%60);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x24));
	tmpValue = HCS_Struct.Params[HCS_PARAM_YLSJ];
	sprintf(string_buf, "%02d:%02d", tmpValue/60, tmpValue%60);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x25));
	tmpValue = HCS_Struct.Params[HCS_PARAM_YRSJ];
	sprintf(string_buf, "%02d:%02d", tmpValue/60, tmpValue%60);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x26));
	tmpValue = HCS_Struct.Params[HCS_PARAM_YRSJ];
	sprintf(string_buf, "%02d:%02d", tmpValue/60, tmpValue%60);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x27));
	tmpValue = HCS_Struct.Params[HCS_PARAM_DHSJ];
	sprintf(string_buf, "%02d:%02d", tmpValue/60, tmpValue%60);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x28));
	tmpValue = HCS_Struct.Params[HCS_PARAM_JLSJ];
	sprintf(string_buf, "%02d:%02d", tmpValue/60, tmpValue%60);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x29));
	tmpValue = HCS_Struct.Params[HCS_PARAM_TLSJ];
	sprintf(string_buf, "%02d:%02d", tmpValue/60, tmpValue%60);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x2A));
	tmpValue = HCS_Struct.Params[HCS_PARAM_GFHC];
	sprintf(string_buf, "%02d:%02d", tmpValue/60, tmpValue%60);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x2B));
	tmpValue = HCS_Struct.Params[HCS_PARAM_YFHC];
	sprintf(string_buf, "%02d:%02d", tmpValue/60, tmpValue%60);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x2C));
	tmpValue = HCS_Struct.Params[HCS_PARAM_BHSL];
	sprintf(string_buf, "%02d:%02d", tmpValue/60, tmpValue%60);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x2D));
	sprintf(string_buf, "%03d", HCS_Struct.Params[HCS_PARAM_BHTL]);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x2E));
	sprintf(string_buf, "%03d", HCS_Struct.Params[HCS_PARAM_KJWD]);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x2F));
	sprintf(string_buf, "%03d", HCS_Struct.Params[HCS_PARAM_BHWD]);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x30));
	sprintf(string_buf, "%03d", HCS_Struct.Params[HCS_PARAM_KBWD]);
	TEXT_SetText(hItem, string_buf);
	
	hItem = WM_GetDialogItem(wm_config, (GUI_ID_USER + 0x31));
	sprintf(string_buf, "%03d", HCS_Struct.Params[HCS_PARAM_TBWD]);
	TEXT_SetText(hItem, string_buf);
}

void static UI_ShowStartupLogo(void)
{
	/*显示   易暖科技 */
	GUI_SetBkColor(GUI_WHITE);
	GUI_SetColor(GUI_BLUE);
	GUI_Clear();
	
	GUI_SetFont(&GUI_FontCNFonts_StartupLog);
	GUI_DispStringAt("\xe6\x98\x93\xe6\x9a\x96\xe7\xa7\x91\xe6\x8a\x80", 150,100);
	
	GUI_SetFont(GUI_FONT_32B_ASCII);
	GUI_Delay(200);
	GUI_DispStringAt("Y", 160, 160);
	GUI_Delay(50);
	GUI_DispString("i");
	GUI_Delay(50);
	GUI_DispString(" ");
	GUI_Delay(50);
	GUI_DispString("N");
	GUI_Delay(50);
	GUI_DispString("u");
	GUI_Delay(50);
	GUI_DispString("a");
	GUI_Delay(50);
	GUI_DispString("n");
	GUI_Delay(50);
	GUI_DispString(" ");
	GUI_Delay(50);
	GUI_DispString("K");
	GUI_Delay(50);
	GUI_DispString("e");
	GUI_Delay(50);
	GUI_DispString(" ");
	GUI_Delay(50);
	GUI_DispString("J");
	GUI_Delay(50);
	GUI_DispString("i");
}

void static UI_Init(void)
{
	uint32_t Qv;
	uint32_t Qr;
	
	GUI_Init();
	GUI_Clear();
	
	GUI_UC_SetEncodeUTF8();
	
	GUI_SetFont(GUI_FONT_8X8_ASCII);
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
	//do
	//{
	//	uint32_t tmpBMP_Index = 0;
	//	
	//	GUI_BMP_DrawEx(GetUISourceData, &tmpBMP_Index, 100, 100);
	//	
	//	GUI_BMP_DrawScaledEx(GetUISourceData, &tmpBMP_Index, 100, 200, 2, 1);
	//}while(0);
	
	//GUI_Delay(4000);
	
	UI_ShowStartupLogo();
	GUI_Delay(5000);
}

typedef struct {
  int xSize, ySize;
  int xPart, yPart;
  int xPos, yPos;
  int Dir;
  int Size;
  int ObjectSize;
} ANIM_DATA;

static GUI_ANIM_HANDLE ani_handle;
static ANIM_DATA ani_data;
static void _SliceInfo(int State, void * pVoid)
{
  GUI_USE_PARA(pVoid);
  switch (State)
	{
		case GUI_ANIM_START:
			GUI_MULTIBUF_Begin();
			break;
		case GUI_ANIM_END:
			GUI_MULTIBUF_End();
			break;
  }
}
static void _AnimDraw1(GUI_ANIM_INFO * pInfo, void * pVoid) {
  ANIM_DATA *pData;
  static int xPosOld;
	WM_HWIN wm_old;

  //_PrepareDrawing(pInfo, pVoid, &pData, xPosOld, 0);
	pData = &ani_data;
	ani_data.xPos = 10;
	ani_data.yPos = 20;
	ani_data.ObjectSize = 100;
	GUI_Exec();
	wm_old = WM_SelectWindow(wm_main);
  GUI_DrawPie(110,100, 10,  0,180, 0);
	GUI_DrawPie( 90,100, 10,180,360, 0);
	GUI_DrawPie(100, 90, 10, 90,270, 0);
	GUI_DrawPie(100,110, 10,270,450, 0);
	GUI_DrawArc(100,100,20,20,0,360);
  xPosOld = pData->xPos;
	WM_SelectWindow(wm_old);
}
static void _AnimDraw2(GUI_ANIM_INFO * pInfo, void * pVoid) {
  ANIM_DATA *pData;
  static int xPosOld;
	WM_HWIN wm_old;

  //_PrepareDrawing(pInfo, pVoid, &pData, xPosOld, 0);
	pData = &ani_data;
	ani_data.xPos = 10;
	ani_data.yPos = 20;
	ani_data.ObjectSize = 100;
	GUI_Exec();
	wm_old = WM_SelectWindow(wm_main);
  GUI_DrawPie(110,100, 10,  0,180, 0);
	GUI_DrawPie( 90,100, 10,180,360, 0);
	GUI_DrawPie(200, 90, 10, 90,270, 0);
	GUI_DrawPie(100,110, 10,270,450, 0);
	GUI_DrawArc(100,100,20,20,0,360);
  xPosOld = pData->xPos;
	WM_SelectWindow(wm_old);
}
static void _AnimDraw3(GUI_ANIM_INFO * pInfo, void * pVoid) {
  ANIM_DATA *pData;
  static int xPosOld;
	WM_HWIN wm_old;

  //_PrepareDrawing(pInfo, pVoid, &pData, xPosOld, 0);
	pData = &ani_data;
	ani_data.xPos = 10;
	ani_data.yPos = 20;
	ani_data.ObjectSize = 100;
	GUI_Exec();
	wm_old = WM_SelectWindow(wm_main);
  GUI_DrawPie(110,100, 10,  0,180, 0);
	GUI_DrawPie( 90,100, 10,180,360, 0);
	GUI_DrawPie(100, 90, 10, 90,270, 0);
	GUI_DrawPie(100,110, 10,270,450, 0);
	GUI_DrawArc(100,100,20,20,0,360);
  xPosOld = pData->xPos;
	WM_SelectWindow(wm_old);
}
void UI_MainAnimation_Update(void)
{
	static unsigned int IsInit = 0;
	
	if(!IsInit)
	{
		ani_handle = GUI_ANIM_Create(3000, 200, &ani_data, _SliceInfo);
		if(!ani_handle)
		{
			while(1);
		}
		GUI_ANIM_AddItem(ani_handle,    0, 1000, ANIM_ACCEL, &ani_data, _AnimDraw1);
		GUI_ANIM_AddItem(ani_handle, 1000, 2000, ANIM_ACCEL, &ani_data, _AnimDraw2);
		GUI_ANIM_AddItem(ani_handle, 2000, 3000, ANIM_ACCEL, &ani_data, _AnimDraw3);
		GUI_ANIM_Start(ani_handle);
		IsInit = 1;
	}
	if(GUI_ANIM_Exec(ani_handle) != 0)
	{
		GUI_ANIM_Start(ani_handle);
	}
}

void UI_MainShow(void)
{
	uint32_t tmpBMP_Index = 0;
	WM_HWIN wm_old;
	
	GUI_Exec();
	
	wm_old = WM_SelectWindow(wm_main);
	GUI_BMP_DrawEx(GetUISourceData, &tmpBMP_Index, 10, 50);
	
	WM_SelectWindow(wm_old);
}

void vTask_UI( void *pvParameters )
{
	unsigned int UI_Tick = 0;
	UI_Init();

	wm_main = CreateWindow_Main();
	wm_config = CreateWindow_Config();
	WM_HideWindow(wm_config);
	
	uint32_t iTime=0;
	CslRTC_Time ui_time;
	CslRTC_Date ui_date;
	
	uint8_t Last_UI_Mode = UI_Mode;
	UI_MainShow();
	
	while(1)
	{
		if(Last_UI_Mode != UI_Mode)    //UI Frames switch
		{
			Last_UI_Mode = UI_Mode;
			switch(UI_Mode)
			{
				case 0:
					WM_HideWindow(wm_config);
					WM_ShowWindow(wm_main);
					UI_MainShow();
					WM_SetFocus(wm_main);
					break;
				case 1:
					WM_HideWindow(wm_main);
					WM_ShowWindow(wm_config);
					WM_SetFocus(wm_config);
					break;
			}
		}
		if(UI_Tick % 10 == 0)
		{
			CslRTC_GetTime(&ui_time);
			CslRTC_GetDate(&ui_date);
			sprintf(string_buf, "%4d/%2d/%2d  %02d:%02d:%02d",ui_date.Year, ui_date.Month, ui_date.Date, ui_time.Hou, ui_time.Min, ui_time.Sec);
			hItem = WM_GetDialogItem(wm_main, (GUI_ID_USER + 0x03));
			TEXT_SetText(hItem, string_buf);
		}
		if(UI_Tick % 10 == 0)
		{
			switch(UI_Mode)
			{
				case 0:
					UI_Main_StatusUpdate();  //Main Frame
					break;
				case 1:
					UI_Config_Update();
					break;
			}
		}
		if(UI_Tick % 5 == 0)
		{
			//UI_MainAnimation_Update();
		}
		UI_Tick++;
		GUI_Delay(50);
	}
}
