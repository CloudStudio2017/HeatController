#include "ui_FrmConfig1.h"
#include "myButton.h"
#include "sysParams.h"
#include "stdio.h"
#include "myBeep.h"
#include "cslRTC.h"

#define CONFIG1_KEY_SET_INDEX    2
#define CONFIG1_KEY_UP_INDEX     3
#define CONFIG1_KEY_DOWN_INDEX   4
#define CONFIG1_KEY_LEFT_INDEX   5
#define CONFIG1_KEY_RIGHT_INDEX  6

static char ui_FrmConfig1_Str_Yuliaoshijian[]   = "00:00";
static char ui_FrmConfig1_Str_Dianhuoshijian[]  = "00:00";
static char ui_FrmConfig1_Str_Jinliaoshijian[]  = "00:00";
static char ui_FrmConfig1_Str_Tingliaoshijian[] = "00:00";
static char ui_FrmConfig1_Str_Baohuosongliao[]  = "00:00";
static char ui_FrmConfig1_Str_Baohuotingliao[]  = "00:00";
static char ui_FrmConfig1_Str_Kaijiwendu[]      = "100";
static char ui_FrmConfig1_Str_Baohuowendu[]     = "400";
static char ui_FrmConfig1_Str_Gufenghouchui[]   = "00:00";
static char ui_FrmConfig1_Str_Yinfenghouchui[]  = "00:00";
static char ui_FrmConfig1_Str_Dinshikaiji[]     = "00:00";
static char ui_FrmConfig1_Str_Dinshiguanji[]    = "00:00";

static char ui_FrmConfig1_Str_Year[]            = "2017";
static char ui_FrmConfig1_Str_Month[]           = "11";
static char ui_FrmConfig1_Str_Date[]            = "11";
static char ui_FrmConfig1_Str_Hour[]            = "00";
static char ui_FrmConfig1_Str_Minute[]          = "00";

CS_BITMAP(Bmp_Cfg_Title1,                     NULL, 150, 10,  10, 10, CSUI_WHITE, CSUI_BLACK, xBitmapXitongshezhi);

CS_BITMAP(Bmp_Cfg_YuliaoshijianTitle,        NULL, 10, 10+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Yuliaoshijian);
CS_LABLE(Lable_Cfg_YuliaoshijianValue,       NULL,150, 15+60, 10, 10, CSUI_WHITE, CSUI_BLACK, ui_FrmConfig1_Str_Yuliaoshijian, NULL);
CS_BITMAP(Bmp_Cfg_DianhuoshijianTitle,       NULL, 10, 40+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Dianhuoshijian);
CS_LABLE(Lable_Cfg_DianhuoshijianValue,      NULL,150, 45+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Dianhuoshijian, NULL);
CS_BITMAP(Bmp_Cfg_JinliaoshijianTitle,       NULL, 10, 70+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Jinliaoshijian);
CS_LABLE(Lable_Cfg_JinliaoshijianValue,      NULL,150, 75+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Jinliaoshijian, NULL);
CS_BITMAP(Bmp_Cfg_TingliaoshijianTitle,      NULL, 10,100+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Tingliaoshijian);
CS_LABLE(Lable_Cfg_TingliaoshijianValue,     NULL,150,105+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Tingliaoshijian, NULL);
CS_BITMAP(Bmp_Cfg_BaohuosongliaoTitle,       NULL, 10,130+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Baohuosongliao);
CS_LABLE(Lable_Cfg_BaohuosongliaoValue,      NULL,150,135+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Baohuosongliao, NULL);
CS_BITMAP(Bmp_Cfg_BaohuotingliaoTitle,       NULL, 10,160+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Baohuotingliao);
CS_LABLE(Lable_Cfg_BaohuotingliaoValue,      NULL,150,165+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Baohuotingliao, NULL);

