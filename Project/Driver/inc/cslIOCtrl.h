#ifndef __CSL_IOCTRL_H__
#define __CSL_IOCTRL_H__

#include "stm32f10x.h"
#include "cslCommon.h"
#include "SCRControl.h"

typedef enum
{
	IOMode_NULL = 0,
	IOMode_Level_Out = 1,
	IOMode_Level_In,
	IOMode_PWM_Out,
	IOMode_PWM_In,
	IOMode_Analog_Out,
	IOMode_Analog_In,
	IOMode_SCR_Out,
}CSLIOCtrl_IOEnum;

typedef struct
{
	uint8_t ActiveLevel;
	uint8_t Res;
}CslIOCtrl_Device_Level_TypeDef;

typedef struct
{
	uint32_t Freq;
	uint32_t Duty;
	TIM_TypeDef* pTIM;
	uint16_t TIM_Channel;
}CslIOCtrl_Device_PWM_TypeDef;

typedef struct
{
	ADC_TypeDef* pADC;
	uint16_t ADC_Channel;
}CslIOCtrl_Device_Analog_TypeDef;

typedef struct
{
	uint8_t Channel;
}CslIOCtrl_Device_SCR_TypeDef;

typedef union
{
	CslIOCtrl_Device_Level_TypeDef*   AsLevel;
	CslIOCtrl_Device_PWM_TypeDef*     AsPWM;
	CslIOCtrl_Device_Analog_TypeDef*  AsAnalog;
	CslIOCtrl_Device_SCR_TypeDef*     AsSCR;
}CslIOCtrl_Device_TypeDef;

typedef struct
{
	GPIO_TypeDef* GPIO;
	uint32_t Pin;
	CSLIOCtrl_IOEnum IOMode;
	CslIOCtrl_Device_TypeDef Device;
}CslIOCtrl_RegTypeDef;

extern uint8_t CslIOCtrl_Reg(CslIOCtrl_RegTypeDef* pIO);
extern uint8_t CslIOCtrl_SetLevelOut(CslIOCtrl_RegTypeDef* pIO, uint8_t NewMode);


#endif

