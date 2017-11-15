#ifndef __SCR_CONTROL_H__
#define __SCR_CONTROL_H__

#include "CslCommon.h"
#include "board.h"

#define SCRControl_Samp_GPIO         _SAMP_HZ_IN_GPIO
#define SCRControl_Samp_PIN          _SAMP_HZ_IN_PIN
#define SCRControl_Samp_PortSource   GPIO_PortSourceGPIOC
#define SCRControl_Scamp_PinSource   GPIO_PinSource9

#define SCRControl_CH0_GPIO          _OUT_WP1_GPIO
#define SCRControl_CH0_PIN           _OUT_WP1_PIN
#define SCRControl_CH1_GPIO          _OUT_WP2_GPIO
#define SCRControl_CH1_PIN           _OUT_WP2_PIN


#define SCRControl_DUTY_MAX          100
#define SCRControl_DUTY_MIN          10
#define SCRControl_DUTY_OVERFLOW     90


extern void SCRControl_SetDuty(uint8_t NewDuty, uint8_t Channel);
extern void SCRControl_Init(void);

#endif
