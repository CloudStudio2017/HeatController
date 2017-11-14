#include "HeatControlSys.h"
#include "FreeRTOS.h"
#include "Task.h"
#include "myBeep.h"
#include "Task_Monitor.h"

CslIOCtrl_Device_Level_TypeDef Device_Dianhuo = {.ActiveLevel = 1, .Res = 0};
CslIOCtrl_Device_Level_TypeDef Device_Liaoji = {.ActiveLevel = 1, .Res = 0};
CslIOCtrl_Device_SCR_TypeDef Device_Gufeng = {.Channel = 0};
CslIOCtrl_Device_SCR_TypeDef Device_Yinfeng = {.Channel = 1};
CslIOCtrl_Device_Level_TypeDef Device_Queliao = {.ActiveLevel = 1, .Res = 1};

CslIOCtrl_RegTypeDef IO_Dianhuo = {.Device.AsLevel = &Device_Dianhuo};
CslIOCtrl_RegTypeDef IO_Liaoji = {.Device.AsLevel = &Device_Liaoji};
CslIOCtrl_RegTypeDef IO_Gufeng = {.Device.AsSCR = &Device_Gufeng};
CslIOCtrl_RegTypeDef IO_Yinfeng = {.Device.AsSCR = &Device_Yinfeng};
CslIOCtrl_RegTypeDef IO_Queliao = {.Device.AsLevel = &Device_Queliao};


volatile HCS_TypeDef HCS_Struct = 
{
	.pParams = &SysParam
};


