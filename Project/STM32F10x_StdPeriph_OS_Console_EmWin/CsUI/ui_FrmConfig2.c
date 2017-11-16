#include "ui_FrmConfig2.h"
#include "myButton.h"
#include "sysParams.h"
#include "stdio.h"
#include "myBeep.h"

#define CONFIG2_KEY_SET_INDEX    2
#define CONFIG2_KEY_UP_INDEX     3
#define CONFIG2_KEY_DOWN_INDEX   4
#define CONFIG2_KEY_LEFT_INDEX   5
#define CONFIG2_KEY_RIGHT_INDEX  6

static char ui_FrmConfig2_Str_Gufengqianchui[]    = "00:00";
static char ui_FrmConfig2_Str_Yinfengqianchui[]   = "00:00";
static char ui_FrmConfig2_Str_Dianhuoyuzhi[]      = "100";
static char ui_FrmConfig2_Str_Yinfengzhihou[]     = "00:00";
static char ui_FrmConfig2_Str_Gufengzhihou[]      = "00:00";
static char ui_FrmConfig2_Str_Songliaozhihou[]    = "00:00";
static char ui_FrmConfig2_Str_Dianhuoyinfeng[]    = "100";
static char ui_FrmConfig2_Str_Dianhuogufeng[]     = "100";
static char ui_FrmConfig2_Str_Zhengchangyinfeng[] = "100";
static char ui_FrmConfig2_Str_Zhengchanggufeng[]  = "100";
static char ui_FrmConfig2_Str_Baohuoyinfeng[]     = "100";
static char ui_FrmConfig2_Str_Baohuogufeng[]      = "100";

CS_BITMAP(Bmp_Cfg_Title2,                     NULL, 150, 10,  10, 10, CSUI_WHITE, CSUI_BLACK, xBitmapXitongshezhi);

CS_BITMAP(Bmp_Cfg_GufengqianchuiTitle,       NULL, 10, 10+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Gufengqianchui);
CS_LABLE(Lable_Cfg_GufengqianchuiValue,      NULL,150, 15+60, 10, 10, CSUI_WHITE, CSUI_BLACK, ui_FrmConfig2_Str_Gufengqianchui, NULL);
CS_BITMAP(Bmp_Cfg_YinfengqianchuiTitle,      NULL, 10, 40+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Yinfengqianchui);
CS_LABLE(Lable_Cfg_YinfengqianchuiValue,     NULL,150, 45+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig2_Str_Yinfengqianchui, NULL);
CS_BITMAP(Bmp_Cfg_DianhuoyuzhiTitle,         NULL, 10, 70+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Dianhuoyuzhi);
CS_LABLE(Lable_Cfg_DianhuoyuzhiValue,        NULL,150, 75+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig2_Str_Dianhuoyuzhi, NULL);
CS_BITMAP(Bmp_Cfg_YinfengzhihouTitle,        NULL, 10,100+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Yinfengzhihou);
CS_LABLE(Lable_Cfg_YinfengzhihouValue,       NULL,150,105+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig2_Str_Yinfengzhihou, NULL);
CS_BITMAP(Bmp_Cfg_GufengzhihouTitle,         NULL, 10,130+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Gufengzhihou);
CS_LABLE(Lable_Cfg_GufengzhihhouValue,       NULL,150,135+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig2_Str_Gufengzhihou, NULL);
CS_BITMAP(Bmp_Cfg_SongliaozhihouTitle,       NULL, 10,160+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Songliaozhihou);
CS_LABLE(Lable_Cfg_SongliaozhihouValue,      NULL,150,165+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig2_Str_Songliaozhihou, NULL);

