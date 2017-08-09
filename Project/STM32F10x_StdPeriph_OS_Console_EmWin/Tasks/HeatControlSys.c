#include "HeatControlSys.h"
#include "myLed.h"
#include "myBeep.h"
#include "FreeRTOS.h"
#include "Task.h"

volatile uint16_t ADCConvertedValue[3];

volatile HCS_TypeDef HCS_Struct;


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
			tmpTemp = (600.0 / 4096.0) * ADCConvertedValue[0];    //K�͵�ż
			break;
		case 1:
			tmpTemp = (150.0 / 4096.0) * ADCConvertedValue[1];   //PT100��ż
			break;
		default:
			return -3000;
	}
	
	return (int16_t)tmpTemp;
}

//���ڼ�¼���ǰ���¶�
void HCS_FireUpStore(void)
{
	HCS_Struct.TempBeforeFire = HCS_GetTemp(0);
}

//�жϵ���Ƿ�ɹ�
uint8_t HCS_FireUpCheck(void)
{
	//����Ƿ���ɹ�
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

//��������
uint8_t HCS_AntiFreeze(void)
{
	//¯��ˮ�µ���5�棬����������ܣ�ѭ�����Զ�������ֹ���
	
	_WaterPump_On_();
	
	HCS_Struct.WaterTemp = HCS_GetTemp(1);
	if(HCS_Struct.WaterTemp >= HCS_Struct.Params[HCS_PARAM_TBWD])
	{
		//TODO
	}
	
	return 0;
}

//���ˮλ���ź�
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

//��ʾ��ˮ
void inline HCS_WaterLowIndicationSet(void)
{
//	myLed_On(LED5);
}

//�رռ�ˮ��ʾ
void inline HCS_WaterLowIndicationReset(void)
{
//	myLed_Off(LED5);
}

//�������ź�
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

//��ʾ����
void inline HCS_MaterialLowIndicationSet(void)
{
//	myLed_On(LED6);
}

//�رռ�����ʾ
void inline HCS_MaterialLowIndicationReset(void)
{
//	myLed_Off(LED6);
}

//���¯��
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
	//ˮλ�ӡ������������رա��������ȱˮ�ͱ��������롮�ر�״̬����ˮλ���������ձ�Ϊ����
	//¯�´ӡ������������رա�������ֹ��Ⱦͱ��������롮�ر�״̬��¯�³����趨ֵ��
	//ȱ�ϴӡ������������رա��������ȱ�Ͼͱ��������롮�ر�״̬��ȱ�Ͽ��������ձ�Ϊ�����еĿͻ�û��¯�¹��ܣ������������Ϊ���ȱ�������ȱ�Ͻ�һ��
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
	HCS_Struct.Params[HCS_PARAM_GFQC] = 2;           //�ķ�ǰ��
	HCS_Struct.Params[HCS_PARAM_YFQC] = 1;           //����ǰ��
	HCS_Struct.Params[HCS_PARAM_YLSJ] = 2;           //Ԥ��ʱ��
	HCS_Struct.Params[HCS_PARAM_YRSJ] = 3;           //Ԥ��ʱ��
	HCS_Struct.Params[HCS_PARAM_DHSJ] = 3;           //���ʱ��
	HCS_Struct.Params[HCS_PARAM_JLSJ] = 2;           //����ʱ��
	HCS_Struct.Params[HCS_PARAM_TLSJ] = 2;           //ͣ��ʱ��
	HCS_Struct.Params[HCS_PARAM_GFHC] = 2;           //�ķ��
	HCS_Struct.Params[HCS_PARAM_YFHC] = 2;           //�����
	HCS_Struct.Params[HCS_PARAM_BHSL] = 2;           //��������
	HCS_Struct.Params[HCS_PARAM_BHTL] = 2;           //����ͣ��
	HCS_Struct.Params[HCS_PARAM_KJWD] = 30;          //�����¶�
	HCS_Struct.Params[HCS_PARAM_TJWD] = 95;          //ͣ���¶�
	HCS_Struct.Params[HCS_PARAM_BHWD] = 90;          //�����¶�
	HCS_Struct.Params[HCS_PARAM_KBWD] = 80;          //�����¶�
	HCS_Struct.Params[HCS_PARAM_TBWD] = 98;          //ͣ���¶�
	HCS_Struct.Params[HCS_PARAM_DSKJ] = 0;           //��ʱ����
	HCS_Struct.Params[HCS_PARAM_DSGJ] = 0;           //��ʱ�ػ�
	
	HCS_Struct.Params[HCS_PARAM_DHYZ] = 20;          //�����ֵ
	HCS_Struct.Params[HCS_PARAM_DHJG] = 4;           //�����
	HCS_Struct.Params[HCS_PARAM_YFZH] = 3;           //�����ͺ�
	HCS_Struct.Params[HCS_PARAM_GFZH] = 3;           //�ķ��ͺ�
	HCS_Struct.Params[HCS_PARAM_DHYF] = 2;           //�������
	HCS_Struct.Params[HCS_PARAM_DHGF] = 2;           //���ķ�
	HCS_Struct.Params[HCS_PARAM_SLZH] = 2;           //�����ͺ�
	HCS_Struct.Params[HCS_PARAM_BJWD] = 600;         //�����¶�
	HCS_Struct.Params[HCS_PARAM_FDWD] = 5;           //�����¶�
	HCS_Struct.Params[HCS_PARAM_ZCYF] = 4;           //��������
	HCS_Struct.Params[HCS_PARAM_ZCGF] = 4;           //�����ķ�
	HCS_Struct.Params[HCS_PARAM_BHYF] = 4;           //��������
	HCS_Struct.Params[HCS_PARAM_BHGF] = 4;           //����ķ�
}

