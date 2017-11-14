#include "stm32f10x.h"
#include "Task_Control.h"
#include "myButton.h"
#include "HeatControlSys.h"
#include "Task_Monitor.h"
#include "sysParams.h"


extern CslIOCtrl_RegTypeDef IO_Dianhuo;
extern CslIOCtrl_RegTypeDef IO_Liaoji;
extern CslIOCtrl_RegTypeDef IO_Gufeng;
extern CslIOCtrl_RegTypeDef IO_Yinfeng;
extern CslIOCtrl_RegTypeDef IO_Queliao;


static void Control_LowLevel_Init(void)
{
	IO_Dianhuo.GPIO = _OUT_RL1_GPIO;
	IO_Dianhuo.Pin = _OUT_RL1_PIN;
	IO_Dianhuo.IOMode = IOMode_Level_Out;
	
	IO_Liaoji.GPIO = _OUT_RL2_GPIO;
	IO_Liaoji.Pin = _OUT_RL2_PIN;
	IO_Liaoji.IOMode = IOMode_Level_Out;
	
	IO_Yinfeng.GPIO = _OUT_WP1_GPIO;
	IO_Yinfeng.Pin = _OUT_WP1_PIN;
	IO_Yinfeng.IOMode = IOMode_SCR_Out;
	
	IO_Gufeng.GPIO = _OUT_WP2_GPIO;
	IO_Gufeng.Pin = _OUT_WP2_PIN;
	IO_Gufeng.IOMode = IOMode_SCR_Out;
	
	CslIOCtrl_Reg(&IO_Dianhuo);
	CslIOCtrl_Reg(&IO_Liaoji);
	CslIOCtrl_Reg(&IO_Yinfeng);
	CslIOCtrl_Reg(&IO_Gufeng);
	
	CslIOCtrl_SetLevelOut(&IO_Dianhuo, 0);
	CslIOCtrl_SetLevelOut(&IO_Liaoji, 0);
	CslIOCtrl_SetSCROut(&IO_Yinfeng, 0);
	CslIOCtrl_SetSCROut(&IO_Gufeng, 0);
}

static uint32_t Is_Init=0;

void vTask_Control( void *pvParameters )
{
	Control_LowLevel_Init();
	HCS_Init();
	
	Is_Init = CONTROL_INIT_DONE;
	//xQueueSendToBack(InitQueue, &Is_Init, portMAX_DELAY);
	
	while(1)
	{
		switch(HCS_Struct.Status)
		{
			case HCS_STATUS_POWEROFF:
				HCS_SM_PowerOff(0);
				break;
			case HCS_STATUS_STANDBY:
				HCS_SM_Standby(0);
				break;
			case HCS_STATUS_STARTUP:
				HCS_SM_Startup(0);
				break;
			case HCS_STATUS_PREBLOW:
				HCS_SM_PreBlowing(0);
				break;
			case HCS_STATUS_PREMATERIAL:
				HCS_SM_PreMaterial(0);
				break;
			case HCS_STATUS_WARMEDUP:
				HCS_SM_WarmedUp(0);
				break;
			case HCS_STATUS_FIREUP:
				HCS_SM_FireUp(0);
				break;
			case HCS_STATUS_RUNNING:
				HCS_SM_Running(0);
				break;
			case HCS_STATUS_FIREPROTECT:
				HCS_SM_FireProtection(0);
				break;
			case HCS_STATUS_TEST:
				HCS_SM_Test(0);
				break;
		}
	}
}
