#include "ui_FrmMain.h"
#include "CslRTC.h"
#include "stdio.h"
#include "myButton.h"
#include "HeatControlSys.h"

#define MAIN_KEY_SET_INDEX    2
#define MAIN_KEY_UP_INDEX     3
#define MAIN_KEY_DOWN_INDEX   4
#define MAIN_KEY_LEFT_INDEX   5
#define MAIN_KEY_RIGHT_INDEX  6

static char str_date[11];
static char str_time[6];

CS_LABLE(Lable_Date, NULL, 240, 280, 140, 18, CSUI_WHITE, CSUI_BLACK, str_date, NULL);
CS_LABLE(Lable_Time, NULL, 380, 280,  80, 18, CSUI_WHITE, CSUI_BLACK, str_time, NULL);
CS_BITMAP(Bmp_SysStatusTitle,    NULL, 260, 10, 100, 30, CSUI_ORANGE, CSUI_DARKBLUE, xBmpData_SysStatus);
CS_BITMAP(Bmp_SysStatusState,    NULL, 400, 10,  60, 30, CSUI_GREEN, CSUI_DARKBLUE, xBmpData_Standby);

CS_BITMAP(Bmp_SongliaoTitle,     NULL, 320, 60,  80, 30, CSUI_ORANGE, CSUI_DARKBLUE, xBmpData_Songliao);
CS_BITMAP(Bmp_SongliaoState,     NULL, 400, 60,  60, 30, CSUI_RED, CSUI_DARKBLUE, xBmpData_Tingzhi);
CS_BITMAP(Bmp_DianhuoTitle,      NULL, 320,100,  80, 30, CSUI_ORANGE, CSUI_DARKBLUE, xBmpData_Dianhuo);
CS_BITMAP(Bmp_DianhuoState,      NULL, 400,100,  60, 30, CSUI_RED, CSUI_DARKBLUE, xBmpData_Tingzhi);
CS_BITMAP(Bmp_YinfengTitle,      NULL, 320,140,  80, 30, CSUI_ORANGE, CSUI_DARKBLUE, xBmpData_Yinfeng);
CS_BITMAP(Bmp_YinfengState,      NULL, 400,140,  60, 30, CSUI_RED, CSUI_DARKBLUE, xBmpData_Tingzhi);
CS_BITMAP(Bmp_GufengTitle,       NULL, 320,180,  80, 30, CSUI_ORANGE, CSUI_DARKBLUE, xBmpData_Gufeng);
CS_BITMAP(Bmp_GufengState,       NULL, 400,180,  60, 30, CSUI_RED, CSUI_DARKBLUE, xBmpData_Tingzhi);

CS_BITMAP(Bmp_BackPic,           NULL,  80, 80,  10, 10, CSUI_GREEN, CSUI_WHITE, xBitmapdata1);

TCsUI_BaseObjectTable FrmMain_ChildTbl[]={
	&Lable_Date.Obj, &Lable_Time.Obj,
	&Bmp_SysStatusTitle.Obj, &Bmp_SysStatusState.Obj,
	&Bmp_SongliaoTitle.Obj, &Bmp_SongliaoState.Obj,
	&Bmp_DianhuoTitle.Obj, &Bmp_DianhuoState.Obj,
	&Bmp_YinfengTitle.Obj, &Bmp_YinfengState.Obj,
	&Bmp_GufengTitle.Obj, &Bmp_GufengState.Obj,
	&Bmp_BackPic.Obj,
	};
CS_FRAME(FrmMain, NULL, 0, 0, 480, 320, CSUI_DARKBLUE, FrmMain_ChildTbl);


static CslRTC_Time xTime;
static CslRTC_Date xDate;

void ui_FrmMain_UpdateOutputStatus(void);
void ui_FrmMain_UpdateStatus(void);
void ui_FrmMain_KeyProcess_Set(uint8_t BtnHandle, uint8_t BtnState);

void ui_FrmMain_Init(void)
{
	Lable_Date.Parent = &FrmMain;
	Lable_Time.Parent = &FrmMain;
	Lable_Date.Font = CsUI_Font_ASCII_1218;
	Lable_Time.Font = CsUI_Font_ASCII_1218;
	
	
	//Update time string
	CslRTC_GetTime(&xTime);
	sprintf(str_time, "%02d:%02d", xTime.Hou, xTime.Min);
	//Update date string
	CslRTC_GetDate(&xDate);
	sprintf(str_date, "%4d/%02d/%02d", xDate.Year, xDate.Month, xDate.Date);
}

void ui_FrmMain_ShowFrame(void)
{
	//Main frame redraw
	FrmMain.Obj.Draw(&FrmMain);
}

void ui_FrmMain_UpdateTime(void)
{
	static uint8_t LastSec = 60;
	static uint8_t LastDate = 32;
	
	CslRTC_GetTime(&xTime);
	if(xTime.Sec != LastSec)
	{
		LastSec = xTime.Sec;
		if(LastSec % 2)
		{
			str_time[2] = ' ';
			Lable_Time.Obj.Draw(&Lable_Time);
		}
		else
		{
			str_time[2] = ':';
			Lable_Time.Obj.Draw(&Lable_Time);
		}
		if(LastSec == 0)
		{
			//Update time string
			sprintf(str_time, "%02d:%02d", xTime.Hou, xTime.Min);
			Lable_Time.Obj.Draw(&Lable_Time);
			
			CslRTC_GetDate(&xDate);
			if(xDate.Date !=  LastDate)
			{
				//Update date string
				LastDate = xDate.Date;
				sprintf(str_date, "%4d/%02d/%02d", xDate.Year, xDate.Month, xDate.Date);
				Lable_Date.Obj.Draw(&Lable_Date);
			}
		}
	}
}

