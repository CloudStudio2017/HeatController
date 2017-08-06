#ifndef __HEAT_CONTROL_SYS_H__
#define __HEAT_CONTROL_SYS_H__

#include "stm32f10x.h"

#define HCS_IO_INPUT   volatile uint8_t
#define HCS_IO_OUTPUT  volatile uint8_t
#define HCS_VA_INPUT   volatile uint32_t
#define HCS_VA_OUTPUT  volatile uint32_t
	
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

typedef struct// HCS_TypeDef
{
	HCS_IO_INPUT WaterLow;
	HCS_IO_INPUT MaterialLow;
	HCS_IO_INPUT WaterHot;
	HCS_VA_INPUT WaterTemp;
	HCS_VA_INPUT StoveTemp;
	
	HCS_IO_OUTPUT WaterPump;
	HCS_IO_OUTPUT MaterialMachine;
	HCS_IO_OUTPUT FireUp;
	HCS_IO_OUTPUT AirBlower;
	HCS_IO_OUTPUT LeadFan;
	
	HCS_STATUS_enum Status;
	
	uint16_t TempBeforeFire;
	
	uint16_t Params[HCS_PARAM_MAX];
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

