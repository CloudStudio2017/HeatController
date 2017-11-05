#include "ui_FrmConfig1.h"
#include "myButton.h"
#include "sysParams.h"
#include "stdio.h"
#include "myBeep.h"

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
	
	};

CS_FRAME(FrmConfig1, NULL, 0, 0, 480, 320, CSUI_BLACK, FrmConfig1_ChildTbl);

#define CONFIG1_CURSOR_MAX         (11)
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
}

void ui_FrmConfig1_UpdateEdit(uint8_t Cursor, int8_t IncValue)
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
			SysParam_ValueLimitTime16(&SysParam.Dinshikaiji);
			break;
		case 11:
			SysParam.Dinshiguanji += IncValue;
			SysParam_ValueLimitTime16(&SysParam.Dinshiguanji);
			break;
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
