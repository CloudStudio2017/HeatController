#include "HeatControlSys.h"
#include "myLed.h"
#include "myBeep.h"
#include "FreeRTOS.h"
#include "Task.h"

volatile uint16_t ADCConvertedValue[3];

volatile HCS_TypeDef HCS_Struct;

/*  开启/关闭 水泵  */
#define _WaterPump_On_()   do{ \
		myLed_On(0);               \
		HCS_Struct.WaterPump = 1;  \
	}while(0)
#define _WaterPump_Off_()  do{ \
		myLed_Off(0);              \
		HCS_Struct.WaterPump = 0;  \
}while(0)
/*  开启/关闭 物料机  */
#define _MaterialMachine_On_()     do{ \
		myLed_On(1);                       \
		HCS_Struct.MaterialMachine = 1;    \
	}while(0)
#define _MaterialMachine_Off_()    do{ \
		myLed_Off(1);                      \
		HCS_Struct.MaterialMachine = 0;    \
}while(0)
/*  开启/关闭 点火器  */
#define _FireUp_On_()       do{ \
		myLed_On(2);                \
		HCS_Struct.FireUp = 1;      \
	}while(0)
#define _FireUp_Off_()      do{ \
		myLed_Off(2);               \
		HCS_Struct.FireUp = 0;      \
}while(0)
/*  开启/关闭 吹风机  */
#define _AirBlower_On_()    do{ \
		myLed_On(3);                \
		HCS_Struct.AirBlower = 1;   \
	}while(0)
#define _AirBlower_Off_()   do{ \
		myLed_Off(3);               \
		HCS_Struct.AirBlower = 0;   \
}while(0)
/*  开启/关闭 引风机  */
#define _LeadFan_On_()      do{ \
		myLed_On(4);                \
		HCS_Struct.LeadFan = 1;     \
	}while(0)
#define _LeadFan_Off_()     do{ \
		myLed_Off(4);               \
		HCS_Struct.LeadFan = 0;     \
}while(0)


static void HCS_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}

#define ADC1_DR_Address    ((uint32_t)0x4001244C)

static void HCS_ADC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	DMA_DeInit(DMA1_Channel1);
  DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStruct.DMA_MemoryBaseAddr     = (uint32_t)&ADCConvertedValue;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = 3;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_High;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStruct);
	
	
	ADC_InitStruct.ADC_Mode               = ADC_Mode_Independent;
  ADC_InitStruct.ADC_ScanConvMode       = ENABLE;
  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStruct.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
  ADC_InitStruct.ADC_DataAlign          = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_NbrOfChannel       = 3;
  ADC_Init(ADC1, &ADC_InitStruct);
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_55Cycles5);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_DMACmd(ADC1, ENABLE);
	
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

static int16_t HCS_GetTemp(uint8_t Channel)
{
	float tmpTemp;
	
	switch(Channel)
	{
		case 0:
			tmpTemp = (600.0 / 4096.0) * ADCConvertedValue[0];    //K型电偶
			break;
		case 1:
			tmpTemp = (150.0 / 4096.0) * ADCConvertedValue[1];   //PT100电偶
			break;
		default:
			return -3000;
	}
	
	return (int16_t)tmpTemp;
}

//用于记录点火前的温度
void HCS_FireUpStore(void)
{
	HCS_Struct.TempBeforeFire = HCS_GetTemp(0);
}

//判断点火是否成功
uint8_t HCS_FireUpCheck(void)
{
	//检测是否点火成功
	HCS_Struct.StoveTemp = HCS_GetTemp(0);
	if(HCS_Struct.StoveTemp >= HCS_Struct.Params[HCS_PARAM_DHYZ])
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
	
	_WaterPump_On_();
	
	HCS_Struct.WaterTemp = HCS_GetTemp(1);
	if(HCS_Struct.WaterTemp >= HCS_Struct.Params[HCS_PARAM_TBWD])
	{
		//TODO
	}
	
	return 0;
}

//检测水位低信号
uint16_t HCS_GetWaterLow(void)
{
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) != RESET)
	{
		return 1;  //Water is low
	}
	else
	{
		return 0;
	}
}

//提示加水
void inline HCS_WaterLowIndicationSet(void)
{
	myLed_On(LED5);
}

//关闭加水提示
void inline HCS_WaterLowIndicationReset(void)
{
	myLed_Off(LED5);
}

//检测加料信号
uint16_t HCS_GetMaterialLow(void)
{
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) != RESET)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//提示加料
void inline HCS_MaterialLowIndicationSet(void)
{
	myLed_On(LED6);
}

//关闭加料提示
void inline HCS_MaterialLowIndicationReset(void)
{
	myLed_Off(LED6);
}