//����״̬
uint8_t HCS_SM_Standby(uint8_t param)
{
	//���ˮλ��ȱ�ϡ�ˮ�¡�¯��
	//���ˮλȱˮȱ�ϣ���ʾ��ˮ���ϣ��û��Լ��ֶ���ˮ����
	//����ˮ�����ܿ����������ܿ���
	//Һ�������ţ�û�а����ذ����������ɴ���ˮ�÷������ܣ�������ˮ��ѭ��ˮ����
	//�����������¶� ��λ�����϶�
	
	HCS_Struct.WaterLow = HCS_GetWaterLow();
	HCS_Struct.MaterialLow = HCS_GetMaterialLow();
	HCS_Struct.StoveTemp = HCS_GetTemp(0);
	HCS_Struct.WaterTemp = HCS_GetTemp(1);
	
	_WaterPump_Off_();   //������ˮ��ѭ������
	_AirBlower_Off_();
	_FireUp_Off_();
	_MaterialMachine_Off_();
	_LeadFan_Off_();
	
	if(HCS_Struct.WaterLow)
	{
		//��ʾ��ˮ
		HCS_WaterLowIndicationSet();
		//�ȴ���ˮ���
		while(HCS_Struct.WaterLow)
		{
			HCS_Struct.WaterLow = HCS_GetWaterLow();
		}
		
		HCS_WaterLowIndicationReset();
	}
	if(HCS_Struct.MaterialLow)
	{
		//��ʾ����
		HCS_MaterialLowIndicationSet();
	}
	
	return 0;
}

//����״̬
uint8_t HCS_SM_Startup(uint8_t param)
{
	//�����ؼ����������ˮλ��ˮ�¡�¯��
	//������ֳ��¾ͱ������롰�ر�״̬��
	//��¯����ģʽ������-ǰ��-Ԥ��-Ԥ��-���-����-����-�ر�
	//ˮλ�ӡ������������رա��������ȱˮ�ͱ��������롮�ر�״̬����ˮλ���������ձ�Ϊ����
	//¯�´ӡ������������رա�������ֹ��Ⱦͱ��������롮�ر�״̬��¯�³����趨ֵ��
	//ȱ�ϴӡ������������رա��������ȱ�Ͼͱ��������롮�ر�״̬��ȱ�Ͽ��������ձ�Ϊ�����еĿͻ�û��¯�¹��ܣ������������Ϊ���ȱ�������ȱ�Ͻ�һ��
	//ˮ������ģʽ��ˮ���Ǹ���ˮ�¶������У�����ѭ���ã��ѹ�¯��ˮѭ����ȥʹ�ã����¿��ã�����ͣ�ã����磺ˮ�ø��ڿ����¶�70�ȣ����ã�����ͣ���¶�50�ȣ�ͣ�ã���ˮ���ڰ����ؼ�ʱ�Ϳ�ʼ��������ͣ��ر�ʱ����������ֱ��ͣ�ã����߰�����Դ����ʱֹͣ������ͣ����״̬��Һ��������û�н�������״̬������������������
	//��¯����ģʽ������-ǰ����Ԥ�ȡ�Ԥ�ϡ�������С�������ͣ���ر�
	//����ʱ��ˮ�£�1.���ڡ�ͣ���¶ȡ�������ǰ����Ԥ�ϣ�Ԥ�ȣ�������У�����2.���ڡ�ͣ���¶ȡ������롮��ͣ������ˮ�ð�ˮ��ѭ����ȥ�����������¶ȡ����£��Զ���������ǰ����Ԥ�ϣ�Ԥ�ȣ�������У�����
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

//ǰ��״̬
uint8_t HCS_SM_PreBlowing(uint8_t param)
{
	uint16_t tmpParams[2];
	
	//���ҳ��������ķ���������
	//�������ķ�ǰ��������ǰ��  ��λ:��
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
	HCS_Struct.Status = HCS_STATUS_WARMEDUP;    //����Ԥ��״̬
	
	return 0;
}

//Ԥ��״̬
uint8_t HCS_SM_WarmedUp(uint8_t param)
{
	//�ڵ��ǰ�����磬�õ�����������У�ֻ�������
	//������Ԥ��ʱ��  ��λ����
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_POWEROFF;	
		return 0;
	}
	
	_AirBlower_Off_();
	_LeadFan_Off_();
	_FireUp_On_();
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_YRSJ] * 1000);
	HCS_Struct.Status = HCS_STATUS_PREMATERIAL;  //����Ԥ��״̬
	return 0;
}

