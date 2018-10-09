#include "HeatControlSys.h"
#include "FreeRTOS.h"
#include "Task.h"
#include "Task_Beep.h"
#include "Task_Monitor.h"
#include "cslRTC.h"
#include "cslLCD.h"
#include "Task_DeviceControl.h"


extern Device_t dev_Fire;
extern Device_t dev_Feeder;
extern Device_t dev_LeadFan;
extern Device_t dev_Blower;

#define DEVICE_COUNT  4
DCB_t devs[DEVICE_COUNT]=
{
	{.Device = &dev_Fire},
	{.Device = &dev_Feeder},
	{.Device = &dev_LeadFan},
	{.Device = &dev_Blower},
};


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

static CslRTC_Time HCS_Time;


static TickType_t Start_Tick;
static uint8_t flag;

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
	
	DeviceControl_Init(devs, DEVICE_COUNT);
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
	return 0;
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
	HCS_Struct.Status = HCS_STATUS_POWEROFF;
	
	//Load Params
	SysParam_LoadFromFlash();
	
	HCS_IO_Init();
	SCRControl_Init();
	HCS_Monitor_Init();
}

//����״̬    ******����****������******
uint8_t HCS_SM_Standby(uint8_t param)
{
	//���ˮλ��ȱ�ϡ�ˮ�¡�¯��
	//���ˮλȱˮȱ�ϣ���ʾ��ˮ���ϣ��û��Լ��ֶ���ˮ����
	//����ˮ�����ܿ����������ܿ���
	//Һ�������ţ�û�а����ذ����������ɴ���ˮ�÷������ܣ�������ˮ��ѭ��ˮ����
	//�����������¶� ��λ�����϶�
	
	//���̣��ķ�ر� -> ���ر� -> ���Ϲر� -> ����ر� -> ���ȱ�� ��
	//                                                ��-----------
	
	switch(param)
	{
		case 0:
			DeviceControl_SendMsg_Stop(ID_DEV_BLOWER);
			DeviceControl_SendMsg_Stop(ID_DEV_FIRE);
			DeviceControl_SendMsg_Stop(ID_DEV_FEEDER);
			DeviceControl_SendMsg_Stop(ID_DEV_LEADFAN);
			param++;
			break;
		case 1:
			if(HCS_Struct.MaterialLow)
			{
				//��ʾ����
				HCS_MaterialLowIndicationSet();
			}
			break;
	}
	return param;
}

//����״̬    ******����****������******
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
		//Task_Beep(3, 50, 50);
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		return 0;
	}
	switch(param)
	{
		case 0:
			/* Beep 1s to start normal */
			//Task_Beep(1, 500, 0);
			param++;
		case 1:
			if(HCS_Struct.WaterTemp.Value > HCS_Struct.pParams->Baohuowendu)
			{
				//TODO : ��ʾ��ǰ�¶ȴ��ڱ����¶�  beep?
			}
			else
			{
				param++;
			}
			break;
		case 2:
			/* wait until temperature down to level */
			if(HCS_Struct.WaterTemp.Value < HCS_Struct.pParams->Kaijiwendu)
			{
				param++;
			}
			HCS_Struct.Status = HCS_STATUS_PREBLOW;         //����ǰ��״̬
			return 0;
	}
	return param;
}