//检测炉温
uint8_t HCS_GetStoveOverHeat(void)
{
	HCS_Struct.StoveTemp =HCS_GetTemp(0);
	if(HCS_Struct.StoveTemp > HCS_Struct.Params[HCS_PARAM_BJWD])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

uint8_t HCS_CheckSysError(void)
{
	//水位从‘开启’到‘关闭’如果出现缺水就报警并进入‘关闭状态’（水位开关量常闭变为开）
	//炉温从‘开启’到‘关闭’如果出现过热就报警并进入‘关闭状态（炉温超过设定值）
	//缺料从‘开启’到‘关闭’如果出现缺料就报警并进入‘关闭状态（缺料开关量常闭变为开，有的客户没有炉温功能，这个开关量设为过热报警，和缺料接一起）
	if(HCS_GetWaterLow())
	{
		return 0xFF;
	}
	if(HCS_GetMaterialLow())
	{
		return 0xFF;
	}
	if(HCS_GetStoveOverHeat())
	{
		return 0xFF;
	}
	
	return 0;
}

void HCS_Init(void)
{
	HCS_Struct.Status = HCS_STATUS_POWEROFF;
	
	HCS_IO_Init();
	HCS_ADC_Init();
	
	//Load Params
	HCS_Struct.Params[HCS_PARAM_GFQC] = 2;           //鼓风前吹
	HCS_Struct.Params[HCS_PARAM_YFQC] = 1;           //引风前吹
	HCS_Struct.Params[HCS_PARAM_YLSJ] = 2;           //预料时间
	HCS_Struct.Params[HCS_PARAM_YRSJ] = 3;           //预热时间
	HCS_Struct.Params[HCS_PARAM_DHSJ] = 3;           //点火时间
	HCS_Struct.Params[HCS_PARAM_JLSJ] = 2;           //进料时间
	HCS_Struct.Params[HCS_PARAM_TLSJ] = 2;           //停料时间
	HCS_Struct.Params[HCS_PARAM_GFHC] = 2;           //鼓风后吹
	HCS_Struct.Params[HCS_PARAM_YFHC] = 2;           //引风后吹
	HCS_Struct.Params[HCS_PARAM_BHSL] = 2;           //保火送料
	HCS_Struct.Params[HCS_PARAM_BHTL] = 2;           //保火停料
	HCS_Struct.Params[HCS_PARAM_KJWD] = 30;          //开机温度
	HCS_Struct.Params[HCS_PARAM_TJWD] = 95;          //停机温度
	HCS_Struct.Params[HCS_PARAM_BHWD] = 90;          //保火温度
	HCS_Struct.Params[HCS_PARAM_KBWD] = 80;          //开泵温度
	HCS_Struct.Params[HCS_PARAM_TBWD] = 98;          //停泵温度
	HCS_Struct.Params[HCS_PARAM_DSKJ] = 0;           //定时开机
	HCS_Struct.Params[HCS_PARAM_DSGJ] = 0;           //定时关机
	
	HCS_Struct.Params[HCS_PARAM_DHYZ] = 20;          //点火阈值
	HCS_Struct.Params[HCS_PARAM_DHJG] = 4;           //点火间隔
	HCS_Struct.Params[HCS_PARAM_YFZH] = 3;           //引风滞后
	HCS_Struct.Params[HCS_PARAM_GFZH] = 3;           //鼓风滞后
	HCS_Struct.Params[HCS_PARAM_DHYF] = 2;           //点火引风
	HCS_Struct.Params[HCS_PARAM_DHGF] = 2;           //点火鼓风
	HCS_Struct.Params[HCS_PARAM_SLZH] = 2;           //送料滞后
	HCS_Struct.Params[HCS_PARAM_BJWD] = 600;         //报警温度
	HCS_Struct.Params[HCS_PARAM_FDWD] = 5;           //防冻温度
	HCS_Struct.Params[HCS_PARAM_ZCYF] = 4;           //正常引风
	HCS_Struct.Params[HCS_PARAM_ZCGF] = 4;           //正常鼓风
	HCS_Struct.Params[HCS_PARAM_BHYF] = 4;           //保火引风
	HCS_Struct.Params[HCS_PARAM_BHGF] = 4;           //保火鼓风
}

//待机状态
uint8_t HCS_SM_Standby(uint8_t param)
{
	//检测水位、缺料、水温、炉温
	//如果水位缺水缺料，提示加水加料；用户自己手动加水加料
	//必须水满才能开机，否则不能开机
	//液晶屏亮着，没有按开关按键开启，可触发水泵防冻功能，不启动水泵循环水功能
	//参数：防冻温度 单位：摄氏度
	
	HCS_Struct.WaterLow = HCS_GetWaterLow();
	HCS_Struct.MaterialLow = HCS_GetMaterialLow();
	HCS_Struct.StoveTemp = HCS_GetTemp(0);
	HCS_Struct.WaterTemp = HCS_GetTemp(1);
	
	_WaterPump_Off_();   //不启动水泵循环功能
	_AirBlower_Off_();
	_FireUp_Off_();
	_MaterialMachine_Off_();
	_LeadFan_Off_();
	
	if(HCS_Struct.WaterLow)
	{
		//提示加水
		HCS_WaterLowIndicationSet();
		//等待加水完成
		while(HCS_Struct.WaterLow)
		{
			HCS_Struct.WaterLow = HCS_GetWaterLow();
		}
		
		HCS_WaterLowIndicationReset();
	}
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
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_POWEROFF;
		
		return 0;
	}
	
	HCS_Struct.WaterLow = HCS_GetWaterLow();
	HCS_Struct.StoveTemp = HCS_GetTemp(0);
	HCS_Struct.WaterTemp = HCS_GetTemp(1);
	
	if(HCS_Struct.WaterTemp > HCS_Struct.Params[HCS_PARAM_BJWD])
	{
		HCS_Struct.Status = HCS_STATUS_POWEROFF;
		return 0;
	}
	vTaskDelay(1000);
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
		HCS_Struct.Status = HCS_STATUS_POWEROFF;
		return 0;
	}
	
	_AirBlower_On_();
	_LeadFan_On_();
	tmpParams[0] = HCS_Struct.Params[HCS_PARAM_GFQC];
	tmpParams[1] = HCS_Struct.Params[HCS_PARAM_YFQC];
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
	HCS_Struct.Status = HCS_STATUS_WARMEDUP;    //进入预热状态
	
	return 0;
}

