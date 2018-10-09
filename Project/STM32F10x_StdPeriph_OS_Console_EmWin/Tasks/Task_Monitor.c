#include "Task_Monitor.h"
#include "cslCommon.h"
#include "PT100.h"
#include "MAX6675.h"
#include "HeatControlSys.h"
#include "cslIOCtrl.h"



#define MONITOR_MAT_LOW_GPIO    _MAT_LOW_GPIO
#define MONITOR_MAT_LOW_PIN     _MAT_LOW_PIN


extern CslIOCtrl_RegTypeDef IO_Queliao;

static uint8_t monitor_sim_mode = 1;

void monitor_simulator(void)
{
	static int sim_count = 0;
	static TickType_t last_tick;
	static uint8_t mode = 0;
	
	switch(HCS_Struct.Status)
	{
		case HCS_STATUS_STANDBY:
			HCS_Struct.MaterialLow = 0;
			HCS_Struct.StoveTemp.Flag = 0;
			HCS_Struct.StoveTemp.Value = 10;
			HCS_Struct.WaterTemp.Flag = 0;
			HCS_Struct.WaterTemp.Value = 10;
			break;
		case HCS_STATUS_STARTUP:
		case HCS_STATUS_PREBLOW:
		case HCS_STATUS_PREMATERIAL:
		case HCS_STATUS_WARMEDUP:
			break;
		case HCS_STATUS_FIREUP:
			HCS_Struct.StoveTemp.Value += 10;
			break;
		case HCS_STATUS_RUNNING:
			if(mode != 2)
			{
				sim_count++;
				if(sim_count > 10)
				{
					mode = 2;
					sim_count = 0;
				}
			}
			break;
		case HCS_STATUS_FIREPROTECT:
			if(mode != 1)
			{
				sim_count++;
				if(sim_count > 10)
				{
					mode = 1;
					sim_count = 0;
				}
			}
			break;
		case HCS_STATUS_POWEROFF:
		case HCS_STATUS_STOPPING:
		case HCS_STATUS_TEST:
			break;
	}
	switch(mode)
	{
		case 1:    // water temperature failling
			HCS_Struct.WaterTemp.Value -= 1;
			break;
		case 2:    // water temperature rising
			HCS_Struct.WaterTemp.Value += 1;
			break;
		default:
			break;
	}
	vTaskDelay(200);
}

void vTask_Monitor( void *pvParameters )
{
	float tmpTemp;
	unsigned char tmpRet;
	signed short tmpK;
	
	while(1)
	{
		if(monitor_sim_mode)
		{
			/* simulator mode for monitor process */
			monitor_simulator();
			continue;
		}
		/* Get Mat low */
		if(GPIO_ReadInputDataBit(MONITOR_MAT_LOW_GPIO, MONITOR_MAT_LOW_PIN) == RESET)
		{
			HCS_Struct.MaterialLow = 1;
		}
		else
		{
			HCS_Struct.MaterialLow = 0;
		}
		
		/* Get K Sensor */
		tmpRet = MAX6675_GetTemp((unsigned short*)&tmpK);
		if(tmpRet == MAX6675_NOERR)
		{
			HCS_Struct.StoveTemp.Value = tmpK;
			if(tmpK > 950)
			{
				HCS_Struct.StoveTemp.Flag = 1;
			}
			else if(tmpK < -50)
			{
				HCS_Struct.StoveTemp.Flag = 2;
			}
			else
			{
				HCS_Struct.StoveTemp.Flag = 0;
			}
		}
		else
		{
			HCS_Struct.StoveTemp.Flag = 3;
			HCS_Struct.StoveTemp.Value = 0;
		}
		/* Get PT100 */
		tmpTemp = PT100_GetTempValue();
		HCS_Struct.WaterTemp.Value = tmpTemp;
		if(tmpTemp > 200)
		{
			HCS_Struct.WaterTemp.Flag = 1;
		}
		else if(tmpTemp < -50)
		{
			HCS_Struct.WaterTemp.Flag = 2;
		}
		else
		{
			HCS_Struct.WaterTemp.Flag = 0;
		}
		
		vTaskDelay(200);
	}
}

void Monitor_InputIO_Init(void)
{
	IO_Queliao.GPIO = _MAT_LOW_GPIO;
	IO_Queliao.Pin = _MAT_LOW_PIN;
	IO_Queliao.IOMode = IOMode_Level_In;
	
	CslIOCtrl_Reg(&IO_Queliao);
}

void vTask_Monitor_Init(void)
{
	Monitor_InputIO_Init();
	PT100_Init();
	PT100_Update_kb(HCS_Struct.pParams->PT100_X100, HCS_Struct.pParams->PT100_X138_5);
	MAX6675_Init();
	
	xTaskCreate(vTask_Monitor, "Task_Monitor", 256, NULL, tskIDLE_PRIORITY, NULL);
}
