#ifndef __HEAT_CONTROL_SYS_H__
#define __HEAT_CONTROL_SYS_H__

#include "stm32f10x.h"
#include "board.h"
#include "cslIOCtrl.h"
#include "sysParams.h"

#define HCS_IO_INPUT   volatile uint8_t
#define HCS_IO_OUTPUT  volatile uint8_t
#define HCS_VA_INPUT   volatile uint32_t
#define HCS_VA_OUTPUT  volatile uint32_t
	

#if BOARD_TYPE == RELEASE_BOARD_V1
	#define _MaterialMachineOn_       myLed_On(1)
	#define _MaterialMachineOff_      myLed_Off(1)
	#define _FireUpOn_                myLed_On(2)
	#define _FireUpOff_               myLed_Off(2)
	#define _AirBlowerOn_             myLed_On(4)
	#define _AirBlowerOff_            myLed_On(4)
	#define _LeadFanOn_               myLed_On(5)
	#define _LeadFanOff_              myLed_On(5)
#elif BOARD_TYPE == TEST_BOARD_V1
	#define _MaterialMachineOn_       CslIOCtrl_SetLevelOut(&IO_Liaoji, 1)
	#define _MaterialMachineOff_      CslIOCtrl_SetLevelOut(&IO_Liaoji, 0)
	#define _FireUpOn_                CslIOCtrl_SetLevelOut(&IO_Dianhuo, 1)
	#define _FireUpOff_               CslIOCtrl_SetLevelOut(&IO_Dianhuo, 0)
	#define _AirBlowerOn_             CslIOCtrl_SetSCROut(&IO_Gufeng, 100)
	#define _AirBlowerOff_            CslIOCtrl_SetSCROut(&IO_Gufeng, 0)
	#define _AirBlowerSet_(Duty)      CslIOCtrl_SetSCROut(&IO_Gufeng, Duty)
	#define _LeadFanOn_               CslIOCtrl_SetSCROut(&IO_Yinfeng, 100)
	#define _LeadFanOff_              CslIOCtrl_SetSCROut(&IO_Yinfeng, 0)
	#define _LeadFanSet_(Duty)        CslIOCtrl_SetSCROut(&IO_Yinfeng, Duty)
#endif

/*  ����/�ر� ˮ��  */
#define _WaterPump_On_()   do{ \
		_WaterPumpOn_;             \
		HCS_Struct.WaterPump = 1;  \
	}while(0)
#define _WaterPump_Off_()  do{ \
		_WaterPumpOff_;            \
		HCS_Struct.WaterPump = 0;  \
}while(0)
/*  ����/�ر� ���ϻ�  */
#define _MaterialMachine_On_()     do{ \
		_MaterialMachineOn_;               \
		HCS_Struct.MaterialMachine = 1;    \
	}while(0)
#define _MaterialMachine_Off_()    do{ \
		_MaterialMachineOff_;              \
		HCS_Struct.MaterialMachine = 0;    \
}while(0)
/*  ����/�ر� �����  */
#define _FireUp_On_()       do{ \
		_FireUpOn_;                 \
		HCS_Struct.FireUp = 1;      \
	}while(0)
#define _FireUp_Off_()      do{ \
		_FireUpOff_;                \
		HCS_Struct.FireUp = 0;      \
}while(0)
/*  ����/�ر� �����  */
#define _AirBlower_On_()    do{ \
		_AirBlowerOn_;              \
		HCS_Struct.AirBlower = 1;   \
	}while(0)
#define _AirBlower_Off_()   do{ \
		_AirBlowerOff_;             \
		HCS_Struct.AirBlower = 0;   \
}while(0)
/*  ����/�ر� �����  */
#define _LeadFan_On_()      do{ \
		_LeadFanOn_;                \
		HCS_Struct.LeadFan = 1;     \
	}while(0)