//预热状态
uint8_t HCS_SM_WarmedUp(uint8_t param)
{
	//在点火前不吹风，让点火器单独运行，只启动点火
	//参数：预热时间  单位：秒
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_POWEROFF;	
		return 0;
	}
	
	_AirBlower_Off_();
	_LeadFan_Off_();
	_FireUp_On_();
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_YRSJ] * 1000);
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
		HCS_Struct.Status = HCS_STATUS_POWEROFF;
		return 0;
	}
	
	_MaterialMachine_On_();
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_YLSJ] * 1000);
	_MaterialMachine_Off_();
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
	i = HCS_Struct.Params[HCS_PARAM_DHSJ] * 10;
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
	if((HCS_Struct.Params[HCS_PARAM_DHYZ] != 0xFFFF) && 
		 (IsFire == 0))
	{
		//有点火阈值需要 则在来一次
		MyBeep_Beep(1);
		vTaskDelay(200);
		MyBeep_Beep(0);
		
		i = HCS_Struct.Params[HCS_PARAM_DHSJ] * 10;
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
		HCS_Struct.Status = HCS_STATUS_POWEROFF;
		
		return 0;
	}
	
	HCS_Struct.WaterTemp = HCS_GetTemp(1);
	if(HCS_Struct.WaterTemp >= HCS_Struct.Params[HCS_PARAM_BHWD])
	{
		HCS_Struct.Status = HCS_STATUS_FIREPROTECT;  //进入保火模式
	}
	
	_AirBlower_On_();
	_LeadFan_On_();
	_FireUp_On_();
	_MaterialMachine_On_();
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_JLSJ] * 1000);
	_MaterialMachine_Off_();
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_TLSJ] * 1000);
	
	return 0;
}

//保火状态
uint8_t HCS_SM_FireProtection(uint8_t param)
{
	//锅炉到达保火温度转为保火状态
	//温度重新下降到开机温度重新进入运行状态，一直循环到关机状态
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_POWEROFF;
		
		return 0;
	}
	
	HCS_Struct.WaterTemp = HCS_GetTemp(1);
	if(HCS_Struct.WaterTemp <= HCS_Struct.Params[HCS_PARAM_KJWD])
	{
		HCS_Struct.Status = HCS_STATUS_RUNNING;      //回到运行模式
	}
	
	_AirBlower_On_();
	_LeadFan_On_();
	_FireUp_Off_();
	_MaterialMachine_On_();
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_BHSL] * 1000);
	_MaterialMachine_Off_();
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_BHTL] * 1000);
	
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
		HCS_Struct.Status = HCS_STATUS_POWEROFF;
		
		return 0;
	}
	
	return 0;
}

//关闭状态
uint8_t HCS_SM_PowerOff(uint8_t param)
{
	//按开关键关闭，锅炉关闭，料机、点火关闭，鼓风、引风在后吹延时完成后停止，再次进入待机界面
	//参数：鼓风后吹，引风后吹  单位：秒
	//关闭状态下才触发防冻功能
	
	_FireUp_Off_();
	_WaterPump_Off_();
	_MaterialMachine_Off_();
	
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_GFHC]);
	_AirBlower_Off_();
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_YFHC]);
	_LeadFan_Off_();
	
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