//Ԥ��״̬
uint8_t HCS_SM_PreMaterial(uint8_t param)
{
	//�ڵ��ǰ�Ƚ����Ϲ����ʹ�ã������ϻ�
	//������Ԥ��ʱ��  ��λ����
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_POWEROFF;
		return 0;
	}
	
	_MaterialMachine_On_();
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_YLSJ] * 1000);
	_MaterialMachine_Off_();
	HCS_Struct.Status = HCS_STATUS_FIREUP;    //������״̬
	return 0;
}

//���״̬
uint8_t HCS_SM_FireUp(uint8_t param)
{
	uint8_t IsFire = 0;
	uint16_t i;
	//���������������Ϲķ�����ȷ磬������������ù�¯���Ż�
	//�������дﵽ�����ֵ��ֹͣ���
	//�������ʱ���ӳ�һ�����ʱ�䣬�رյ����û�ﵽ�͵�𱨾�
	//�����ֵ�п��ع��ܣ��еĲ����¯�¾Ͳ���Ҫ�������
	//���磬�ķ�����ɵ� �ڡ����״̬����ʼ���ͺ������ϻ��ڡ����״̬���������ͺ���
	//���������ʱ�䣬�����ͺ󣬹ķ��ͺ��ϻ��ͺ� ��λ����; ���ֵ ��λ�����϶ȣ������ ��λ�����ӣ�������磬���ķ� ��λ:  %
	
	
	_FireUp_On_();
	i = HCS_Struct.Params[HCS_PARAM_DHSJ] * 10;
	do
	{
		vTaskDelay(100);
		i--;
		if(HCS_FireUpCheck() == 0x00)
		{
			IsFire = 1;    //���ɹ�
			break;
		}
	}while(i>0);
	if((HCS_Struct.Params[HCS_PARAM_DHYZ] != 0xFFFF) && 
		 (IsFire == 0))
	{
		//�е����ֵ��Ҫ ������һ��
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
				IsFire = 1;    //���ɹ�
				break;
			}
		}while(i>0);
	}
	_FireUp_Off_();
	
	if(!IsFire)
	{
		HCS_Struct.Status = HCS_STATUS_POWEROFF;  //����ر�ģʽ
		//��𱨾�
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
	HCS_Struct.Status = HCS_STATUS_RUNNING;     //��������ģʽ
	return 0;
}

//����״̬
uint8_t HCS_SM_Running(uint8_t param)
{
	//��¯���Ż����ϼ��£��ϻ���Ъ���ϣ��ķ磬����Ľ�����Ϊ����������
	//����������ʱ�䣬ͣ��ʱ�� ��λ����
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_POWEROFF;
		
		return 0;
	}
	
	HCS_Struct.WaterTemp = HCS_GetTemp(1);
	if(HCS_Struct.WaterTemp >= HCS_Struct.Params[HCS_PARAM_BHWD])
	{
		HCS_Struct.Status = HCS_STATUS_FIREPROTECT;  //���뱣��ģʽ
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

//����״̬
uint8_t HCS_SM_FireProtection(uint8_t param)
{
	//��¯���ﱣ���¶�תΪ����״̬
	//�¶������½��������¶����½�������״̬��һֱѭ�����ػ�״̬
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_POWEROFF;
		
		return 0;
	}
	
	HCS_Struct.WaterTemp = HCS_GetTemp(1);
	if(HCS_Struct.WaterTemp <= HCS_Struct.Params[HCS_PARAM_KJWD])
	{
		HCS_Struct.Status = HCS_STATUS_RUNNING;      //�ص�����ģʽ
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

//��ͣ״̬
uint8_t HCS_SM_Suspend(uint8_t param)
{
	//��ˮ�´ﵽ��ͣ���¶ȡ����ϻ�ͣ���ķ磬���磨����Ϊ����������ں���ʱ��ɺ�ͣ
	//��ˮ���½����ڡ������¶ȡ���1.ʱ�䲻����������������ص�������״̬����ʼ��2.ʱ�䳬��������������ص���Ԥ��״̬����ʼ
	//�������ķ�󴵣������ ��λ���룬�����¶ȣ�ͣ���¶� ��λ�����϶�
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_POWEROFF;
		
		return 0;
	}
	
	return 0;
}

//�ر�״̬
uint8_t HCS_SM_PowerOff(uint8_t param)
{
	//�����ؼ��رգ���¯�رգ��ϻ������رգ��ķ硢�����ں���ʱ��ɺ�ֹͣ���ٴν����������
	//�������ķ�󴵣������  ��λ����
	//�ر�״̬�²Ŵ�����������
	
	_FireUp_Off_();
	_WaterPump_Off_();
	_MaterialMachine_Off_();
	
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_GFHC]);
	_AirBlower_Off_();
	vTaskDelay(HCS_Struct.Params[HCS_PARAM_YFHC]);
	_LeadFan_Off_();
	
	//�ȴ�����
	while(1)
	{
		if(HCS_Struct.Status != HCS_STATUS_POWEROFF)
		{
			break;
		}
		//��������
	}
	
	return 0;
}