#define _LeadFan_Off_()     do{ \
		_LeadFanOff_;               \
		HCS_Struct.LeadFan = 0;     \
}while(0)

	
typedef enum
{
	HCS_STATUS_STANDBY = 0,
	HCS_STATUS_STARTUP,
	HCS_STATUS_PREBLOW,
	HCS_STATUS_PREMATERIAL,
	HCS_STATUS_WARMEDUP,
	HCS_STATUS_FIREUP,
	HCS_STATUS_RUNNING,
	HCS_STATUS_FIREPROTECT,
	HCS_STATUS_POWEROFF,
}HCS_STATUS_enum;

typedef enum
{
	HCS_PARAM_GFQC = 0,   //�ķ�ǰ��
	HCS_PARAM_YFQC,       //����ǰ��
	HCS_PARAM_YLSJ,       //Ԥ��ʱ��
	HCS_PARAM_YRSJ,       //Ԥ��ʱ��
	HCS_PARAM_DHSJ,       //���ʱ��
	HCS_PARAM_JLSJ,       //����ʱ��
	HCS_PARAM_TLSJ,       //ͣ��ʱ��
	HCS_PARAM_GFHC,       //�ķ��
	HCS_PARAM_YFHC,       //�����
	HCS_PARAM_BHSL,       //��������
	HCS_PARAM_BHTL,       //����ͣ��
	HCS_PARAM_KJWD,       //�����¶�
	HCS_PARAM_TJWD,       //ͣ���¶�
	HCS_PARAM_BHWD,       //�����¶�
	HCS_PARAM_KBWD,       //�����¶�
	HCS_PARAM_TBWD,       //ͣ���¶�
	HCS_PARAM_DSKJ,       //��ʱ����
	HCS_PARAM_DSGJ,       //��ʱ�ػ�
	
	HCS_PARAM_DHYZ,       //�����ֵ
	HCS_PARAM_DHJG,       //�����
	HCS_PARAM_YFZH,       //�����ͺ�
	HCS_PARAM_GFZH,       //�ķ��ͺ�
	HCS_PARAM_DHYF,       //�������
	HCS_PARAM_DHGF,       //���ķ�
	HCS_PARAM_SLZH,       //�����ͺ�
	HCS_PARAM_BJWD,       //�����¶�
	HCS_PARAM_FDWD,       //�����¶�
	HCS_PARAM_ZCYF,       //��������
	HCS_PARAM_ZCGF,       //�����ķ�
	HCS_PARAM_BHYF,       //��������
	HCS_PARAM_BHGF,       //����ķ�
	
	HCS_PARAM_MAX,
}HCS_PARAM_enum;

typedef struct
{
	float   Value;
	uint8_t Flag;          //0:NoErr 1:TooHigh 2:TooLow 3:SensorOffLine
}HCS_Temperature;

typedef struct// HCS_TypeDef
{
	HCS_IO_INPUT WaterLow;
	HCS_IO_INPUT MaterialLow;
	HCS_IO_INPUT WaterHot;
	HCS_Temperature WaterTemp;
	HCS_Temperature StoveTemp;
	
	HCS_IO_OUTPUT WaterPump;
	HCS_IO_OUTPUT MaterialMachine;
	HCS_IO_OUTPUT FireUp;
	HCS_IO_OUTPUT AirBlower;
	HCS_IO_OUTPUT LeadFan;
	
	HCS_STATUS_enum Status;
	
	uint16_t TempBeforeFire;
	
	SysParam_TypeDef* pParams;
	//uint16_t Params[HCS_PARAM_MAX];
}HCS_TypeDef;

extern volatile HCS_TypeDef HCS_Struct;

extern void HCS_Init(void);

extern uint8_t HCS_SM_Standby(uint8_t param);
extern uint8_t HCS_SM_Startup(uint8_t param);
extern uint8_t HCS_SM_PreBlowing(uint8_t param);
extern uint8_t HCS_SM_WarmedUp(uint8_t param);
extern uint8_t HCS_SM_PreMaterial(uint8_t param);
extern uint8_t HCS_SM_FireUp(uint8_t param);
extern uint8_t HCS_SM_Running(uint8_t param);
extern uint8_t HCS_SM_FireProtection(uint8_t param);
extern uint8_t HCS_SM_Suspend(uint8_t param);
extern uint8_t HCS_SM_PowerOff(uint8_t param);



#endif

