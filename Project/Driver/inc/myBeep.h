#ifndef __MY_BEEP_H__
#define __MY_BEEP_H__

#include "stm32f10x.h"
#include "cslCommon.h"

extern void MyBeep_Init(void);
extern void MyBeep_Beep(uint8_t Mode);

#endif
