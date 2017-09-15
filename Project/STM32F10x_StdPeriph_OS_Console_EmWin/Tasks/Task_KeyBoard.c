#include "stm32f10x.h"
#include "Task_KeyBoard.h"
#include "myButton.h"
#include "myLed.h"
#include "myBeep.h"
#include "HeatControlSys.h"
#include "board.h"

#include "Frames.h"

static uint32_t Is_Init=0;


void KB_PowerSwitch(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		switch(HCS_Struct.Status)
		{
			case HCS_STATUS_STANDBY:
			case HCS_STATUS_STARTUP:
			case HCS_STATUS_PREBLOW:
			case HCS_STATUS_PREMATERIAL:
			case HCS_STATUS_WARMEDUP:
			case HCS_STATUS_FIREUP:
			case HCS_STATUS_RUNNING:
			case HCS_STATUS_FIREPROTECT:
				HCS_Struct.Status = HCS_STATUS_POWEROFF;
				//TODO:发送消息现在进入关机
				break;
			case HCS_STATUS_POWEROFF:
				HCS_Struct.Status = HCS_STATUS_STANDBY;
				//TODO:发送消息现在进入开机初始化
				break;
		}
	}
}

void KB_SysSwitch(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		switch(HCS_Struct.Status)
		{
			case HCS_STATUS_STANDBY:
				HCS_Struct.Status = HCS_STATUS_STARTUP;
				//TODO:发送消息现在启动
				break;
			case HCS_STATUS_STARTUP:
			case HCS_STATUS_PREBLOW:
			case HCS_STATUS_PREMATERIAL:
			case HCS_STATUS_WARMEDUP:
			case HCS_STATUS_FIREUP:
			case HCS_STATUS_RUNNING:
			case HCS_STATUS_FIREPROTECT:
				//HCS_Struct.Status = HCS_STATUS_POWEROFF;
				//TODO:发送消息
				break;
			case HCS_STATUS_POWEROFF:
				//HCS_Struct.Status = HCS_STATUS_STANDBY;
				//TODO:发送消息
				break;
		}
	}
}

void KB_TestSwitch(uint8_t BtnHandle, uint8_t BtnState)
{
	static uint8_t xx = 0;
	
	if(BtnState == BUTTON_STATUS_PRESS)
	{
		MyBeep_Beep(1);
	}
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		MyBeep_Beep(0);
	}
	if(BtnState == BUTTON_STATUS_HOLD)
	{
		MyBeep_Beep(xx);
		xx = 1 - xx;
	}
}

void KB_SetSwitch(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		//设置界面切换
		if(BtnState == BUTTON_STATUS_RELEASE)
		{
			UI_Mode = !UI_Mode;
		}
	}
}

void KB_UpKey(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		
	}
}

void KB_DownKey(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		
	}
}

void KB_LeftKey(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		
	}
}

void KB_RightKey(uint8_t BtnHandle, uint8_t BtnState)
{
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		
	}
}

void KeyBoard_Regs(void)
{
	MyButton_RegType btn;
	
	btn.ButtonIdleState = SET;
	
	btn.CallBackFunc = KB_PowerSwitch;
	btn.ButtonGPIO = _BUTTON_POWER_GPIO;
	btn.ButtonPin = _BUTTON_POWER_PIN;
	MyButton_Reg(0, &btn);
	
	btn.CallBackFunc = KB_SysSwitch;
	btn.ButtonGPIO = _BUTTON_SWITCH_GPIO;
	btn.ButtonPin = _BUTTON_SWITCH_PIN;
	MyButton_Reg(1, &btn);
	
	btn.CallBackFunc = KB_SetSwitch;
	btn.ButtonGPIO = _BUTTON_SET_GPIO;
	btn.ButtonPin = _BUTTON_SET_PIN;
	MyButton_Reg(2, &btn);
	
	btn.CallBackFunc = KB_UpKey;
	btn.ButtonGPIO = _BUTTON_UP_GPIO;
	btn.ButtonPin = _BUTTON_UP_PIN;
	MyButton_Reg(3, &btn);
	
	btn.CallBackFunc = KB_DownKey;
	btn.ButtonGPIO = _BUTTON_DOWN_GPIO;
	btn.ButtonPin = _BUTTON_DOWN_PIN;
	MyButton_Reg(4, &btn);
	
	btn.CallBackFunc = KB_LeftKey;
	btn.ButtonGPIO = _BUTTON_LEFT_GPIO;
	btn.ButtonPin = _BUTTON_LEFT_PIN;
	MyButton_Reg(5, &btn);
	
	btn.CallBackFunc = KB_RightKey;
	btn.ButtonGPIO = _BUTTON_RIGHT_GPIO;
	btn.ButtonPin = _BUTTON_RIGHT_PIN;
	MyButton_Reg(6, &btn);
	
	btn.CallBackFunc = KB_TestSwitch;
	btn.ButtonGPIO = _BUTTON_RESERVE_GPIO;
	btn.ButtonPin = _BUTTON_RESERVE_PIN;
	MyButton_Reg(7, &btn);
}

void vTask_KeyBoard( void *pvParameters )
{
	MyButton_Init();
	KeyBoard_Regs();
	
	MyBeep_Init();
	
	Is_Init = KEYBOARD_INIT_DONE;
	//xQueueSendToBack(InitQueue, &Is_Init, portMAX_DELAY);
	
	while(1)
	{
		MyButton_Process();
		vTaskDelay(50);
	}
}