CS_BITMAP(Bmp_Cfg_DianhuoyinfengTitle,       NULL,250, 10+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Dianhuoyinfeng);
CS_LABLE(Lable_Cfg_DianhuoyinfengValue,      NULL,390, 15+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig2_Str_Dianhuoyinfeng, NULL);
CS_BITMAP(Bmp_Cfg_DianhuogufengTitle,        NULL,250, 40+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Dianhuogufeng);
CS_LABLE(Lable_Cfg_DianhuogufengValue,       NULL,390, 45+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig2_Str_Dianhuogufeng, NULL);
CS_BITMAP(Bmp_Cfg_ZhengchangyinfengTitle,    NU-LL,250, 70+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Zhengchangyinfeng);
CS_LABLE(Lable_Cfg_ZhengchangyinfengValue,   NULL,390, 75+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig2_Str_Zhengchangyinfeng, NULL);
CS_BITMAP(Bmp_Cfg_ZhengchanggufengTitle,     NULL,250,100+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Zhengchanggufeng);
CS_LABLE(Lable_Cfg_ZhengchanggufengValue,    NULL,390,105+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig2_Str_Zhengchanggufeng, NULL);
CS_BITMAP(Bmp_Cfg_BaohuoyinfengTitle,        NULL,250,130+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Baohuoyinfeng);
CS_LABLE(Lable_Cfg_BaohuoyinfengValue,       NULL,390,135+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig2_Str_Baohuoyinfeng, NULL);
CS_BITMAP(Bmp_Cfg_BaohuogufengTitle,         NULL,250,160+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Baohuogufeng);
CS_LABLE(Lable_Cfg_BaohuogufengValue,        NULL,390,165+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmConfig2_Str_Baohuogufeng, NULL);

TCsUI_BaseObjectTable FrmConfig2_ChildTbl[]={
	&Bmp_Cfg_Title2.Obj,
	&Bmp_Cfg_GufengqianchuiTitle.Obj, &Lable_Cfg_GufengqianchuiValue.Obj,
	&Bmp_Cfg_YinfengqianchuiTitle.Obj, &Lable_Cfg_YinfengqianchuiValue.Obj,
	&Bmp_Cfg_DianhuoyuzhiTitle.Obj, &Lable_Cfg_DianhuoyuzhiValue.Obj,
	&Bmp_Cfg_YinfengzhihouTitle.Obj, &Lable_Cfg_YinfengzhihouValue.Obj,
	&Bmp_Cfg_GufengzhihouTitle.Obj, &Lable_Cfg_GufengzhihhouValue.Obj,
	&Bmp_Cfg_SongliaozhihouTitle.Obj, &Lable_Cfg_SongliaozhihouValue.Obj,
	
	&Bmp_Cfg_DianhuoyinfengTitle.Obj, &Lable_Cfg_DianhuoyinfengValue.Obj,
	&Bmp_Cfg_DianhuogufengTitle.Obj, &Lable_Cfg_DianhuogufengValue.Obj,
	&Bmp_Cfg_ZhengchangyinfengTitle.Obj, &Lable_Cfg_ZhengchangyinfengValue.Obj,
	&Bmp_Cfg_ZhengchanggufengTitle.Obj, &Lable_Cfg_ZhengchanggufengValue.Obj,
	&Bmp_Cfg_BaohuoyinfengTitle.Obj, &Lable_Cfg_BaohuoyinfengValue.Obj,
	&Bmp_Cfg_BaohuogufengTitle.Obj, &Lable_Cfg_BaohuogufengValue.Obj,
	
	};

CS_FRAME(FrmConfig2, NULL, 0, 0, 480, 320, CSUI_BLACK, FrmConfig2_ChildTbl);

#define CONFIG2_CURSOR_MAX         (11)
volatile static uint8_t ui_FrmConfig2_Cursor = 0;
volatile static uint8_t ui_FrmConfig2_EditUpdateFlag = 0;

