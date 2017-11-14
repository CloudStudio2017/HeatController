#include "HeatControlSys.h"
#include "myBeep.h"
#include "FreeRTOS.h"
#include "Task.h"
#include "Task_Monitor.h"

CslIOCtrl_Device_Level_TypeDef Device_Liaoji = {.ActiveLevel = 1, .Res = 0};
CslIOCtrl_Device_Level_TypeDef Device_Dianhuo = {.ActiveLevel = 1, .Res = 0};
CslIOCtrl_Device_Level_TypeDef Device_Shuiwei = {.ActiveLevel = 1, .Res = 0};
CslIOCtrl_Device_Level_TypeDef Device_Queliao = {.ActiveLevel = 1, .Res = 0};
CslIOCtrl_Device_SCR_TypeDef Device_Yinfeng = {.Channel = 0};
CslIOCtrl_Device_SCR_TypeDef Device_Gufeng = {.Channel = 1};

CslIOCtrl_RegTypeDef IO_Liaoji = {.Device.AsLevel = &Device_Liaoji};
CslIOCtrl_RegTypeDef IO_Dianhuo = {.Device.AsLevel = &Device_Dianhuo};
CslIOCtrl_RegTypeDef IO_Shuiwei = {.Device.AsLevel = &Device_Shuiwei};
CslIOCtrl_RegTypeDef IO_Queliao = {.Device.AsLevel = &Device_Queliao};
CslIOCtrl_RegTypeDef IO_Yinfeng = {.Device.AsSCR = &Device_Yinfeng};
CslIOCtrl_RegTypeDef IO_Gufeng = {.Device.AsSCR = &Device_Gufeng};


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

//���ڼ�¼���ǰ���¶�
void HCS_FireUpStore(void)
{
	HCS_Struct.TempBeforeFire = HCS_Struct.StoveTemp.Value;
}

