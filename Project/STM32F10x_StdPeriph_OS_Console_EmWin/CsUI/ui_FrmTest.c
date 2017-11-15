#include "ui_FrmTest.h"
#include "myButton.h"
#include "sysParams.h"
#include "stdio.h"
#include "myBeep.h"
#include "HeatControlSys.h"

#define TEST_KEY_POWERSWITCH_INDEX 0
#define TEST_KEY_SET_INDEX    2
#define TEST_KEY_UP_INDEX     3
#define TEST_KEY_DOWN_INDEX   4
#define TEST_KEY_LEFT_INDEX   5
#define TEST_KEY_RIGHT_INDEX  6

static char ui_FrmTest_Str_Dianhuo[]   = "OFF";
static char ui_FrmTest_Str_Liaoji[]    = "OFF";
static char ui_FrmTest_Str_Gufeng[]    = "  0%";
static char ui_FrmTest_Str_Yinfeng[]   = "  0%";
static char ui_FrmTest_Str_PT100[]     = "Error";
static char ui_FrmTest_Str_KSensor[]   = "Error";
static char ui_FrmTest_Str_Queliao[]   = "Yes";

CS_BITMAP(Bmp_Test_Title,                    NULL, 150, 10,  10, 10, CSUI_WHITE, CSUI_BLACK, xBitmapXitongshezhi);

CS_BITMAP(Bmp_Test_DianhuoTitle,             NULL, 10, 10+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Dianhuo);
CS_LABLE(Lable_Test_DianhuoValue,            NULL,150, 15+60, 10, 10, CSUI_WHITE, CSUI_BLACK, ui_FrmTest_Str_Dianhuo, NULL);
CS_BITMAP(Bmp_Test_LiaojiTitle,              NULL, 10, 40+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Songliao);
CS_LABLE(Lable_Test_LiaojiValue,             NULL,150, 45+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmTest_Str_Liaoji, NULL);
CS_BITMAP(Bmp_Test_GufengTitle,              NULL, 10, 70+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Gufeng);
CS_LABLE(Lable_Test_GufengValue,             NULL,150, 75+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmTest_Str_Gufeng, NULL);
CS_BITMAP(Bmp_Test_YinfengTitle,             NULL, 10,100+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Yinfeng);
CS_LABLE(Lable_Test_YinfengValue,            NULL,150,105+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmTest_Str_Yinfeng, NULL);

CS_BITMAP(Bmp_Test_PT100Title,               NULL,250, 10+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_PT100);
CS_LABLE(Lable_Test_PT100Value,              NULL,390, 15+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmTest_Str_PT100, NULL);
CS_BITMAP(Bmp_Test_KSensorTitle,             NULL,250, 40+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_KDianou);
CS_LABLE(Lable_Test_KSensorValue,            NULL,390, 45+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmTest_Str_KSensor, NULL);
CS_BITMAP(Bmp_Test_QueliaoTitle,             NULL,250, 70+60, 10, 10, CSUI_BLUE, CSUI_BLACK, xBmpData_Queliao);
CS_LABLE(Lable_Test_QueliaoValue,            NULL,390, 75+60, 10, 10, CSUI_BLUE, CSUI_BLACK, ui_FrmTest_Str_Queliao, NULL);


TCsUI_BaseObjectTable FrmTest_ChildTbl[]={
	&Bmp_Test_Title.Obj,
	&Bmp_Test_DianhuoTitle.Obj, &Lable_Test_DianhuoValue.Obj,
	&Bmp_Test_LiaojiTitle.Obj, &Lable_Test_LiaojiValue.Obj,
	&Bmp_Test_GufengTitle.Obj, &Lable_Test_GufengValue.Obj,
	&Bmp_Test_YinfengTitle.Obj, &Lable_Test_YinfengValue.Obj,
	&Bmp_Test_PT100Title.Obj, &Lable_Test_PT100Value.Obj,
	&Bmp_Test_KSensorTitle.Obj, &Lable_Test_KSensorValue.Obj,
	&Bmp_Test_QueliaoTitle.Obj, &Lable_Test_QueliaoValue.Obj,
	
	};

CS_FRAME(FrmTest, NULL, 0, 0, 480, 320, CSUI_BLACK, FrmTest_ChildTbl);

#define TEST_CURSOR_MAX         (3)
volatile static uint8_t ui_FrmTest_Cursor = 0;
volatile static uint8_t ui_FrmTest_EditUpdateFlag = 0;
TestStatusTypeDef TestStatus;

