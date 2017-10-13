#ifndef __PT100_H__
#define __PT100_H__

#include "stm32f10x.h"
#include "cslADC.h"

extern float PT100_R2T(float PT100_ResValue);
extern uint8_t PT100_Init(void);
extern float PT100_GetTempValue(void);

#endif
