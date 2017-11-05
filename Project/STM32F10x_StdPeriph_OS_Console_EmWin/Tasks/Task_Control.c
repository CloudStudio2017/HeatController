#include "stm32f10x.h"
#include "Task_Control.h"
#include "myButton.h"
#include "HeatControlSys.h"
#include "Task_Monitor.h"
#include "sysParams.h"

extern CslIOCtrl_RegTypeDef IO_Liaoji;
extern CslIOCtrl_RegTypeDef IO_Yinfeng;
extern CslIOCtrl_RegTypeDef IO_Gufeng;
extern CslIOCtrl_RegTypeDef IO_Dianhuo;
extern CslIOCtrl_RegTypeDef IO_Shuiwei;
extern CslIOCtrl_RegTypeDef IO_Queliao;


static void Control_LowLevel_Init(void)
{
	HCS_Init();
	
	IO_Liaoji.GPIO = _OUT_L1_GPIO;
	IO_Liaoji.Pin = _OUT_L1_PIN;
	IO_Liaoji.IOMode = IOMode_Level_Out;
	
	IO_Yinfeng.GPIO = _OUT_L2_GPIO;
	IO_Yinfeng.Pin = _OUT_L2_PIN;
	IO_Yinfeng.IOMode = IOMode_Level_Out;
	
	IO_Gufeng.GPIO = _OUT_L3_GPIO;
	IO_Gufeng.Pin = _OUT_L3_PIN;
	IO_Gufeng.IOMode = IOMode_Level_Out;
	
	IO_Dianhuo.GPIO = _OUT_L4_GPIO;
	IO_Dianhuo.Pin = _OUT_L4_PIN;
	IO_Dianhuo.IOMode = IOMode_Level_Out;
	
	IO_Shuiwei.GPIO = _OUT_LWP_GPIO;
	IO_Shuiwei.Pin = _OUT_LWP_PIN;
	IO_Shuiwei.IOMode = IOMode_Level_In;
	
	IO_Queliao.GPIO = _OUT_RWP_GPIO;
	IO_Queliao.Pin = _OUT_RWP_PIN;
	IO_Queliao.IOMode = IOMode_Level_Out;
	
	//CslIOCtrl_Reg(&IO_Liaoji);
	//CslIOCtrl_Reg(&IO_Yinfeng);
	//CslIOCtrl_Reg(&IO_Gufeng);
	//CslIOCtrl_Reg(&IO_Dianhuo);
	//CslIOCtrl_Reg(&IO_Shuiwei);
	//CslIOCtrl_Reg(&IO_Queliao);
	
	//CslIOCtrl_SetLevelOut(&IO_Liaoji, 0);
	//CslIOCtrl_SetLevelOut(&IO_Yinfeng, 1);
	//CslIOCtrl_SetLevelOut(&IO_Gufeng, 1);
	//CslIOCtrl_SetLevelOut(&IO_Dianhuo, 1);
	//CslIOCtrl_SetLevelOut(&IO_Shuiwei, 0);
	//CslIOCtrl_SetLevelOut(&IO_Queliao, 1);
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
		}
	}
}