CS_BITMAP(Bmp_Cfg_KaijiwenduTitle,           NULL,250, 10+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Kaijiwendu);
CS_LABLE(Lable_Cfg_KaijiwenduValue,          NULL,390, 15+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Kaijiwendu, NULL);
CS_BITMAP(Bmp_Cfg_BaohuowenduTitle,          NULL,250, 40+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Baohuowendu);
CS_LABLE(Lable_Cfg_BaohuowenduValue,         NULL,390, 45+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Baohuowendu, NULL);

CS_BITMAP(Bmp_Cfg_GufenghouchuiTitle,        NULL,250, 70+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Gufenghouchui);
CS_LABLE(Lable_Cfg_GufenghuochuiValue,       NULL,390, 75+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Gufenghouchui, NULL);
CS_BITMAP(Bmp_Cfg_YinfenghouchuiTitle,       NULL,250,100+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Yinfenghouchui);
CS_LABLE(Lable_Cfg_YinfenghouchuiValue,      NULL,390,105+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Yinfenghouchui, NULL);
CS_BITMAP(Bmp_Cfg_DinshikaijiTitle,          NULL,250,130+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Dinshikaiji);
CS_LABLE(Lable_Cfg_DinshikaijiValue,         NULL,390,135+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Dinshikaiji, NULL);
CS_BITMAP(Bmp_Cfg_DinshiguanjiTitle,         NULL,250,160+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Dinshigunaji);
CS_LABLE(Lable_Cfg_DinshiguanjiValue,        NULL,390,165+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Dinshiguanji, NULL);

CS_LABLE(Lable_Cfg_YearValue,                NULL, 80,255,10,10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Year, NULL);
CS_BITMAP(Bmp_Cfg_YearTitile,                NULL,130,250,10,10, CSUI_BLUE, CSUI_BLACK, xBmpData_Nian);
CS_LABLE(Lable_Cfg_MonthValue,               NULL,165,255,10,10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Month, NULL);
CS_BITMAP(Bmp_Cfg_MonthTitile,               NULL,190,250,10,10, CSUI_BLUE, CSUI_BLACK, xBmpData_Yue);
CS_LABLE(Lable_Cfg_DateValue,                NULL,225,255,10,10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Date, NULL);
CS_BITMAP(Bmp_Cfg_DateTitile,                NULL,250,250,10,10, CSUI_BLUE, CSUI_BLACK, xBmpData_Ri);
CS_LABLE(Lable_Cfg_HourValue,                NULL,285,255,10,10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Hour, NULL);
CS_BITMAP(Bmp_Cfg_HourTitile,                NULL,310,250,10,10, CSUI_BLUE, CSUI_BLACK, xBmpData_Shi);
CS_LABLE(Lable_Cfg_MinuteValue,              NULL,345,255,10,10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig1_Str_Minute, NULL);
CS_BITMAP(Bmp_Cfg_MinuteTitile,              NULL,370,250,10,10, CSUI_BLUE, CSUI_BLACK, xBmpData_Fen);

TCsUI_BaseObjectTable FrmConfig1_ChildTbl[]={
	&Bmp_Cfg_Title1.Obj,
	&Bmp_Cfg_YuliaoshijianTitle.Obj, &Lable_Cfg_YuliaoshijianValue.Obj,
	&Bmp_Cfg_DianhuoshijianTitle.Obj, &Lable_Cfg_DianhuoshijianValue.Obj,
	&Bmp_Cfg_JinliaoshijianTitle.Obj, &Lable_Cfg_JinliaoshijianValue.Obj,
	&Bmp_Cfg_TingliaoshijianTitle.Obj, &Lable_Cfg_TingliaoshijianValue.Obj,
	&Bmp_Cfg_BaohuosongliaoTitle.Obj, &Lable_Cfg_BaohuosongliaoValue.Obj,
	&Bmp_Cfg_BaohuotingliaoTitle.Obj, &Lable_Cfg_BaohuotingliaoValue.Obj,
	
	&Bmp_Cfg_KaijiwenduTitle.Obj, &Lable_Cfg_KaijiwenduValue.Obj,
	&Bmp_Cfg_BaohuowenduTitle.Obj, &Lable_Cfg_BaohuowenduValue.Obj,
	&Bmp_Cfg_GufenghouchuiTitle.Obj, &Lable_Cfg_GufenghuochuiValue.Obj,
	&Bmp_Cfg_YinfenghouchuiTitle.Obj, &Lable_Cfg_YinfenghouchuiValue.Obj,
	&Bmp_Cfg_DinshikaijiTitle.Obj, &Lable_Cfg_DinshikaijiValue.Obj,
	&Bmp_Cfg_DinshiguanjiTitle.Obj, &Lable_Cfg_DinshiguanjiValue.Obj,
	
	&Bmp_Cfg_YearTitile.Obj, &Lable_Cfg_YearValue.Obj,
	&Bmp_Cfg_MonthTitile.Obj, &Lable_Cfg_MonthValue.Obj,
	&Bmp_Cfg_DateTitile.Obj, &Lable_Cfg_DateValue.Obj,
	&Bmp_Cfg_HourTitile.Obj, &Lable_Cfg_HourValue.Obj,
	&Bmp_Cfg_MinuteTitile.Obj, &Lable_Cfg_MinuteValue.Obj,
	
	};

