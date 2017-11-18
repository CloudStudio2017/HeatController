#include "Task_Monitor.h"
#include "cslCommon.h"
#include "PT100.h"
#include "MAX6675.h"
#include "HeatControlSys.h"
#include "cslIOCtrl.h"



#define MONITOR_MAT_LOW_GPIO    _MAT_LOW_GPIO
#define MONITOR_MAT_LOW_PIN     _MAT_LOW_PIN


extern CslIOCtrl_RegTypeDef IO_Queliao;


void vTask_Monitor( void *pvParameters )
{
	float tmpTemp;
	unsigned char tmpRet;
	signed short tmpK;
	
	while(1)
	{
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
