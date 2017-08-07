#include "stm32f10x.h"
#include "Task_Control.h"
#include "myButton.h"
#include "myLed.h"
#include "HeatControlSys.h"



static void Control_LowLevel_Init(void)
{
	HCS_Init();
	
	myLed_Init();
	myLed_Off(0);
	myLed_Off(1);
	myLed_Off(2);
	myLed_Off(3);
	myLed_Off(4);
	myLed_Off(5);
	myLed_Off(6);
	myLed_Off(7);
}

static uint32_t Is_Init=0;

void vTask_Control( void *pvParameters )
{
	Control_LowLevel_Init();
	HCS_Init();
	
	Is_Init = CONTROL_INIT_DONE;
	xQueueSendToBack(InitQueue, &Is_Init, portMAX_DELAY);
	
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
