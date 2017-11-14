#ifndef __SCR_CONTROL_H__
#define __SCR_CONTROL_H__

#include "CslCommon.h"

#define SCRControl_Samp_GPIO         GPIOC
#define SCRControl_Samp_PIN          GPIO_Pin_9
#define SCRControl_Samp_PortSource   GPIO_PortSourceGPIOC
#define SCRControl_Scamp_PinSource   GPIO_PinSource9

#define SCRControl_CH0_GPIO          GPIOD
#define SCRControl_CH0_PIN           GPIO_Pin_12
#define SCRControl_CH1_GPIO          GPIOD
#define SCRControl_CH1_PIN           GPIO_Pin_13


#define SCRControl_DUTY_MAX          100
#define SCRControl_DUTY_MIN          10
#define SCRControl_DUTY_OVERFLOW     90


extern void SCRControl_SetDuty(uint8_t NewDuty, uint8_t Channel);
extern void SCRControl_Init(void);

#endif