//ǰ��״̬    ******����****������******
uint8_t HCS_SM_PreBlowing(uint8_t param)
{	
	//���ҳ��������ķ���������
	//�������ķ�ǰ��������ǰ��  ��λ:��
	
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		return 0;
	}
	switch(param)
	{
		case 0:
			DeviceControl_SendMsg_Set(ID_DEV_BLOWER, HCS_Struct.pParams->Zhengchanggufeng);
			DeviceControl_SendMsg_Set(ID_DEV_LEADFAN, HCS_Struct.pParams->Zhengchangyinfeng);
			Start_Tick = xTaskGetTickCount();
			flag = 0;
			param++;
			break;
		case 1:
			if((!(flag & 0x1)) && ((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Gufengqianchui * 1000))
			{
				DeviceControl_SendMsg_Stop(ID_DEV_BLOWER);
				flag |= 0x1;
			}
			if((!(flag & 0x2)) && ((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Yinfengqianchui * 1000))
			{
				DeviceControl_SendMsg_Stop(ID_DEV_LEADFAN);
				flag |= 0x2;
			}
			if((flag & 0x3) == 0x3)
			{
				param++;
			}
			break;
		case 2:
			HCS_Struct.Status = HCS_STATUS_WARMEDUP;    //����Ԥ��״̬
			return 0;
	}
	return param;
}

//Ԥ��״̬  ******����****������******
uint8_t HCS_SM_WarmedUp(uint8_t param)
{	
	//�ڵ��ǰ�����磬�õ�����������У�ֻ�������
	//������Ԥ��ʱ��  ��λ����
	
	//���̣����� -> Ԥ��ʱ�䵽 -> ���ر� -> ����Ԥ��
	
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		return 0;
	}
	switch(param)
	{
		case 0:
			DeviceControl_SendMsg_Run(ID_DEV_FIRE);
			Start_Tick = xTaskGetTickCount();
			flag = 0;
			param++;
			break;
		case 1:
			if((!(flag & 0x1) && ((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Yureshijian * 1000)))
			{
				DeviceControl_SendMsg_Run(ID_DEV_FIRE);
				flag |= 0x1;
			}
			if((flag & 0x1) == 0x1)
			{
				param++;
			}
			break;
		case 2:
			HCS_Struct.Status = HCS_STATUS_PREMATERIAL;  //����Ԥ��״̬
			return 0;
	}
	return param;
}

//Ԥ��״̬    ******����****������******
uint8_t HCS_SM_PreMaterial(uint8_t param)
{
	//�ڵ��ǰ�Ƚ����Ϲ����ʹ�ã������ϻ�
	//������Ԥ��ʱ��  ��λ����
	
	//���̣����ϴ� -> Ԥ��ʱ�䵽 -> ���Ϲر� -> ���
	
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;
		return 0;
	}
	switch(param)
	{
		case 0:
			DeviceControl_SendMsg_Run(ID_DEV_FEEDER);
			Start_Tick = xTaskGetTickCount();
			flag = 0;
			param++;
			break;
		case 1:
			if((!(flag & 0x1)) && ((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Yuliaoshijian * 1000))
			{
				DeviceControl_SendMsg_Stop(ID_DEV_FEEDER);
				flag |= 0x1;
			}
			if((flag & 0x1) == 0x1)
			{
				param++;
			}
			break;
		case 2:
			HCS_Struct.Status = HCS_STATUS_FIREUP;    //������״̬
			return 0;
	}
	return param;
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
	
	//���̣����� -> �������ֵ ---> ���ر� -> �ϻ��� -> �ϻ��ͺ�ʱ�䵽 -> �ϻ��ر� -> ��������״̬
	//             ��   δ�ﵽ��    �ﵽ
	//              <-------- -------> �ٴε����û�ﵽ�͵�𱨾� -> �������״̬
	//                δ��ʱ    ��ʱ
	//   -> ����� -> �����ͺ�ʱ�䵽 -> ����ر�
	//   -> �ķ�� -> �ķ��ͺ�ʱ�䵽 -> �ķ�ر�
	switch(param)
	{
		case 0:
			DeviceControl_SendMsg_Run(ID_DEV_FIRE);
			DeviceControl_SendMsg_Set(ID_DEV_LEADFAN, HCS_Struct.pParams->Dianhuoyinfeng);
			DeviceControl_SendMsg_Set(ID_DEV_BLOWER, HCS_Struct.pParams->Dianhuogufeng);
			Start_Tick = xTaskGetTickCount();
			param++;
			break;
		case 1:
			if(HCS_FireUpCheck() == 0x00)
			{
				param = 4;       //���ɹ�
				break;
			}
			if((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Dianhuoshijian * 1000)
			{
				//TODO : alarm beep
				param = 2;       //first fire time up, try it again
				break;
			}
			break;
		case 2:
			if(HCS_FireUpCheck() == 0x00)
			{
				param = 4;       //���ɹ�
				break;
			}
			if((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Dianhuoshijian * 1000)
			{
				//TODO : alarm beep
				HCS_Struct.Status = HCS_STATUS_STANDBY;
				return 0;
				break;
			}
			break;
		case 3:
			param++;
		case 4:
			DeviceControl_SendMsg_Run(ID_DEV_FEEDER);
			Start_Tick = xTaskGetTickCount();
			param++;
		case 5:
			if((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Songliaozhihou * 1000)
			{
				DeviceControl_SendMsg_Stop(ID_DEV_FEEDER);
				HCS_Struct.Status = HCS_STATUS_RUNNING;     //��������ģʽ
				return 0;
			}
			break;
	}
	return param;
}

//����״̬    ******����****������******
uint8_t HCS_SM_Running(uint8_t param)
{
	//��¯���Ż����ϼ��£��ϻ���Ъ���ϣ��ķ磬����Ľ�����Ϊ����������
	//����������ʱ�䣬ͣ��ʱ�� ��λ����
	
	//���̣����� -> �ķ�� -> ����� -> �ϻ��� -> ����ʱ�䵽 -> �ϻ��ر� ->ͣ��ʱ�䵽
	//                                           ��                                  ��
	//                                            ------------------------------------
	//      ���ڱ����¶� -> ���뱣��ģʽ
	
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;	
		return 0;
	}
	
	switch(param)
	{
		case 0:
			DeviceControl_SendMsg_Run(ID_DEV_FIRE);
			DeviceControl_SendMsg_Set(ID_DEV_BLOWER, HCS_Struct.pParams->Zhengchanggufeng);
			DeviceControl_SendMsg_Set(ID_DEV_LEADFAN, HCS_Struct.pParams->Zhengchangyinfeng);
			param++;
		case 1:
			DeviceControl_SendMsg_Run(ID_DEV_FEEDER);
			Start_Tick = xTaskGetTickCount();
		case 2:
			if(HCS_Struct.WaterTemp.Value >= HCS_Struct.pParams->Baohuowendu)
			{
				HCS_Struct.Status = HCS_STATUS_FIREPROTECT;  //���뱣��ģʽ
				return 0;
			}
			if((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Jinliaoshijian * 1000)
			{
				param = 3;
			}
			break;
		case 3:
			DeviceControl_SendMsg_Stop(ID_DEV_FEEDER);
			Start_Tick = xTaskGetTickCount();
		case 4:
			if(HCS_Struct.WaterTemp.Value >= HCS_Struct.pParams->Baohuowendu)
			{
				HCS_Struct.Status = HCS_STATUS_FIREPROTECT;  //���뱣��ģʽ
				return 0;
			}
			if((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Tingliaoshijian * 1000)
			{
				param = 1;
			}
	}
	return param;
}

//����״̬    ******����****������******
uint8_t HCS_SM_FireProtection(uint8_t param)
{
	//��¯���ﱣ���¶�תΪ����״̬
	//�¶������½��������¶����½�������״̬��һֱѭ�����ػ�״̬
	
	//���̣����ر� -> �ķ�� -> ����� -> �ϻ��� -> ����ʱ�䵽 -> �ϻ��ر� ->ͣ��ʱ�䵽
	//                 ������    ������       ��                                  ��
	//                                            ------------------------------------
	//      ���ڱ����¶� -> ��������ģʽ
	
	if(HCS_CheckSysError())
	{
		HCS_Struct.Status = HCS_STATUS_STANDBY;	
		return 0;
	}
	
	switch(param)
	{
		case 0:
			DeviceControl_SendMsg_Stop(ID_DEV_FIRE);
			DeviceControl_SendMsg_Set(ID_DEV_BLOWER, HCS_Struct.pParams->Baohuogufeng);
			DeviceControl_SendMsg_Set(ID_DEV_LEADFAN, HCS_Struct.pParams->Baohuoyinfeng);
			param++;
		case 1:
			DeviceControl_SendMsg_Run(ID_DEV_FEEDER);
			Start_Tick = xTaskGetTickCount();
		case 2:
			if(HCS_Struct.WaterTemp.Value < HCS_Struct.pParams->Baohuowendu)
			{
				HCS_Struct.Status = HCS_STATUS_RUNNING;  //��������ģʽ
				return 0;
			}
			if((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Baohuosongliao * 1000)
			{
				param = 3;
			}
			break;
		case 3:
			DeviceControl_SendMsg_Stop(ID_DEV_FEEDER);
			Start_Tick = xTaskGetTickCount();
		case 4:
			if(HCS_Struct.WaterTemp.Value < HCS_Struct.pParams->Baohuowendu)
			{
				HCS_Struct.Status = HCS_STATUS_RUNNING;  //��������ģʽ
				return 0;
			}
			if((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Baohuotingliao * 1000)
			{
				param = 1;
			}
	}
	return param;
}

//��ͣ״̬  *****��ʱ��֧��******
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

//����
uint8_t HCS_SM_PowerOn(uint8_t param)
{
	return 0;
}

//�ر�״̬
uint8_t HCS_SM_PowerOff(uint8_t param)
{
	return 0;
}

//ֹͣ  ******����****������*******
uint8_t HCS_SM_Stopping(uint8_t param)
{	
	//�����ؼ��رգ���¯�رգ��ϻ������رգ��ķ硢�����ں���ʱ��ɺ�ֹͣ���ٴν����������
	//�������ķ�󴵣������  ��λ����
	//�ر�״̬�²Ŵ�����������
	
	//���̣����Ϲر� -> ���ر� ��
	//                          -> �ķ�� -> �ķ�ʱ�䵽 -> �ķ�ر�
	//                          -> ����� -> ����ʱ�䵽 -> ����ر�
	//                                                               -> �����������
	
	switch(param)
	{
		case 0:
			DeviceControl_SendMsg_Stop(ID_DEV_FEEDER);
			DeviceControl_SendMsg_Stop(ID_DEV_FIRE);
			param++;
		case 1:
			DeviceControl_SendMsg_Set(ID_DEV_LEADFAN, HCS_Struct.pParams->Zhengchanggufeng);
			DeviceControl_SendMsg_Set(ID_DEV_BLOWER, HCS_Struct.pParams->Zhengchangyinfeng);
			flag = 0;
			param++;
			break;
		case 2:
			if((!(flag & 0x1)) && ((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Gufenghouchui * 1000))
			{
				DeviceControl_SendMsg_Stop(ID_DEV_BLOWER);
				flag |= 0x1;
			}
			if((!(flag & 0x2)) && ((xTaskGetTickCount() - Start_Tick) > HCS_Struct.pParams->Yinfenghouchui * 1000))
			{
				DeviceControl_SendMsg_Stop(ID_DEV_LEADFAN);
				flag |= 0x2;
			}
			if((flag & 0x3) == 0x3)
			{
				param++;
			}
			break;
		case 3:
			HCS_Struct.Status = HCS_STATUS_STANDBY;
			return 0;
	}
	return param;

//	//�ȴ�����
//	while(1)
//	{
//		if(HCS_Struct.Status != HCS_STATUS_POWEROFF)
//		{
//			break;
//		}
//		//��������
//		//��ʱ����
//		CslRTC_GetTime(&HCS_Time);
//		if(HCS_Struct.pParams->Dinshikaiji >= 0)
//		{
//			if(HCS_Time.Hou == HCS_Struct.pParams->Dinshikaiji / 60)
//			{
//				if(HCS_Time.Min == HCS_Struct.pParams->Dinshikaiji % 60)
//				{
//					HCS_Struct.Status = HCS_STATUS_STANDBY;
//					CsLCD_DisplayControl(0);
//					CslLCD_BLK(1);
//				}
//			}
//		}
//		vTaskDelay(100);
//	}
//	
//	return 0;
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