static void HCS_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
#if BOARD_TYPE == RELEASE_BOARD_V1
	RCC_APB2PeriphClockCmd(
		GPIO2RCC(_IN_W1_GPIO) | GPIO2RCC(_IN_W2_GPIO) | GPIO2RCC(_IN_W3_GPIO) |
		GPIO2RCC(_IN_W4_GPIO) | GPIO2RCC(_IN_TH_GPIO) | GPIO2RCC(_IN_PHH_GPIO) |
		GPIO2RCC(_IN_PH_GPIO) , ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; //GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_InitStruct.GPIO_Pin  = _IN_W1_PIN;
	GPIO_Init(_IN_W1_GPIO, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = _IN_W2_PIN;
	GPIO_Init(_IN_W2_GPIO, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = _IN_W3_PIN;
	GPIO_Init(_IN_W3_GPIO, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = _IN_W4_PIN;
	GPIO_Init(_IN_W4_GPIO, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = _IN_TH_PIN;
	GPIO_Init(_IN_TH_GPIO, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = _IN_PHH_PIN;
	GPIO_Init(_IN_PHH_GPIO, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = _IN_PH_PIN;
	GPIO_Init(_IN_PH_GPIO, &GPIO_InitStruct);
#elif BOARD_TYPE == TEST_BOARD_V1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
#endif
}

static void HCS_Monitor_Init(void)
{
	vTask_Monitor_Init();
}

//用于记录点火前的温度
void HCS_FireUpStore(void)
{
	HCS_Struct.TempBeforeFire = HCS_Struct.StoveTemp.Value;
}

//判断点火是否成功
uint8_t HCS_FireUpCheck(void)
{
	//检测是否点火成功
	if(HCS_Struct.StoveTemp.Value >= HCS_Struct.pParams->Dianhuoyuzhi)
	{
		return 0x00;
	}
	else
	{
		return 0xFF;
	}
}

//防冻功能
uint8_t HCS_AntiFreeze(void)
{
	//炉内水温低于5℃，进入防冻功能，循环泵自动开启防止结冰
	
	//_WaterPump_On_();
	
	//if(HCS_Struct.WaterTemp >= HCS_Struct.Params[HCS_PARAM_TBWD])
	{
		//TODO
	}
	
	return 0;
}

//提示加水
void inline HCS_WaterLowIndicationSet(void)
{
//	myLed_On(LED5);
}

//关闭加水提示
void inline HCS_WaterLowIndicationReset(void)
{
//	myLed_Off(LED5);
}

//提示加料
void inline HCS_MaterialLowIndicationSet(void)
{
//	myLed_On(LED6);
}

//关闭加料提示
void inline HCS_MaterialLowIndicationReset(void)
{
//	myLed_Off(LED6);
}

uint8_t HCS_CheckSysError(void)
{
	//水位从‘开启’到‘关闭’如果出现缺水就报警并进入‘关闭状态’（水位开关量常闭变为开）
	//炉温从‘开启’到‘关闭’如果出现过热就报警并进入‘关闭状态（炉温超过设定值）
	//缺料从‘开启’到‘关闭’如果出现缺料就报警并进入‘关闭状态（缺料开关量常闭变为开，有的客户没有炉温功能，这个开关量设为过热报警，和缺料接一起）
	//if(HCS_GetWaterLow())
	//{
	//	return 0xFF;
	//}
	if(HCS_Struct.MaterialLow)
	{
		return 0xFF;
	}
	if(HCS_Struct.StoveTemp.Flag != 0)
	{
		return 0xFF;    //Exit when stove temperature is not normal
	}
	if(HCS_Struct.StoveTemp.Value > 800)
	{
		return 0xFF;    //Exit when stove temperature is overheat
	}
	
	return 0;
}

void HCS_Init(void)
{
	HCS_Struct.Status = HCS_STATUS_STANDBY;
	
	HCS_IO_Init();
	SCRControl_Init();
	HCS_Monitor_Init();

	//Load Params
	SysParam_LoadFromFlash();
}

//待机状态
uint8_t HCS_SM_Standby(uint8_t param)
{
	//检测水位、缺料、水温、炉温
	//如果水位缺水缺料，提示加水加料；用户自己手动加水加料
	//必须水满才能开机，否则不能开机
	//液晶屏亮着，没有按开关按键开启，可触发水泵防冻功能，不启动水泵循环水功能
	//参数：防冻温度 单位：摄氏度
	
	//HCS_Struct.WaterLow = HCS_GetWaterLow();
	
	//_WaterPump_Off_();   //不启动水泵循环功能
	_AirBlower_Off_();
	_FireUp_Off_();
	_MaterialMachine_Off_();
	_LeadFan_Off_();
	
	//if(HCS_Struct.WaterLow)
	//{
	//	//提示加水
	//	HCS_WaterLowIndicationSet();
	//	//等待加水完成
	//	while(HCS_Struct.WaterLow)
	//	{
	//		HCS_Struct.WaterLow = HCS_GetWaterLow();
	//	}
	//	
	//	HCS_WaterLowIndicationReset();
	//}
	if(HCS_Struct.MaterialLow)
	{
		//提示加料
		HCS_MaterialLowIndicationSet();
	}
	
	return 0;
}

//开启状态
uint8_t HCS_SM_Startup(uint8_t param)
{
	//按开关键开启，检测水位、水温、炉温
	//如果出现超温就报警进入“关闭状态”
	//锅炉运行模式：开启-前吹-预热-预料-点火-运行-保火-关闭
	//水位从‘开启’到‘关闭’如果出现缺水就报警并进入‘关闭状态’（水位开关量常闭变为开）
	//炉温从‘开启’到‘关闭’如果出现过热就报警并进入‘关闭状态（炉温超过设定值）
	//缺料从‘开启’到‘关闭’如果出现缺料就报警并进入‘关闭状态（缺料开关量常闭变为开，有的客户没有炉温功能，这个开关量设为过热报警，和缺料接一起）
	//水泵运行模式：水泵是根据水温独立运行，它是循环泵，把锅炉热水循环出去使用，高温开泵，低温停泵（例如：水泵高于开泵温度70度，开泵；低于停泵温度50度，停泵），水泵在按开关键时就开始工作，暂停或关闭时继续工作，直到停泵，或者按‘电源’键时停止。在暂停待机状态（液晶屏亮着没有进入运行状态）触发‘防冻’功能
	//锅炉运行模式：开启-前吹—预热—预料—点火—运行—保火—暂停—关闭
	//开机时：水温：1.低于‘停机温度’开机，前吹，预料，预热，点火，运行，保火。2.高于‘停机温度’，进入‘暂停’，当水泵把水温循环出去降到‘开机温度’以下，自动开机进入前吹，预料，预热，点火，运行，保火
	uint8_t i;
	
	
	
	if(HCS_CheckSysError())
	{
		for(i=0;i<3;i++)
		{
			MyBeep_Beep(1);
			vTaskDelay(50);
			MyBeep_Beep(0);
			vTaskDelay(50);
		}
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		
		return 0;
	}
	
	/* Beep 1s to start normal */
	MyBeep_Beep(1);
	vTaskDelay(500);
	MyBeep_Beep(0);
	
	/* wait until temperature down to level */
	if(HCS_Struct.WaterTemp.Value > HCS_Struct.pParams->Baohuowendu)
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		//现在高于开机温度，需要等待温度降低
		while(HCS_Struct.WaterTemp.Value > HCS_Struct.pParams->Kaijiwendu)
		{
			if(HCS_Struct.Status == HCS_STATUS_POWEROFF)
			{
				return 0;
			}
		}
		HCS_Struct.Status = HCS_STATUS_PREBLOW;
	}
	if((HCS_Struct.Status != HCS_STATUS_POWEROFF) && (HCS_Struct.Status != HCS_STATUS_STANDBY))
		HCS_Struct.Status = HCS_STATUS_PREBLOW;
	
	return 0;
}

//前吹状态
uint8_t HCS_SM_PreBlowing(uint8_t param)
{
	uint16_t tmpParams[2];
	
	//吹灰尘，启动鼓风机和引风机
	//参数：鼓风前吹，引风前吹  单位:秒
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		return 0;
	}
	
	_AirBlower_On_();
	_LeadFan_On_();
	tmpParams[0] = HCS_Struct.pParams->Gufengqianchui;
	tmpParams[1] = HCS_Struct.pParams->Yinfengqianchui;
	if(tmpParams[1] > tmpParams[0])
	{
		vTaskDelay(tmpParams[0] * 1000);
		_AirBlower_Off_();
		vTaskDelay((tmpParams[1] - tmpParams[0]) * 1000);
		_LeadFan_Off_();
	}
	else
	{
		vTaskDelay(tmpParams[1] * 1000);
		_LeadFan_Off_();
		vTaskDelay((tmpParams[0] - tmpParams[1]) * 1000);
		_AirBlower_Off_();
	}
	if((HCS_Struct.Status != HCS_STATUS_POWEROFF) && (HCS_Struct.Status != HCS_STATUS_STANDBY))
		HCS_Struct.Status = HCS_STATUS_WARMEDUP;    //进入预热状态
	
	return 0;
}

//预热状态
uint8_t HCS_SM_WarmedUp(uint8_t param)
{
	uint16_t tmpParams[2];
	
	//在点火前不吹风，让点火器单独运行，只启动点火
	//参数：预热时间  单位：秒
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;	
		return 0;
	}
	
	_AirBlower_Off_();
	_LeadFan_Off_();
	_FireUp_On_();
	tmpParams[0] = HCS_Struct.pParams->Yinfengzhihou;
	tmpParams[1] = HCS_Struct.pParams->Gufengzhihou;
	if(tmpParams[1] > tmpParams[0])
	{
		vTaskDelay(tmpParams[0] * 1000);
		_LeadFan_On_();
		vTaskDelay((tmpParams[1] - tmpParams[0]) * 1000);
		_AirBlower_On_();
	}
	else
	{
		vTaskDelay(tmpParams[1] * 1000);
		_AirBlower_On_();
		vTaskDelay((tmpParams[0] - tmpParams[1]) * 1000);
		_LeadFan_On_();
	}
	if((HCS_Struct.Status != HCS_STATUS_POWEROFF) && (HCS_Struct.Status != HCS_STATUS_STANDBY))
		HCS_Struct.Status = HCS_STATUS_PREMATERIAL;  //进入预料状态
	return 0;
}

//预料状态
uint8_t HCS_SM_PreMaterial(uint8_t param)
{
	//在点火前先进点料供点火使用，启动料机
	//参数：预料时间  单位：秒
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		return 0;
	}
	
	_MaterialMachine_On_();
	vTaskDelay(HCS_Struct.pParams->Yuliaoshijian * 1000);
	//_MaterialMachine_Off_();
	if((HCS_Struct.Status != HCS_STATUS_POWEROFF) && (HCS_Struct.Status != HCS_STATUS_STANDBY))
		HCS_Struct.Status = HCS_STATUS_FIREUP;    //进入点火状态
	return 0;
}

//点火状态
uint8_t HCS_SM_FireUp(uint8_t param)
{
	uint8_t IsFire = 0;
	uint16_t i;
	//点火器持续发热配合鼓风机送热风，引风机给氧，让锅炉点着火
	//点火过程中达到点火阈值，停止点火
	//超过点火时间延长一个点火时间，关闭点火，再没达到就点火报警
	//点火阈值有开关功能，有的不检测炉温就不需要这个功能
	//引风，鼓风度数可调 在‘点火状态’开始后滞后开启；料机在‘点火状态’结束后滞后开启
	//参数：点火时间，引风滞后，鼓风滞后，料机滞后 单位：秒; 点火阀值 单位：摄氏度；点火间隔 单位：分钟；点火引风，点火鼓风 单位:  %
	
	_FireUp_On_();
	_LeadFan_On_();
	_AirBlower_On_();
	i = HCS_Struct.pParams->Dianhuoshijian * 10;
	do
	{
		vTaskDelay(100);
		i--;
		if(HCS_FireUpCheck() == 0x00)
		{
			IsFire = 1;    //点火成功
			break;
		}
	}while(i>0);
	if((HCS_Struct.pParams->Dianhuoyuzhi != (short)0xFFFF) && (IsFire == 0))
	{
		//有点火阈值需要 则在来一次
		MyBeep_Beep(1);
		vTaskDelay(200);
		MyBeep_Beep(0);
		
		i = HCS_Struct.pParams->Dianhuoshijian * 10;
		do
		{
			vTaskDelay(100);
			i--;
			if(HCS_FireUpCheck() == 0x00)
			{
				IsFire = 1;    //点火成功
				break;
			}
		}while(i>0);
	}
	_FireUp_Off_();
	
	if(!IsFire)
	{
		HCS_Struct.Status = HCS_STATUS_POWEROFF;  //进入关闭模式
		//点火报警
		MyBeep_Beep(1);
		vTaskDelay(100);
		MyBeep_Beep(0);
		vTaskDelay(50);
		MyBeep_Beep(1);
		vTaskDelay(100);
		MyBeep_Beep(0);
		vTaskDelay(50);
		MyBeep_Beep(1);
		vTaskDelay(100);
		MyBeep_Beep(0);
		vTaskDelay(50);
		//
		return 0xFF;
	}
	if((HCS_Struct.Status != HCS_STATUS_POWEROFF) && (HCS_Struct.Status != HCS_STATUS_STANDBY))
		HCS_Struct.Status = HCS_STATUS_RUNNING;     //进入运行模式
	return 0;
}

//运行状态
uint8_t HCS_SM_Running(uint8_t param)
{
	//锅炉点着火后进料加温，料机间歇进料，鼓风，引风的进风量为正常进风量
	//参数：进料时间，停料时间 单位：秒
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		
		return 0;
	}
	
	if(HCS_Struct.WaterTemp.Value >= HCS_Struct.pParams->Baohuowendu)
	{
		if((HCS_Struct.Status != HCS_STATUS_POWEROFF) && (HCS_Struct.Status != HCS_STATUS_STANDBY))
			HCS_Struct.Status = HCS_STATUS_FIREPROTECT;  //进入保火模式
	}
	
	_AirBlower_On_();
	_LeadFan_On_();
	_FireUp_On_();
	_MaterialMachine_On_();
	vTaskDelay(HCS_Struct.pParams->Jinliaoshijian * 1000);
	_MaterialMachine_Off_();
	vTaskDelay(HCS_Struct.pParams->Tingliaoshijian * 1000);
	
	return 0;
}

//保火状态
uint8_t HCS_SM_FireProtection(uint8_t param)
{
	//锅炉到达保火温度转为保火状态
	//温度重新下降到开机温度重新进入运行状态，一直循环到关机状态
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		
		return 0;
	}
	
	if(HCS_Struct.WaterTemp.Value <= HCS_Struct.pParams->Baohuowendu)
	{
		if((HCS_Struct.Status != HCS_STATUS_POWEROFF) && (HCS_Struct.Status != HCS_STATUS_STANDBY))
			HCS_Struct.Status = HCS_STATUS_RUNNING;      //回到运行模式
	}
	
	_AirBlower_On_();
	_LeadFan_On_();
	_FireUp_Off_();
	_MaterialMachine_On_();
	vTaskDelay(HCS_Struct.pParams->Baohuosongliao * 1000);
	_MaterialMachine_Off_();
	vTaskDelay(HCS_Struct.pParams->Baohuotingliao * 1000);
	
	return 0;
}

