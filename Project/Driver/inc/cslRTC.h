#ifndef __CSL_IOCTRL_H__
#define __CSL_IOCTRL_H__

#include "stm32f10x.h"
#include "cslCommon.h"

typedef struct CslRTC_Date
{
	uint16_t Year;
	uint8_t  Month;
	uint8_t  Date;
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
extern void CslRTC_GetDate(CslRTC_Date* pDate);
extern void CslRTC_SetTime(CslRTC_Time* pTime);
extern void CslRTC_SetDate(CslRTC_Date* pDate);
extern void CslRTC_Init(void);


extern void CslRTC_Sec2Date(uint32_t sec, CslRTC_Date* pDate);
extern void CslRTC_Date2Sec(CslRTC_Date* pDate, uint32_t* psec);
extern void CslRTC_Sec2Time(uint32_t sec, CslRTC_Time *pTime);
extern void CslRTC_Time2Sec(CslRTC_Time *pTime, uint32_t* psec);


#endif

