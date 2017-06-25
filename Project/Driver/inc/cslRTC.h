#ifndef __CSL_IOCTRL_H__
#define __CSL_IOCTRL_H__

#include "stm32f10x.h"
#include "cslCommon.h"

typedef struct CslRTC_Date
{
	uint16_t Year;
	uint8_t  Month;
	uint8_t  Day;
}CslRTC_Date;

typedef struct CslRTC_Time
{
	uint8_t Hou;
	uint8_t Min;
	uint8_t Sec;
}CslRTC_Time;

typedef struct CslRTC_Struct
{
	CslRTC_Date Date;
	CslRTC_Time Time;
}CslRTC_Struct;


extern void CslRTC_GetTime(CslRTC_Time* pTime);
extern void CslRTC_Init(void);


#endif

