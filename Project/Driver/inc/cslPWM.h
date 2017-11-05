#ifndef __CSL_PWM_H__
#define __CSL_PWM_H__

#include "cslCommon.h"

extern uint8_t CslPWMOut_Init(TIM_TypeDef* pTIM, GPIO_TypeDef* pGPIO, uint16_t Pin, uint8_t Channel, uint32_t Freq);
extern uint8_t CslPWMOut_SetDuty(TIM_TypeDef* pTIM, uint8_t Channel, uint8_t Duty);


#endif
