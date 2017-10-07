#include "ui_FrmMain.h"
#include "CslRTC.h"
#include "stdio.h"

static char str_date[11];
static char str_time[6];

CS_LABLE(Lable_Date, NULL, 240, 280, 140, 18, CSUI_WHITE, CSUI_BLACK, str_date, NULL);
CS_LABLE(Lable_Time, NULL, 380, 280,  80, 18, CSUI_WHITE, CSUI_BLACK, str_time, NULL);
CS_BITMAP(Bmp_SysStatusTitle,    NULL, 260, 10, 100, 30, CSUI_ORANGE, CSUI_BLACK, xBmpData_SysStatus);
CS_BITMAP(Bmp_SysStatusState,    NULL, 400, 10,  60, 30, CSUI_GREEN, CSUI_BLACK, xBmpData_Standby);

CS_BITMAP(Bmp_SongliaoTitle,     NULL, 320, 60,  80, 30, CSUI_GREEN, CSUI_BLACK, xBmpData_Songliao);
CS_BITMAP(Bmp_SongliaoState,     NULL, 400, 60,  60, 30, CSUI_RED, CSUI_BLACK, xBmpData_Tingzhi);
CS_BITMAP(Bmp_DianhuoTitle,      NULL, 320,100,  80, 30, CSUI_GREEN, CSUI_BLACK, xBmpData_Dianhuo);
CS_BITMAP(Bmp_DianhuoState,      NULL, 400,100,  60, 30, CSUI_RED, CSUI_BLACK, xBmpData_Tingzhi);
CS_BITMAP(Bmp_YinfengTitle,      NULL, 320,140,  80, 30, CSUI_GREEN, CSUI_BLACK, xBmpData_Yinfeng);
CS_BITMAP(Bmp_YinfengState,      NULL, 400,140,  60, 30, CSUI_RED, CSUI_BLACK, xBmpData_Tingzhi);
CS_BITMAP(Bmp_GufengTitle,       NULL, 320,180,  80, 30, CSUI_GREEN, CSUI_BLACK, xBmpData_Gufeng);
CS_BITMAP(Bmp_GufengState,       NULL, 400,180,  60, 30, CSUI_RED, CSUI_BLACK, xBmpData_Tingzhi);

TCsUI_BaseObjectTable FrmMain_ChildTbl[]={
	&Lable_Date.Obj, &Lable_Time.Obj,
	&Bmp_SysStatusTitle.Obj, &Bmp_SysStatusState.Obj,
	&Bmp_SongliaoTitle.Obj, &Bmp_SongliaoState.Obj,
	&Bmp_DianhuoTitle.Obj, &Bmp_DianhuoState.Obj,
	&Bmp_YinfengTitle.Obj, &Bmp_YinfengState.Obj,
	&Bmp_GufengTitle.Obj, &Bmp_GufengState.Obj,	
	};
CS_FRAME(FrmMain, NULL, 0, 0, 480, 320, CSUI_BLUE, FrmMain_ChildTbl);


static CslRTC_Time xTime;
static CslRTC_Date xDate;

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
	
	while(1)
	{
		if(UI_Index != 0)
		{
			return;
		}
		ui_FrmMain_UpdateTime();
	}
}


