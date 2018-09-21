#include "stm32f10x.h"
#include "Task_Control.h"
#include "myButton.h"
#include "HeatControlSys.h"
#include "Task_Monitor.h"
#include "sysParams.h"
#include "cslRTC.h"
#include "cslLCD.h"
#include "Task_DeviceControl.h"



static QueueHandle_t msg_handle;

typedef struct control_msg_t
{
	unsigned char cmd;
}control_msg_t;

static control_msg_t msg;

//static void Control_LowLevel_Init(void)
//{
//	IO_Dianhuo.GPIO = _OUT_RL3_GPIO;
//	IO_Dianhuo.Pin = _OUT_RL3_PIN;
//	IO_Dianhuo.IOMode = IOMode_Level_Out;
//	
//	IO_Liaoji.GPIO = _OUT_RL2_GPIO;
//	IO_Liaoji.Pin = _OUT_RL2_PIN;
//	IO_Liaoji.IOMode = IOMode_Level_Out;
//	
//	IO_Yinfeng.GPIO = _OUT_WP1_GPIO;
//	IO_Yinfeng.Pin = _OUT_WP1_PIN;
//	IO_Yinfeng.IOMode = IOMode_SCR_Out;
//	
//	IO_Gufeng.GPIO = _OUT_WP2_GPIO;
//	IO_Gufeng.Pin = _OUT_WP2_PIN;
//	IO_Gufeng.IOMode = IOMode_SCR_Out;
//	
//	CslIOCtrl_Reg(&IO_Dianhuo);
//	CslIOCtrl_Reg(&IO_Liaoji);
//	CslIOCtrl_Reg(&IO_Yinfeng);
//	CslIOCtrl_Reg(&IO_Gufeng);
//	
//	CslIOCtrl_SetLevelOut(&IO_Dianhuo, 0);
//	CslIOCtrl_SetLevelOut(&IO_Liaoji, 0);
//	CslIOCtrl_SetSCROut(&IO_Yinfeng, 0);
//	CslIOCtrl_SetSCROut(&IO_Gufeng, 0);
//}

static uint32_t Is_Init=0;
static CslRTC_Time HCS_Time;

void Control_SendMsg(unsigned char cmd)
{
	control_msg_t msg;
	msg.cmd = cmd;
	xQueueSend(msg_handle, &msg, portMAX_DELAY);
}

void vTask_Control( void *pvParameters )
{
	int ret;
	int sub_stage;
	//Control_LowLevel_Init();
	HCS_Init();
	
	Is_Init = CONTROL_INIT_DONE;
	//xQueueSendToBack(InitQueue, &Is_Init, portMAX_DELAY);
	msg_handle = xQueueCreate(4, sizeof(control_msg_t));
	
	while(1)
	{
		ret = xQueueReceive(msg_handle, &msg, 20);     //pick msg each 20 ms
		if(ret != pdFALSE)
		{
			//deal with control msg
			switch(msg.cmd)
			{
				case CMD_CONTROL_POWEROFF:
					if(HCS_Struct.Status != HCS_STATUS_POWEROFF)
					{
						HCS_Struct.Status = HCS_STATUS_POWEROFF;
						HCS_SM_PowerOff(0);
					}
					break;
				case CMD_CONTROL_POWERON:
					if(HCS_Struct.Status == HCS_STATUS_POWEROFF)
					{
						//Init device system
						HCS_Struct.Status = HCS_STATUS_STANDBY;          //FSM: PowerOff -> Standby
						sub_stage = 0;
						HCS_SM_PowerOn(0);
					}
					break;
				case CMD_CONTROL_START:
					if(HCS_Struct.Status == HCS_STATUS_STANDBY)
					{
						//Start device engine
						HCS_Struct.Status = HCS_STATUS_STARTUP;          //FSM: Standby -> Starup
						sub_stage = 0;
					}
					break;
				case CMD_CONTROL_SUSPEND:
					//Not support suspend now
					break;
				case CMD_CONTROL_STOP:
					if((HCS_Struct.Status != HCS_STATUS_POWEROFF) &&
						 (HCS_Struct.Status != HCS_STATUS_STANDBY))
					{
						HCS_Struct.Status = HCS_STATUS_STOPPING;
						sub_stage = 0;
					}
					break;
				case CMD_CONTROL_RUN:
					//Not support resume to run now
					break;
				case CMD_CONTROL_TEST:
					HCS_Struct.Status = HCS_STATUS_TEST;
					break;
			}
		}
		switch(HCS_Struct.Status)
		{
			case HCS_STATUS_STOPPING:
				sub_stage = HCS_SM_Stopping(sub_stage);
				break;
			case HCS_STATUS_POWEROFF:
				sub_stage = HCS_SM_PowerOff(sub_stage);
				break;
			case HCS_STATUS_STANDBY:
				sub_stage = HCS_SM_Standby(sub_stage);
				break;
			case HCS_STATUS_STARTUP:
				sub_stage = HCS_SM_Startup(sub_stage);
				break;
			case HCS_STATUS_PREBLOW:
				sub_stage = HCS_SM_PreBlowing(sub_stage);
				break;
			case HCS_STATUS_PREMATERIAL:
				sub_stage = HCS_SM_PreMaterial(sub_stage);
				break;
			case HCS_STATUS_WARMEDUP:
				sub_stage = HCS_SM_WarmedUp(sub_stage);
				break;
			case HCS_STATUS_FIREUP:
				sub_stage = HCS_SM_FireUp(sub_stage);
				break;
			case HCS_STATUS_RUNNING:
				sub_stage = HCS_SM_Running(sub_stage);
				break;
			case HCS_STATUS_FIREPROTECT:
				sub_stage = HCS_SM_FireProtection(sub_stage);
				break;
			case HCS_STATUS_TEST:
				sub_stage = HCS_SM_Test(sub_stage);
				break;
		}
		CslRTC_GetTime(&HCS_Time);
		if((HCS_Struct.pParams->Dinshiguanji >= 0) && (HCS_Struct.Status != HCS_STATUS_POWEROFF))
		{
			if(HCS_Time.Hou == HCS_Struct.pParams->Dinshiguanji / 60)
			{
				if(HCS_Time.Min == HCS_Struct.pParams->Dinshiguanji % 60)
				{
					HCS_Struct.Status = HCS_STATUS_POWEROFF;
					CsLCD_DisplayControl(1);
					CslLCD_BLK(0);
					extern volatile uint8_t UI_Index;
					UI_Index = 0;
				}
			}
		}
	}
}