void ui_FrmTest_SelectEdit(uint8_t Cursor);
void ui_FrmTest_UpdateEditAndExcute(uint8_t Cursor, int8_t IncValue);
void ui_FrmTest_KeyProcess_Up(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmTest_KeyProcess_Down(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmTest_KeyProcess_Left(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmTest_KeyProcess_Right(uint8_t BtnHandle, uint8_t BtnState);
void ui_FrmTest_KeyProcess_Set(uint8_t BtnHandle, uint8_t BtnState);

void ui_FrmTest_Init(void)
{
	Lable_Test_DianhuoValue.Font = CsUI_Font_ASCII_1218;
	Lable_Test_LiaojiValue.Font = CsUI_Font_ASCII_1218;
	Lable_Test_GufengValue.Font = CsUI_Font_ASCII_1218;
	Lable_Test_YinfengValue.Font = CsUI_Font_ASCII_1218;
	Lable_Test_PT100Value.Font = CsUI_Font_ASCII_1218;
	Lable_Test_KSensorValue.Font = CsUI_Font_ASCII_1218;
	Lable_Test_QueliaoValue.Font = CsUI_Font_ASCII_1218;
	
	Lable_Test_DianhuoValue.Parent = &FrmTest;
	Lable_Test_LiaojiValue.Parent = &FrmTest;
	Lable_Test_GufengValue.Parent = &FrmTest;
	Lable_Test_YinfengValue.Parent = &FrmTest;
	Lable_Test_PT100Value.Parent = &FrmTest;
	Lable_Test_KSensorValue.Parent = &FrmTest;
	Lable_Test_QueliaoValue.Parent = &FrmTest;
}

void ui_FrmTest_ShowFrame(void)
{
	FrmTest.Obj.Draw(&FrmTest);
}

void ui_FrmTest_Process(void)
{
	static uint8_t ui_FrmTest_iCount = 0;
	static uint8_t ui_FrmTest_Cursor_Old = -1;
	
	ui_FrmTest_Cursor = 0;
	ui_FrmTest_UpdateEditAndExcute(0, 0);
	ui_FrmTest_UpdateEditAndExcute(1, 0);
	ui_FrmTest_UpdateEditAndExcute(2, 0);
	ui_FrmTest_UpdateEditAndExcute(3, 0);
	ui_FrmTest_SelectEdit(ui_FrmTest_Cursor);
	
	MyButton_ReLinkCallBack(TEST_KEY_SET_INDEX, ui_FrmTest_KeyProcess_Set);
	MyButton_ReLinkCallBack(TEST_KEY_UP_INDEX, ui_FrmTest_KeyProcess_Up);
	MyButton_ReLinkCallBack(TEST_KEY_DOWN_INDEX, ui_FrmTest_KeyProcess_Down);
	MyButton_ReLinkCallBack(TEST_KEY_LEFT_INDEX, ui_FrmTest_KeyProcess_Left);
	MyButton_ReLinkCallBack(TEST_KEY_RIGHT_INDEX, ui_FrmTest_KeyProcess_Right);
	MyButton_ReLinkCallBack(TEST_KEY_POWERSWITCH_INDEX, NULL);
	
	while(1)
	{
		if(UI_Index != 3)
		{
			return;
		}
		if(ui_FrmTest_Cursor_Old != ui_FrmTest_Cursor)
		{
			ui_FrmTest_SelectEdit(ui_FrmTest_Cursor);
			ui_FrmTest_Cursor_Old = ui_FrmTest_Cursor;
		}
		if(ui_FrmTest_EditUpdateFlag)
		{
			ui_FrmTest_SelectEdit(ui_FrmTest_Cursor);
			ui_FrmTest_EditUpdateFlag = 0;
		}
		vTaskDelay(100);
		ui_FrmTest_iCount++;
		if(ui_FrmTest_iCount >= 10)
		{
			ui_FrmTest_iCount = 0;
			//TODO Update TempSensor and Queliao Input
			//PT100
			if(HCS_Struct.WaterTemp.Flag)
			{
				sprintf(ui_FrmTest_Str_PT100, "Error");
			}
			else
			{
				sprintf(ui_FrmTest_Str_PT100, " %3.0f ", HCS_Struct.WaterTemp.Value);
			}
			Lable_Test_PT100Value.Obj.Draw(&Lable_Test_PT100Value);
			//K Sensor
			if(HCS_Struct.StoveTemp.Flag)
			{
				sprintf(ui_FrmTest_Str_KSensor, "Error");
			}
			else
			{
				sprintf(ui_FrmTest_Str_KSensor, " %3.0f ", HCS_Struct.StoveTemp.Value);
			}
			Lable_Test_KSensorValue.Obj.Draw(&Lable_Test_KSensorValue);
			//Queliao
			if(HCS_Struct.MaterialLow)
			{
				sprintf(ui_FrmTest_Str_Queliao, "Yes");
			}
			else
			{
				sprintf(ui_FrmTest_Str_Queliao, " No");
			}
			Lable_Test_QueliaoValue.Obj.Draw(&Lable_Test_QueliaoValue);
		}
	}
}

void ui_FrmTest_SelectEdit(uint8_t Cursor)
{
	Lable_Test_DianhuoValue.FrontColor = CSUI_BLUE;
	Lable_Test_LiaojiValue.FrontColor = CSUI_BLUE;
	Lable_Test_GufengValue.FrontColor = CSUI_BLUE;
	Lable_Test_YinfengValue.FrontColor = CSUI_BLUE;
	switch(Cursor)
	{
		case 0: Lable_Test_DianhuoValue.FrontColor = CSUI_WHITE; break;
		case 1: Lable_Test_LiaojiValue.FrontColor = CSUI_WHITE; break;
		case 2: Lable_Test_GufengValue.FrontColor = CSUI_WHITE; break;
		case 3: Lable_Test_YinfengValue.FrontColor = CSUI_WHITE; break;
	}
	Lable_Test_DianhuoValue.Obj.Draw(&Lable_Test_DianhuoValue);
	Lable_Test_LiaojiValue.Obj.Draw(&Lable_Test_LiaojiValue);
	Lable_Test_GufengValue.Obj.Draw(&Lable_Test_GufengValue);
	Lable_Test_YinfengValue.Obj.Draw(&Lable_Test_YinfengValue);
}

void ui_FrmTest_UpdateEditAndExcute(uint8_t Cursor, int8_t IncValue)
{
	switch(Cursor)
	{
		case 0:
			if(IncValue > 0)
			{
				TestStatus.DianhuoStatus = 1;
				sprintf(ui_FrmTest_Str_Dianhuo, " ON");
				_FireUp_On_();
			}
			else
			{
				TestStatus.DianhuoStatus = 0;
				sprintf(ui_FrmTest_Str_Dianhuo, "OFF");
				_FireUp_Off_();
			}
			break;
		case 1:
			if(IncValue > 0)
			{
				TestStatus.LiaojiStatus = 1;
				sprintf(ui_FrmTest_Str_Liaoji, " ON");
				_MaterialMachine_On_();
			}
			else
			{
				TestStatus.DianhuoStatus = 0;
				sprintf(ui_FrmTest_Str_Liaoji, "OFF");
				_MaterialMachine_Off_();
			}
			break;
		case 2:
			TestStatus.GufengStatus += IncValue;
			if(TestStatus.GufengStatus > 100)
				TestStatus.GufengStatus = 100;
			else if(TestStatus.GufengStatus < 0)
				TestStatus.GufengStatus = 0;
			sprintf(ui_FrmTest_Str_Gufeng, "%3d%%", TestStatus.GufengStatus);
			_AirBlowerSet_(TestStatus.GufengStatus);
			break;
		case 3:
			TestStatus.YinfengStatus += IncValue;
			if(TestStatus.YinfengStatus > 100)
				TestStatus.YinfengStatus = 100;
			else if(TestStatus.YinfengStatus < 0)
				TestStatus.YinfengStatus = 0;
			sprintf(ui_FrmTest_Str_Yinfeng, "%3d%%", TestStatus.YinfengStatus);
			_LeadFanSet_(TestStatus.YinfengStatus);
			break;
	}
}

void ui_FrmTest_KeyProcess_Up(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_PRESS)
		return;
	
	if(ui_FrmTest_Cursor == 0)
	{
		ui_FrmTest_Cursor = TEST_CURSOR_MAX;
	}
	else
	{
		ui_FrmTest_Cursor--;
	}
}

void ui_FrmTest_KeyProcess_Down(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_PRESS)
		return;
	
	ui_FrmTest_Cursor++;
	if(ui_FrmTest_Cursor > TEST_CURSOR_MAX)
	{
		ui_FrmTest_Cursor = 0;
	}
}

void ui_FrmTest_KeyProcess_Left(uint8_t BtnHandle, uint8_t BtnState)
{
	switch(BtnState)
	{
		case BUTTON_STATUS_RELEASE:
		case BUTTON_STATUS_HOLD:
			ui_FrmTest_UpdateEditAndExcute(ui_FrmTest_Cursor, -1);
			ui_FrmTest_EditUpdateFlag = 1;
			break;
	}
}

void ui_FrmTest_KeyProcess_Right(uint8_t BtnHandle, uint8_t BtnState)
{
	switch(BtnState)
	{
		case BUTTON_STATUS_RELEASE:
		case BUTTON_STATUS_HOLD:
			ui_FrmTest_UpdateEditAndExcute(ui_FrmTest_Cursor, +1);
			ui_FrmTest_EditUpdateFlag = 1;
			break;
	}
}

void ui_FrmTest_KeyProcess_Set(uint8_t BtnHandle, uint8_t BtnState)
{
	switch(BtnState)
	{
		case BUTTON_STATUS_RELEASE:
			//Return to main frame
			UI_Index = 0;
			MyBeep_Beep(1);
			vTaskDelay(50);
			MyBeep_Beep(0);
			HCS_Struct.Status = HCS_STATUS_STANDBY;
			//TODO Close Device
			MyButton_ReLinkCallBack(TEST_KEY_SET_INDEX, NULL);
			MyButton_ReLinkCallBack(TEST_KEY_UP_INDEX, NULL);
			MyButton_ReLinkCallBack(TEST_KEY_DOWN_INDEX, NULL);
			MyButton_ReLinkCallBack(TEST_KEY_LEFT_INDEX, NULL);
			MyButton_ReLinkCallBack(TEST_KEY_RIGHT_INDEX, NULL);
			break;
	}
}