CS_FRAME(FrmConfig1, NULL, 0, 0, 480, 320, CSUI_BLACK, FrmConfig1_ChildTbl);

#define CONFIG1_CURSOR_MAX         (16)
volatile static uint8_t ui_FrmConfig1_Cursor = 0;
volatile static uint8_t ui_FrmConfig1_EditUpdateFlag = 0;

void ui_FrmConfig1_SelectEdit(uint8_t Cursor);
void ui_FrmConfig1_UpdateEdit(uint8_t Cursor, int8_t IncValue);
void ui_FrmConfig1_KeyProcess_Up(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmConfig1_KeyProcess_Down(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmConfig1_KeyProcess_Left(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmConfig1_KeyProcess_Right(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmConfig1_KeyProcess_Set(uint8_t BtnHandle, uint8_t BtnState);

void ui_FrmConfig1_Init(void)
{
	Lable_Cfg_YuliaoshijianValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_DianhuoshijianValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_JinliaoshijianValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_TingliaoshijianValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_BaohuosongliaoValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_BaohuotingliaoValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_KaijiwenduValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_BaohuowenduValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_GufenghuochuiValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_YinfenghouchuiValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_DinshikaijiValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_DinshiguanjiValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_YearValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_MonthValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_DateValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_HourValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_MinuteValue.Font = CsUI_Font_ASCII_1218;
}

void ui_FrmConfig1_ShowFrame(void)
{
	//Config1 frame redraw
	FrmConfig1.Obj.Draw(&FrmConfig1);
}

void ui_FrmConfig1_Process(void)
{
	static uint8_t ui_FrmConfig1_Cursor_Old = -1;
	
	ui_FrmConfig1_Cursor = 0;
	ui_FrmConfig1_UpdateEdit(0, 0);
	ui_FrmConfig1_UpdateEdit(1, 0);
	ui_FrmConfig1_UpdateEdit(2, 0);
	ui_FrmConfig1_UpdateEdit(3, 0);
	ui_FrmConfig1_UpdateEdit(4, 0);
	ui_FrmConfig1_UpdateEdit(5, 0);
	ui_FrmConfig1_UpdateEdit(6, 0);
	ui_FrmConfig1_UpdateEdit(7, 0);
	ui_FrmConfig1_UpdateEdit(8, 0);
	ui_FrmConfig1_UpdateEdit(9, 0);
	ui_FrmConfig1_UpdateEdit(10, 0);
	ui_FrmConfig1_UpdateEdit(11, 0);
	ui_FrmConfig1_UpdateEdit(12, 0);
	ui_FrmConfig1_UpdateEdit(13, 0);
	ui_FrmConfig1_UpdateEdit(14, 0);
	ui_FrmConfig1_UpdateEdit(15, 0);
	ui_FrmConfig1_UpdateEdit(16, 0);
	ui_FrmConfig1_SelectEdit(ui_FrmConfig1_Cursor);
	
	MyButton_ReLinkCallBack(CONFIG1_KEY_SET_INDEX, ui_FrmConfig1_KeyProcess_Set);
	MyButton_ReLinkCallBack(CONFIG1_KEY_UP_INDEX, ui_FrmConfig1_KeyProcess_Up);
	MyButton_ReLinkCallBack(CONFIG1_KEY_DOWN_INDEX, ui_FrmConfig1_KeyProcess_Down);
	MyButton_ReLinkCallBack(CONFIG1_KEY_LEFT_INDEX, ui_FrmConfig1_KeyProcess_Left);
	MyButton_ReLinkCallBack(CONFIG1_KEY_RIGHT_INDEX, ui_FrmConfig1_KeyProcess_Right);
	
	while(1)
	{
		if(UI_Index != 1)
		{
			return;
		}
		if(ui_FrmConfig1_Cursor_Old != ui_FrmConfig1_Cursor)
		{
			ui_FrmConfig1_SelectEdit(ui_FrmConfig1_Cursor);
			ui_FrmConfig1_Cursor_Old = ui_FrmConfig1_Cursor;
		}
		if(ui_FrmConfig1_EditUpdateFlag)
		{
			ui_FrmConfig1_SelectEdit(ui_FrmConfig1_Cursor);
			ui_FrmConfig1_EditUpdateFlag = 0;
		}
	}
}

void ui_FrmConfig1_SelectEdit(uint8_t Cursor)
{
	Lable_Cfg_YuliaoshijianValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_DianhuoshijianValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_JinliaoshijianValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_TingliaoshijianValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_BaohuosongliaoValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_BaohuotingliaoValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_KaijiwenduValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_BaohuowenduValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_GufenghuochuiValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_YinfenghouchuiValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_DinshikaijiValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_DinshiguanjiValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_YearValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_MonthValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_DateValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_HourValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_MinuteValue.FrontColor = CSUI_BLUE;
	switch(Cursor)
	{
		case 0: Lable_Cfg_YuliaoshijianValue.FrontColor = CSUI_WHITE; break;
		case 1: Lable_Cfg_DianhuoshijianValue.FrontColor = CSUI_WHITE; break;
		case 2: Lable_Cfg_JinliaoshijianValue.FrontColor = CSUI_WHITE; break;
		case 3: Lable_Cfg_TingliaoshijianValue.FrontColor = CSUI_WHITE; break;
		case 4: Lable_Cfg_BaohuosongliaoValue.FrontColor = CSUI_WHITE; break;
		case 5: Lable_Cfg_BaohuotingliaoValue.FrontColor = CSUI_WHITE; break;
		case 6: Lable_Cfg_KaijiwenduValue.FrontColor = CSUI_WHITE; break;
		case 7: Lable_Cfg_BaohuowenduValue.FrontColor = CSUI_WHITE; break;
		case 8: Lable_Cfg_GufenghuochuiValue.FrontColor = CSUI_WHITE; break;
		case 9: Lable_Cfg_YinfenghouchuiValue.FrontColor = CSUI_WHITE; break;
		case 10: Lable_Cfg_DinshikaijiValue.FrontColor = CSUI_WHITE; break;
		case 11: Lable_Cfg_DinshiguanjiValue.FrontColor = CSUI_WHITE; break;
		case 12: Lable_Cfg_YearValue.FrontColor = CSUI_WHITE; break;
		case 13: Lable_Cfg_MonthValue.FrontColor = CSUI_WHITE; break;
		case 14: Lable_Cfg_DateValue.FrontColor = CSUI_WHITE; break;
		case 15: Lable_Cfg_HourValue.FrontColor = CSUI_WHITE; break;
		case 16: Lable_Cfg_MinuteValue.FrontColor = CSUI_WHITE; break;
	}
	
	Lable_Cfg_YuliaoshijianValue.Obj.Draw(&Lable_Cfg_YuliaoshijianValue);
	Lable_Cfg_DianhuoshijianValue.Obj.Draw(&Lable_Cfg_DianhuoshijianValue);
	Lable_Cfg_JinliaoshijianValue.Obj.Draw(&Lable_Cfg_JinliaoshijianValue);
	Lable_Cfg_TingliaoshijianValue.Obj.Draw(&Lable_Cfg_TingliaoshijianValue);
	Lable_Cfg_BaohuosongliaoValue.Obj.Draw(&Lable_Cfg_BaohuosongliaoValue);
	Lable_Cfg_BaohuotingliaoValue.Obj.Draw(&Lable_Cfg_BaohuotingliaoValue);
	Lable_Cfg_KaijiwenduValue.Obj.Draw(&Lable_Cfg_KaijiwenduValue);
	Lable_Cfg_BaohuowenduValue.Obj.Draw(&Lable_Cfg_BaohuowenduValue);
	Lable_Cfg_GufenghuochuiValue.Obj.Draw(&Lable_Cfg_GufenghuochuiValue);
	Lable_Cfg_YinfenghouchuiValue.Obj.Draw(&Lable_Cfg_YinfenghouchuiValue);
	Lable_Cfg_DinshikaijiValue.Obj.Draw(&Lable_Cfg_DinshikaijiValue);
	Lable_Cfg_DinshiguanjiValue.Obj.Draw(&Lable_Cfg_DinshiguanjiValue);
	Lable_Cfg_YearValue.Obj.Draw(&Lable_Cfg_YearValue);
	Lable_Cfg_MonthValue.Obj.Draw(&Lable_Cfg_MonthValue);
	Lable_Cfg_DateValue.Obj.Draw(&Lable_Cfg_DateValue);
	Lable_Cfg_HourValue.Obj.Draw(&Lable_Cfg_HourValue);
	Lable_Cfg_MinuteValue.Obj.Draw(&Lable_Cfg_MinuteValue);
}

void ui_FrmConfig1_UpdateEdit(uint8_t Cursor, int8_t IncValue)
{
	uint8_t tmpTimeData;
	CslRTC_Date tmpDate;
	CslRTC_Time tmpTime;
	
	if(IncValue != 0)
	{
		switch(Cursor)
		{
			case 0:
				SysParam.Yuliaoshijian += IncValue;
				SysParam_ValueLimitTime16(&SysParam.Yuliaoshijian);
				break;
			case 1:
				SysParam.Dianhuoshijian += IncValue;
				SysParam_ValueLimitTime16(&SysParam.Dianhuoshijian);
				break;
			case 2:
				SysParam.Jinliaoshijian += IncValue;
				SysParam_ValueLimitTime16(&SysParam.Jinliaoshijian);
				break;
			case 3:
				SysParam.Tingliaoshijian += IncValue;
				SysParam_ValueLimitTime16(&SysParam.Tingliaoshijian);
				break;
			case 4:
				SysParam.Baohuosongliao += IncValue;
				SysParam_ValueLimitTime16(&SysParam.Baohuosongliao);
				break;
			case 5:
				SysParam.Baohuotingliao += IncValue;
				SysParam_ValueLimitTime16(&SysParam.Baohuotingliao);
				break;
			case 6:
				SysParam.Kaijiwendu += IncValue;
				SysParam_ValueLimitTemp16(&SysParam.Kaijiwendu);
				break;
			case 7:
				SysParam.Baohuowendu += IncValue;
				SysParam_ValueLimitTemp16(&SysParam.Baohuowendu);
				break;
			case 8:
				SysParam.Gufenghouchui += IncValue;
				SysParam_ValueLimitTime16(&SysParam.Gufenghouchui);
				break;
			case 9:
				SysParam.Yinfenghouchui += IncValue;
				SysParam_ValueLimitTime16(&SysParam.Yinfenghouchui);
				break;
			case 10:
				SysParam.Dinshikaiji += IncValue;
				SysParam_ValueLimit24Hour(&SysParam.Dinshikaiji);
				break;
			case 11:
				SysParam.Dinshiguanji += IncValue;
				SysParam_ValueLimit24Hour(&SysParam.Dinshiguanji);
				break;
			case 12:
				CslRTC_GetDate(&tmpDate);
				tmpDate.Year += IncValue;
				if(tmpDate.Year > 2050)
					tmpDate.Year = 2000;
				if(tmpDate.Year < 2000)
					tmpDate.Year = 2050;
				CslRTC_SetDate(&tmpDate);
				break;
			case 13:
				CslRTC_GetDate(&tmpDate);
				tmpDate.Month += IncValue;
				if(tmpDate.Month > 12)
					tmpDate.Month = 1;
				if(tmpDate.Month < 1)
					tmpDate.Month = 12;
				CslRTC_SetDate(&tmpDate);
				break;
			case 14:
				CslRTC_GetDate(&tmpDate);
				tmpDate.Date += IncValue;
				switch(tmpDate.Month)
				{
					case 1:
					case 3:
					case 5:
					case 7:
					case 8:
					case 10:
					case 12:
						if(tmpDate.Date > 31)
							tmpDate.Date = 1;
						if(tmpDate.Date < 1)
							tmpDate.Date = 31;
						break;
					case 2:
						if(tmpDate.Date > 28)
							tmpDate.Date = 1;
						if(tmpDate.Date < 1)
							tmpDate.Date = 28;
						break;
					case 4:
					case 6:
					case 9:
					case 11:
						if(tmpDate.Date > 30)
							tmpDate.Date = 1;
						if(tmpDate.Date < 1)
							tmpDate.Date = 30;
						break;
				}
				CslRTC_SetDate(&tmpDate);
				break;
			case 15:
				CslRTC_GetTime(&tmpTime);
				tmpTime.Hou += IncValue;
				if(tmpTime.Hou > 200)
					tmpTime.Hou = 23;
				if(tmpTime.Hou > 23)
					tmpTime.Hou = 0;
				CslRTC_SetTime(&tmpTime);
				break;
			case 16:
				CslRTC_GetTime(&tmpTime);
				tmpTime.Min += IncValue;
				if(tmpTime.Min > 200)
					tmpTime.Min = 59;
				if(tmpTime.Min > 59)
					tmpTime.Min = 0;
				CslRTC_SetTime(&tmpTime);
				break;
		}
	}
	switch(Cursor)
	{
		case 0: sprintf(ui_FrmConfig1_Str_Yuliaoshijian, "%02d:%02d", SysParam.Yuliaoshijian / 60, SysParam.Yuliaoshijian % 60); break;
		case 1: sprintf(ui_FrmConfig1_Str_Dianhuoshijian, "%02d:%02d", SysParam.Dianhuoshijian / 60, SysParam.Dianhuoshijian % 60);	break;
		case 2: sprintf(ui_FrmConfig1_Str_Jinliaoshijian, "%02d:%02d", SysParam.Jinliaoshijian / 60, SysParam.Jinliaoshijian % 60);	break;
		case 3: sprintf(ui_FrmConfig1_Str_Tingliaoshijian, "%02d:%02d", SysParam.Tingliaoshijian / 60, SysParam.Tingliaoshijian % 60);	break;
		case 4: sprintf(ui_FrmConfig1_Str_Baohuosongliao, "%02d:%02d", SysParam.Baohuosongliao / 60, SysParam.Baohuosongliao % 60);	break;
		case 5: sprintf(ui_FrmConfig1_Str_Baohuotingliao, "%02d:%02d", SysParam.Baohuotingliao / 60, SysParam.Baohuotingliao % 60);	break;
		case 6: sprintf(ui_FrmConfig1_Str_Kaijiwendu, "%03d", SysParam.Kaijiwendu);	break;
		case 7: sprintf(ui_FrmConfig1_Str_Baohuowendu, "%03d", SysParam.Baohuowendu);	break;
		case 8: sprintf(ui_FrmConfig1_Str_Gufenghouchui, "%02d:%02d", SysParam.Gufenghouchui / 60, SysParam.Gufenghouchui % 60);	break;
		case 9: sprintf(ui_FrmConfig1_Str_Yinfenghouchui, "%02d:%02d", SysParam.Yinfenghouchui / 60, SysParam.Yinfenghouchui % 60);	break;
		case 10: sprintf(ui_FrmConfig1_Str_Dinshikaiji, "%02d:%02d", SysParam.Dinshikaiji / 60, SysParam.Dinshikaiji % 60);	break;
		case 11: sprintf(ui_FrmConfig1_Str_Dinshiguanji, "%02d:%02d", SysParam.Dinshiguanji / 60, SysParam.Dinshiguanji % 60);	break;
		case 12: CslRTC_GetDate(&tmpDate); sprintf(ui_FrmConfig1_Str_Year, "%4d", tmpDate.Year); break;
		case 13: CslRTC_GetDate(&tmpDate); sprintf(ui_FrmConfig1_Str_Month, "%2d", tmpDate.Month); break;
		case 14: CslRTC_GetDate(&tmpDate); sprintf(ui_FrmConfig1_Str_Date, "%2d", tmpDate.Date); break;
		case 15: CslRTC_GetTime(&tmpTime); sprintf(ui_FrmConfig1_Str_Hour, "%02d", tmpTime.Hou); break;
		case 16: CslRTC_GetTime(&tmpTime); sprintf(ui_FrmConfig1_Str_Minute, "%02d", tmpTime.Min); break;
	}
}

void ui_FrmConfig1_KeyProcess_Up(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_PRESS)
		return;
	
	if(ui_FrmConfig1_Cursor == 0)
	{
		ui_FrmConfig1_Cursor = CONFIG1_CURSOR_MAX;
	}
	else
	{
		ui_FrmConfig1_Cursor--;
	}
}

void ui_FrmConfig1_KeyProcess_Down(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_PRESS)
		return;
	
	ui_FrmConfig1_Cursor++;
	if(ui_FrmConfig1_Cursor > CONFIG1_CURSOR_MAX)
	{
		ui_FrmConfig1_Cursor = 0;
	}
}

void ui_FrmConfig1_KeyProcess_Left(uint8_t BtnHandle, uint8_t BtnState)
{
	switch(BtnState)
	{
		case BUTTON_STATUS_RELEASE:
		case BUTTON_STATUS_HOLD:
			ui_FrmConfig1_UpdateEdit(ui_FrmConfig1_Cursor, -1);
			ui_FrmConfig1_EditUpdateFlag = 1;
			break;
	}
}

void ui_FrmConfig1_KeyProcess_Right(uint8_t BtnHandle, uint8_t BtnState)
{
	switch(BtnState)
	{
		case BUTTON_STATUS_RELEASE:
		case BUTTON_STATUS_HOLD:
			ui_FrmConfig1_UpdateEdit(ui_FrmConfig1_Cursor, +1);
			ui_FrmConfig1_EditUpdateFlag = 1;
			break;
	}
}

void ui_FrmConfig1_KeyProcess_Set(uint8_t BtnHandle, uint8_t BtnState)
{
	static uint8_t HoldSave = 0;
	
	switch(BtnState)
	{
		case BUTTON_STATUS_RELEASE:
			if(HoldSave)
			{
				//Enter the second config frame
				HoldSave = 0;
				UI_Index = 2;
				MyBeep_Beep(1);
				vTaskDelay(50);
				MyBeep_Beep(0);
				vTaskDelay(50);
				MyBeep_Beep(1);
				vTaskDelay(50);
				MyBeep_Beep(0);
				MyButton_ReLinkCallBack(CONFIG1_KEY_SET_INDEX, NULL);
			}
			else
			{
				//Return to main frame
				UI_Index = 0;
				SysParam_SaveToFlash();
				MyBeep_Beep(1);
				vTaskDelay(200);
				MyBeep_Beep(0);
			}
			break;
		case BUTTON_STATUS_HOLD:
			HoldSave = 1;
			break;
	}
}
