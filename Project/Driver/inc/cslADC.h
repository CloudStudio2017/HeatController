#ifndef __CSL_ADC_H__
#define __CSL_ADC_H__

#include "cslCommon.h"
#include "stm32f10x.h"

extern uint8_t CslADC_Init(void);
extern uint16_t CslADC_GetADCValue(uint8_t Channel);

#endif