//暂停状态
uint8_t HCS_SM_Suspend(uint8_t param)
{
	//当水温达到‘停机温度’，料机停，鼓风，引风（度数为保火度数）在后吹延时完成后停
	//当水温下降低于‘开机温度’；1.时间不超过‘点火间隔’，回到‘运行状态’开始，2.时间超过‘点火间隔’，回到‘预料状态’开始
	//参数：鼓风后吹，引风后吹 单位：秒，开机温度，停机温度 单位：摄氏度
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		
		return 0;
	}
	
	return 0;
}

//关闭状态
uint8_t HCS_SM_PowerOff(uint8_t param)
{
	uint16_t tmpParams[2];
	
	//按开关键关闭，锅炉关闭，料机、点火关闭，鼓风、引风在后吹延时完成后停止，再次进入待机界面
	//参数：鼓风后吹，引风后吹  单位：秒
	//关闭状态下才触发防冻功能
	
	_FireUp_Off_();
	//_WaterPump_Off_();
	_MaterialMachine_Off_();
	
	tmpParams[0] = HCS_Struct.pParams->Gufenghouchui;
	tmpParams[1] = HCS_Struct.pParams->Yinfenghouchui;
	if(HCS_Struct.pParams->Gufenghouchui > HCS_Struct.pParams->Yinfenghouchui)
	{
		vTaskDelay(HCS_Struct.pParams->Yinfenghouchui * 1000);
		_LeadFan_Off_();
		vTaskDelay((HCS_Struct.pParams->Gufenghouchui - HCS_Struct.pParams->Yinfenghouchui) * 1000);
		_AirBlower_Off_();
	}
	else
	{
		vTaskDelay(HCS_Struct.pParams->Gufenghouchui * 1000);
		_AirBlower_Off_();
		vTaskDelay((HCS_Struct.pParams->Yinfenghouchui - HCS_Struct.pParams->Gufenghouchui) * 1000);
		_LeadFan_Off_();
	}
	
	//等待开启
	while(1)
	{
		if(HCS_Struct.Status != HCS_STATUS_POWEROFF)
		{
			break;
		}
		//防冻功能
	}
	
	return 0;
}

//Test
uint8_t HCS_SM_Test(uint8_t param)
{
	_FireUp_Off_();
	_MaterialMachine_Off_();
	_AirBlower_Off_();
	_LeadFan_Off_();
	
	while(1)
	{
		if(HCS_Struct.Status != HCS_STATUS_TEST)
		{
			break;
		}
	}
	
	return 0;
}