void ui_FrmConfig2_SelectEdit(uint8_t Cursor);
void ui_FrmConfig2_UpdateEdit(uint8_t Cursor, int8_t IncValue);
void ui_FrmConfig2_KeyProcess_Up(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmConfig2_KeyProcess_Down(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmConfig2_KeyProcess_Left(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmConfig2_KeyProcess_Right(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmConfig2_KeyProcess_Set(uint8_t BtnHandle, uint8_t BtnState);

void ui_FrmConfig2_Init(void)
{
	Lable_Cfg_GufengqianchuiValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_YinfengqianchuiValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_DianhuoyuzhiValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_YinfengzhihouValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_GufengzhihhouValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_SongliaozhihouValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_DianhuoyinfengValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_DianhuogufengValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_ZhengchangyinfengValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_ZhengchanggufengValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_BaohuoyinfengValue.Font = CsUI_Font_ASCII_1218;
	Lable_Cfg_BaohuogufengValue.Font = CsUI_Font_ASCII_1218;
}

void ui_FrmConfig2_ShowFrame(void)
{
	//Config1 frame redraw
	FrmConfig2.Obj.Draw(&FrmConfig2);
}

void ui_FrmConfig2_Process(void)
{
	static uint8_t ui_FrmConfig2_Cursor_Old = -1;
	
	ui_FrmConfig2_Cursor = 0;
	ui_FrmConfig2_UpdateEdit(0, 0);
	ui_FrmConfig2_UpdateEdit(1, 0);
	ui_FrmConfig2_UpdateEdit(2, 0);
	ui_FrmConfig2_UpdateEdit(3, 0);
	ui_FrmConfig2_UpdateEdit(4, 0);
	ui_FrmConfig2_UpdateEdit(5, 0);
	ui_FrmConfig2_UpdateEdit(6, 0);
	ui_FrmConfig2_UpdateEdit(7, 0);
	ui_FrmConfig2_UpdateEdit(8, 0);
	ui_FrmConfig2_UpdateEdit(9, 0);
	ui_FrmConfig2_UpdateEdit(10, 0);
	ui_FrmConfig2_UpdateEdit(11, 0);
	ui_FrmConfig2_SelectEdit(ui_FrmConfig2_Cursor);
	
	MyButton_ReLinkCallBack(CONFIG2_KEY_SET_INDEX, ui_FrmConfig2_KeyProcess_Set);
	MyButton_ReLinkCallBack(CONFIG2_KEY_UP_INDEX, ui_FrmConfig2_KeyProcess_Up);
	MyButton_ReLinkCallBack(CONFIG2_KEY_DOWN_INDEX, ui_FrmConfig2_KeyProcess_Down);
	MyButton_ReLinkCallBack(CONFIG2_KEY_LEFT_INDEX, ui_FrmConfig2_KeyProcess_Left);
	MyButton_ReLinkCallBack(CONFIG2_KEY_RIGHT_INDEX, ui_FrmConfig2_KeyProcess_Right);
	
	while(1)
	{
		if(UI_Index != 2)
		{
			return;
		}
		if(ui_FrmConfig2_Cursor_Old != ui_FrmConfig2_Cursor)
		{
			ui_FrmConfig2_SelectEdit(ui_FrmConfig2_Cursor);
			ui_FrmConfig2_Cursor_Old = ui_FrmConfig2_Cursor;
		}
		if(ui_FrmConfig2_EditUpdateFlag)
		{
			ui_FrmConfig2_SelectEdit(ui_FrmConfig2_Cursor);
			ui_FrmConfig2_EditUpdateFlag = 0;
		}
	}
}

void ui_FrmConfig2_SelectEdit(uint8_t Cursor)
{
	Lable_Cfg_GufengqianchuiValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_YinfengqianchuiValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_DianhuoyuzhiValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_YinfengzhihouValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_GufengzhihhouValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_SongliaozhihouValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_DianhuoyinfengValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_DianhuogufengValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_ZhengchangyinfengValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_ZhengchanggufengValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_BaohuoyinfengValue.FrontColor = CSUI_BLUE;
	Lable_Cfg_BaohuogufengValue.FrontColor = CSUI_BLUE;
	switch(Cursor)
	{
		case 0: Lable_Cfg_GufengqianchuiValue.FrontColor = CSUI_WHITE; break;
		case 1: Lable_Cfg_YinfengqianchuiValue.FrontColor = CSUI_WHITE; break;
		case 2: Lable_Cfg_DianhuoyuzhiValue.FrontColor = CSUI_WHITE; break;
		case 3: Lable_Cfg_YinfengzhihouValue.FrontColor = CSUI_WHITE; break;
		case 4: Lable_Cfg_GufengzhihhouValue.FrontColor = CSUI_WHITE; break;
		case 5: Lable_Cfg_SongliaozhihouValue.FrontColor = CSUI_WHITE; break;
		case 6: Lable_Cfg_DianhuoyinfengValue.FrontColor = CSUI_WHITE; break;
		case 7: Lable_Cfg_DianhuogufengValue.FrontColor = CSUI_WHITE; break;
		case 8: Lable_Cfg_ZhengchangyinfengValue.FrontColor = CSUI_WHITE; break;
		case 9: Lable_Cfg_ZhengchanggufengValue.FrontColor = CSUI_WHITE; break;
		case 10: Lable_Cfg_BaohuoyinfengValue.FrontColor = CSUI_WHITE; break;
		case 11: Lable_Cfg_BaohuogufengValue.FrontColor = CSUI_WHITE; break;
	}
	
	Lable_Cfg_GufengqianchuiValue.Obj.Draw(&Lable_Cfg_GufengqianchuiValue);
	Lable_Cfg_YinfengqianchuiValue.Obj.Draw(&Lable_Cfg_YinfengqianchuiValue);
	Lable_Cfg_DianhuoyuzhiValue.Obj.Draw(&Lable_Cfg_DianhuoyuzhiValue);
	Lable_Cfg_YinfengzhihouValue.Obj.Draw(&Lable_Cfg_YinfengzhihouValue);
	Lable_Cfg_GufengzhihhouValue.Obj.Draw(&Lable_Cfg_GufengzhihhouValue);
	Lable_Cfg_SongliaozhihouValue.Obj.Draw(&Lable_Cfg_SongliaozhihouValue);
	Lable_Cfg_DianhuoyinfengValue.Obj.Draw(&Lable_Cfg_DianhuoyinfengValue);
	Lable_Cfg_DianhuogufengValue.Obj.Draw(&Lable_Cfg_DianhuogufengValue);
	Lable_Cfg_ZhengchangyinfengValue.Obj.Draw(&Lable_Cfg_ZhengchangyinfengValue);
	Lable_Cfg_ZhengchanggufengValue.Obj.Draw(&Lable_Cfg_ZhengchanggufengValue);
	Lable_Cfg_BaohuoyinfengValue.Obj.Draw(&Lable_Cfg_BaohuoyinfengValue);
	Lable_Cfg_BaohuogufengValue.Obj.Draw(&Lable_Cfg_BaohuogufengValue);
}

void ui_FrmConfig2_UpdateEdit(uint8_t Cursor, int8_t IncValue)
{
	switch(Cursor)
	{
		case 0:
			SysParam.Gufengqianchui += IncValue;
			SysParam_ValueLimitTime16(&SysParam.Gufengqianchui);
			break;
		case 1:
			SysParam.Yinfengqianchui += IncValue;
			SysParam_ValueLimitTime16(&SysParam.Yinfengqianchui);
			break;
		case 2:
			SysParam.Dianhuoyuzhi += IncValue;
			SysParam_ValueLimitTime16(&SysParam.Dianhuoyuzhi);
			break;
		case 3:
			SysParam.Yinfengzhihou += IncValue;
			SysParam_ValueLimitTime16(&SysParam.Yinfengzhihou);
			break;
		case 4:
			SysParam.Gufengzhihou += IncValue;
			SysParam_ValueLimitTime16(&SysParam.Gufengzhihou);
			break;
		case 5:
			SysParam.Songliaozhihou += IncValue;
			SysParam_ValueLimitTime16(&SysParam.Songliaozhihou);
			break;
		case 6:
			SysParam.Dianhuoyinfeng += IncValue;
			SysParam_ValueLimitDuty(&SysParam.Dianhuoyinfeng);
			break;
		case 7:
			SysParam.Dianhuogufeng += IncValue;
			SysParam_ValueLimitDuty(&SysParam.Dianhuogufeng);
			break;
		case 8:
			SysParam.Zhengchangyinfeng += IncValue;
			SysParam_ValueLimitDuty(&SysParam.Zhengchangyinfeng);
			break;
		case 9:
			SysParam.Zhengchanggufeng += IncValue;
			SysParam_ValueLimitDuty(&SysParam.Zhengchanggufeng);
			break;
		case 10:
			SysParam.Baohuoyinfeng += IncValue;
			SysParam_ValueLimitDuty(&SysParam.Baohuoyinfeng);
			break;
		case 11:
			SysParam.Baohuogufeng += IncValue;
			SysParam_ValueLimitDuty(&SysParam.Baohuogufeng);
			break;
	}
	switch(Cursor)
	{
		case 0: sprintf(ui_FrmConfig2_Str_Gufengqianchui, "%02d:%02d", SysParam.Gufengqianchui / 60, SysParam.Gufengqianchui % 60); break;
		case 1: sprintf(ui_FrmConfig2_Str_Yinfengqianchui, "%02d:%02d", SysParam.Yinfengqianchui / 60, SysParam.Yinfengqianchui % 60);	break;
		case 2: sprintf(ui_FrmConfig2_Str_Dianhuoyuzhi, "%03d", SysParam.Dianhuoyuzhi);	break;
		case 3: sprintf(ui_FrmConfig2_Str_Yinfengzhihou, "%02d:%02d", SysParam.Yinfengzhihou / 60, SysParam.Yinfengzhihou % 60);	break;
		case 4: sprintf(ui_FrmConfig2_Str_Gufengzhihou, "%02d:%02d", SysParam.Gufengzhihou / 60, SysParam.Gufengzhihou % 60);	break;
		case 5: sprintf(ui_FrmConfig2_Str_Songliaozhihou, "%02d:%02d", SysParam.Songliaozhihou / 60, SysParam.Songliaozhihou % 60);	break;
		case 6: sprintf(ui_FrmConfig2_Str_Dianhuoyinfeng, "%03d", SysParam.Dianhuoyinfeng);	break;
		case 7: sprintf(ui_FrmConfig2_Str_Dianhuogufeng, "%03d", SysParam.Dianhuogufeng);	break;
		case 8: sprintf(ui_FrmConfig2_Str_Zhengchangyinfeng, "%03d", SysParam.Zhengchangyinfeng);	break;
		case 9: sprintf(ui_FrmConfig2_Str_Zhengchanggufeng, "%03d", SysParam.Zhengchanggufeng);	break;
		case 10: sprintf(ui_FrmConfig2_Str_Baohuoyinfeng, "%03d", SysParam.Baohuoyinfeng);	break;
		case 11: sprintf(ui_FrmConfig2_Str_Baohuogufeng, "%03d", SysParam.Baohuogufeng);	break;
	}
}

void ui_FrmConfig2_KeyProcess_Up(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_PRESS)
		return;
	
	if(ui_FrmConfig2_Cursor == 0)
	{
		ui_FrmConfig2_Cursor = CONFIG2_CURSOR_MAX;
	}
	else
	{
		ui_FrmConfig2_Cursor--;
	}
}

void ui_FrmConfig2_KeyProcess_Down(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_PRESS)
		return;
	
	ui_FrmConfig2_Cursor++;
	if(ui_FrmConfig2_Cursor > CONFIG2_CURSOR_MAX)
	{
		ui_FrmConfig2_Cursor = 0;
	}
}

void ui_FrmConfig2_KeyProcess_Left(uint8_t BtnHandle, uint8_t BtnState)
{
	switch(BtnState)
	{
		case BUTTON_STATUS_RELEASE:
		case BUTTON_STATUS_HOLD:
			ui_FrmConfig2_UpdateEdit(ui_FrmConfig2_Cursor, -1);
			ui_FrmConfig2_EditUpdateFlag = 1;
			break;
	}
}

void ui_FrmConfig2_KeyProcess_Right(uint8_t BtnHandle, uint8_t BtnState)
{
	switch(BtnState)
	{
		case BUTTON_STATUS_RELEASE:
		case BUTTON_STATUS_HOLD:
			ui_FrmConfig2_UpdateEdit(ui_FrmConfig2_Cursor, +1);
			ui_FrmConfig2_EditUpdateFlag = 1;
			break;
	}
}

void ui_FrmConfig2_KeyProcess_Set(uint8_t BtnHandle, uint8_t BtnState)
{
	static uint8_t HoldSave = 0;
	
	switch(BtnState)
	{
		case BUTTON_STATUS_RELEASE:
			if(HoldSave)
			{
				//Enter the second config frame
				HoldSave = 0;
				UI_Index = 0;
				MyBeep_Beep(1);
				vTaskDelay(50);
				MyBeep_Beep(0);
				MyButton_ReLinkCallBack(CONFIG2_KEY_SET_INDEX, NULL);
			}
			else
			{
				//Return to main frame
				UI_Index = 1;
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