//�жϵ���Ƿ�ɹ�
uint8_t HCS_FireUpCheck(void)
{
	//����Ƿ���ɹ�
	if(HCS_Struct.StoveTemp.Value >= HCS_Struct.pParams->Dianhuoyuzhi)
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
	
	//_WaterPump_On_();
	
	//if(HCS_Struct.WaterTemp >= HCS_Struct.Params[HCS_PARAM_TBWD])
	{
		//TODO
	}
	
	return 0;
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

uint8_t HCS_CheckSysError(void)
{
	//ˮλ�ӡ������������رա��������ȱˮ�ͱ��������롮�ر�״̬����ˮλ���������ձ�Ϊ����
	//¯�´ӡ������������رա�������ֹ��Ⱦͱ��������롮�ر�״̬��¯�³����趨ֵ��
	//ȱ�ϴӡ������������رա��������ȱ�Ͼͱ��������롮�ر�״̬��ȱ�Ͽ��������ձ�Ϊ�����еĿͻ�û��¯�¹��ܣ������������Ϊ���ȱ�������ȱ�Ͻ�һ��
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

//����״̬
uint8_t HCS_SM_Standby(uint8_t param)
{
	//���ˮλ��ȱ�ϡ�ˮ�¡�¯��
	//���ˮλȱˮȱ�ϣ���ʾ��ˮ���ϣ��û��Լ��ֶ���ˮ����
	//����ˮ�����ܿ����������ܿ���
	//Һ�������ţ�û�а����ذ����������ɴ���ˮ�÷������ܣ�������ˮ��ѭ��ˮ����
	//�����������¶� ��λ�����϶�
	
	//HCS_Struct.WaterLow = HCS_GetWaterLow();
	
	//_WaterPump_Off_();   //������ˮ��ѭ������
	_AirBlower_Off_();
	_FireUp_Off_();
	_MaterialMachine_Off_();
	_LeadFan_Off_();
	
	//if(HCS_Struct.WaterLow)
	//{
	//	//��ʾ��ˮ
	//	HCS_WaterLowIndicationSet();
	//	//�ȴ���ˮ���
	//	while(HCS_Struct.WaterLow)
	//	{
	//		HCS_Struct.WaterLow = HCS_GetWaterLow();
	//	}
	//	
	//	HCS_WaterLowIndicationReset();
	//}
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
		//���ڸ��ڿ����¶ȣ���Ҫ�ȴ��¶Ƚ���
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

//ǰ��״̬
uint8_t HCS_SM_PreBlowing(uint8_t param)
{
	uint16_t tmpParams[2];
	
	//���ҳ��������ķ���������
	//�������ķ�ǰ��������ǰ��  ��λ:��
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
		HCS_Struct.Status = HCS_STATUS_WARMEDUP;    //����Ԥ��״̬
	
	return 0;
}

//Ԥ��״̬
uint8_t HCS_SM_WarmedUp(uint8_t param)
{
	uint16_t tmpParams[2];
	
	//�ڵ��ǰ�����磬�õ�����������У�ֻ�������
	//������Ԥ��ʱ��  ��λ����
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
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		return 0;
	}
	
	_MaterialMachine_On_();
	vTaskDelay(HCS_Struct.pParams->Yuliaoshijian * 1000);
	//_MaterialMachine_Off_();
	if((HCS_Struct.Status != HCS_STATUS_POWEROFF) && (HCS_Struct.Status != HCS_STATUS_STANDBY))
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
	_LeadFan_On_();
	_AirBlower_On_();
	i = HCS_Struct.pParams->Dianhuoshijian * 10;
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
	if((HCS_Struct.pParams->Dianhuoyuzhi != (short)0xFFFF) && (IsFire == 0))
	{
		//�е����ֵ��Ҫ ������һ��
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
	if((HCS_Struct.Status != HCS_STATUS_POWEROFF) && (HCS_Struct.Status != HCS_STATUS_STANDBY))
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
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		
		return 0;
	}
	
	if(HCS_Struct.WaterTemp.Value >= HCS_Struct.pParams->Baohuowendu)
	{
		if((HCS_Struct.Status != HCS_STATUS_POWEROFF) && (HCS_Struct.Status != HCS_STATUS_STANDBY))
			HCS_Struct.Status = HCS_STATUS_FIREPROTECT;  //���뱣��ģʽ
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

//����״̬
uint8_t HCS_SM_FireProtection(uint8_t param)
{
	//��¯���ﱣ���¶�תΪ����״̬
	//�¶������½��������¶����½�������״̬��һֱѭ�����ػ�״̬
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		
		return 0;
	}
	
	if(HCS_Struct.WaterTemp.Value <= HCS_Struct.pParams->Baohuowendu)
	{
		if((HCS_Struct.Status != HCS_STATUS_POWEROFF) && (HCS_Struct.Status != HCS_STATUS_STANDBY))
			HCS_Struct.Status = HCS_STATUS_RUNNING;      //�ص�����ģʽ
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

//��ͣ״̬
uint8_t HCS_SM_Suspend(uint8_t param)
{
	//��ˮ�´ﵽ��ͣ���¶ȡ����ϻ�ͣ���ķ磬���磨����Ϊ����������ں���ʱ��ɺ�ͣ
	//��ˮ���½����ڡ������¶ȡ���1.ʱ�䲻����������������ص�������״̬����ʼ��2.ʱ�䳬��������������ص���Ԥ��״̬����ʼ
	//�������ķ�󴵣������ ��λ���룬�����¶ȣ�ͣ���¶� ��λ�����϶�
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		
		return 0;
	}
	
	return 0;
}

//�ر�״̬
uint8_t HCS_SM_PowerOff(uint8_t param)
{
	uint16_t tmpParams[2];
	
	//�����ؼ��رգ���¯�رգ��ϻ������رգ��ķ硢�����ں���ʱ��ɺ�ֹͣ���ٴν����������
	//�������ķ�󴵣������  ��λ����
	//�ر�״̬�²Ŵ�����������
	
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