void ui_FrmMain_Process(void)
{
	static uint32_t iCount = 0;
	
	MyButton_ReLinkCallBack(MAIN_KEY_SET_INDEX, ui_FrmMain_KeyProcess_Set);
	MyButton_ReLinkCallBack(MAIN_KEY_UP_INDEX, NULL);
	MyButton_ReLinkCallBack(MAIN_KEY_DOWN_INDEX, NULL);
	MyButton_ReLinkCallBack(MAIN_KEY_LEFT_INDEX, NULL);
	MyButton_ReLinkCallBack(MAIN_KEY_RIGHT_INDEX, NULL);
	
	while(1)
	{
		if(UI_Index != 0)
		{
			return;
		}
		ui_FrmMain_UpdateTime();
		ui_FrmMain_UpdateStatus();
		ui_FrmMain_UpdateOutputStatus();
		
		vTaskDelay(50);
	}
}

void ui_FrmMain_UpdateOutputStatus(void)
{
	if(HCS_Struct.MaterialMachine)
	{
		Bmp_SongliaoState.pBmp = (TBitmap_Head*)xBmpData_Yunxing;
		Bmp_SongliaoState.FrontColor = CSUI_GREEN;
	}
	else
	{
		Bmp_SongliaoState.pBmp = (TBitmap_Head*)xBmpData_Tingzhi;
		Bmp_SongliaoState.FrontColor = CSUI_RED;
	}
	if(HCS_Struct.FireUp)
	{
		Bmp_DianhuoState.pBmp = (TBitmap_Head*)xBmpData_Yunxing;
		Bmp_DianhuoState.FrontColor = CSUI_GREEN;
	}
	else
	{
		Bmp_DianhuoState.pBmp = (TBitmap_Head*)xBmpData_Tingzhi;
		Bmp_DianhuoState.FrontColor = CSUI_RED;
	}
	if(HCS_Struct.LeadFan)
	{
		Bmp_YinfengState.pBmp = (TBitmap_Head*)xBmpData_Yunxing;
		Bmp_YinfengState.FrontColor = CSUI_GREEN;
	}
	else
	{
		Bmp_YinfengState.pBmp = (TBitmap_Head*)xBmpData_Tingzhi;
		Bmp_YinfengState.FrontColor = CSUI_RED;
	}
	if(HCS_Struct.AirBlower)
	{
		Bmp_GufengState.pBmp = (TBitmap_Head*)xBmpData_Yunxing;
		Bmp_GufengState.FrontColor = CSUI_GREEN;
	}
	else
	{
		Bmp_GufengState.pBmp = (TBitmap_Head*)xBmpData_Tingzhi;
		Bmp_GufengState.FrontColor = CSUI_RED;
	}
	
	Bmp_SongliaoState.Obj.Draw(&Bmp_SongliaoState);
	Bmp_DianhuoState.Obj.Draw(&Bmp_DianhuoState);
	Bmp_YinfengState.Obj.Draw(&Bmp_YinfengState);
	Bmp_GufengState.Obj.Draw(&Bmp_GufengState);
}

void ui_FrmMain_UpdateStatus(void)
{
	static HCS_STATUS_enum Status_Save = -1;
	
	if(Status_Save == HCS_Struct.Status)
	{
		return;
	}
	Status_Save = HCS_Struct.Status;
	switch(HCS_Struct.Status)
	{
		case HCS_STATUS_STANDBY:
			Bmp_SysStatusState.pBmp = (TBitmap_Head*)xBmpData_Standby;
			break;
		case HCS_STATUS_PREBLOW:
			Bmp_SysStatusState.pBmp = (TBitmap_Head*)xBmpData_PreAir;
			break;
		case HCS_STATUS_PREMATERIAL:
			Bmp_SysStatusState.pBmp = (TBitmap_Head*)xBmpData_PreMat;
			break;
		case HCS_STATUS_WARMEDUP:
			Bmp_SysStatusState.pBmp = (TBitmap_Head*)xBmpData_PreHeat;
			break;
		case HCS_STATUS_FIREUP:
			Bmp_SysStatusState.pBmp = (TBitmap_Head*)xBmpData_Fire;
			break;
		case HCS_STATUS_RUNNING:
			Bmp_SysStatusState.pBmp = (TBitmap_Head*)xBmpData_Run;
			break;
		case HCS_STATUS_FIREPROTECT:
			Bmp_SysStatusState.pBmp = (TBitmap_Head*)xBmpData_KeepFire;
			break;
	}
	Bmp_SysStatusState.Obj.Draw(&Bmp_SysStatusState);
}

void ui_FrmMain_KeyProcess_Set(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		UI_Index = 1;
	}
}

