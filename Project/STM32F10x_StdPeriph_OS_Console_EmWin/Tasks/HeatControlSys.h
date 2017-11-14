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
#elif BOARD_TYPE == RELEASE_BOARD_V2
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

/*  开启/关闭 水泵  */
#define _WaterPump_On_()   do{ \
		_WaterPumpOn_;             \
		HCS_Struct.WaterPump = 1;  \
	}while(0)
#define _WaterPump_Off_()  do{ \
		_WaterPumpOff_;            \
		HCS_Struct.WaterPump = 0;  \
}while(0)
/*  开启/关闭 物料机  */
#define _MaterialMachine_On_()     do{ \
		_MaterialMachineOn_;               \
		HCS_Struct.MaterialMachine = 1;    \
	}while(0)
#define _MaterialMachine_Off_()    do{ \
		_MaterialMachineOff_;              \
		HCS_Struct.MaterialMachine = 0;    \
}while(0)
/*  开启/关闭 点火器  */
#define _FireUp_On_()       do{ \
		_FireUpOn_;                 \
		HCS_Struct.FireUp = 1;      \
	}while(0)
#define _FireUp_Off_()      do{ \
		_FireUpOff_;                \
		HCS_Struct.FireUp = 0;      \
}while(0)
/*  开启/关闭 吹风机  */
#define _AirBlower_On_()    do{ \
		_AirBlowerOn_;              \
		HCS_Struct.AirBlower = 1;   \
	}while(0)
#define _AirBlower_Off_()   do{ \
		_AirBlowerOff_;             \
		HCS_Struct.AirBlower = 0;   \
}while(0)
/*  开启/关闭 引风机  */
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
	HCS_STATUS_TEST,
}HCS_STATUS_enum;

typedef enum
{
	HCS_PARAM_GFQC = 0,   //鼓风前吹
	HCS_PARAM_YFQC,       //引风前吹
	HCS_PARAM_YLSJ,       //预料时间
	HCS_PARAM_YRSJ,       //预热时间
	HCS_PARAM_DHSJ,       //点火时间
	HCS_PARAM_JLSJ,       //进料时间
	HCS_PARAM_TLSJ,       //停料时间
	HCS_PARAM_GFHC,       //鼓风后吹
	HCS_PARAM_YFHC,       //引风后吹
	HCS_PARAM_BHSL,       //保火送料
	HCS_PARAM_BHTL,       //保火停料
	HCS_PARAM_KJWD,       //开机温度
	HCS_PARAM_TJWD,       //停机温度
	HCS_PARAM_BHWD,       //保火温度
	HCS_PARAM_KBWD,       //开泵温度
	HCS_PARAM_TBWD,       //停泵温度
	HCS_PARAM_DSKJ,       //定时开机
	HCS_PARAM_DSGJ,       //定时关机
	
	HCS_PARAM_DHYZ,       //点火阈值
	HCS_PARAM_DHJG,       //点火间隔
	HCS_PARAM_YFZH,       //引风滞后
	HCS_PARAM_GFZH,       //鼓风滞后
	HCS_PARAM_DHYF,       //点火引风
	HCS_PARAM_DHGF,       //点火鼓风
	HCS_PARAM_SLZH,       //送料滞后
	HCS_PARAM_BJWD,       //报警温度
	HCS_PARAM_FDWD,       //防冻温度
	HCS_PARAM_ZCYF,       //正常引风
	HCS_PARAM_ZCGF,       //正常鼓风
	HCS_PARAM_BHYF,       //保火引风
	HCS_PARAM_BHGF,       //保火鼓风
	
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
extern uint8_t HCS_SM_Test(uint8_t param);



#endif

