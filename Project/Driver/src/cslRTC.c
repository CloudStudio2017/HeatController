#include "CslRTC.h"

static const uint8_t _mDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
static const uint8_t _sDays[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

#define IsLeapYear(YYYY)   (((YYYY) % 4 == 0) && ((YYYY) % 100 != 0) || ((YYYY) % 400 == 0))

void CslRTC_Sec2Date(uint32_t sec, CslRTC_Date* pDate)
{
	uint16_t YY = 2000;
	uint8_t MM = 1;
	uint32_t tmpDate;
	const uint8_t* pDayMap;
	
	tmpDate = sec / (24 * 3600);
	while(tmpDate > 365)
	{
		if(IsLeapYear(YY))
		{
			tmpDate -= 366;
		}
		else
		{
			tmpDate -= 365;
		}
		YY++;
	}
	pDate->Year = YY;
	if(IsLeapYear(YY))
	{
		pDayMap = _sDays;
	}
	else
	{
		pDayMap = _mDays;
	}
	while(tmpDate >= pDayMap[MM - 1])
	{
		tmpDate -= pDayMap[MM - 1];
		MM++;
	}
	pDate->Month = MM;
	pDate->Date = tmpDate + 1;
}

void CslRTC_Date2Sec(CslRTC_Date* pDate, uint32_t* psec)
{
	uint16_t YY;
	uint8_t MM, DD;
	uint32_t tmpDate = 0;
	const uint8_t* pDayMap;
	
	YY = pDate->Year;
	MM = pDate->Month;
	DD = pDate->Date;
	
	if(IsLeapYear(YY))
	{
		pDayMap = _sDays;
	}
	else
	{
		pDayMap = _mDays;
	}
	while(YY > 2000)
	{
		if(IsLeapYear(YY-1))
		{
			tmpDate += 366;
		}
		else
		{
			tmpDate += 365;
		}
		YY--;
	}
	while(MM > 1)
	{
		MM--;
		tmpDate += pDayMap[MM-1];
	}
	tmpDate += DD - 1;
	
	*psec = tmpDate * 24 * 3600;
}

void CslRTC_Sec2Time(uint32_t sec, CslRTC_Time *pTime)
{
	pTime->Hou = sec / 3600 % 24;
	pTime->Min = sec / 60 % 60;
	pTime->Sec = sec % 60;
}

void CslRTC_Time2Sec(CslRTC_Time *pTime, uint32_t* psec)
{
	*psec = pTime->Hou * 3600 + pTime->Min * 60 + pTime->Sec;
}

void CslRTC_GetTime(CslRTC_Time* pTime)
{
	uint32_t tmpCounter;
	
	tmpCounter = RTC_GetCounter();
	CslRTC_Sec2Time(tmpCounter, pTime);
}

void CslRTC_GetDate(CslRTC_Date* pDate)
{
	uint32_t tmpCounter;
	
	tmpCounter = RTC_GetCounter();
	CslRTC_Sec2Date(tmpCounter, pDate);
}

void CslRTC_SetTime(CslRTC_Time* pTime)
{
	uint32_t tmpCounter;
	uint32_t tmpSec;
	
	tmpCounter = RTC_GetCounter() / (24 * 3600);
	CslRTC_Time2Sec(pTime, &tmpSec);
	tmpCounter = tmpCounter * (24 * 3600) + tmpSec;
	RTC_SetCounter(tmpCounter);
	RTC_WaitForLastTask();
}

void CslRTC_SetDate(CslRTC_Date* pDate)
{
	uint32_t tmpCounter;
	uint32_t tmpSec;
	
	tmpCounter = RTC_GetCounter() % (24 * 3600);
	CslRTC_Date2Sec(pDate, &tmpSec);
	tmpCounter = tmpCounter + tmpSec;
	RTC_SetCounter(tmpCounter);
	RTC_WaitForLastTask();
}

#define CSL_RTC_BKP_REG         BKP_DR1
#define CSL_RTC_BKP_REG_VALUE   0x2234
uint8_t CslRTC_CheckBackupReg(void)
{
	if(BKP_ReadBackupRegister(CSL_RTC_BKP_REG) != CSL_RTC_BKP_REG_VALUE)
	{
		return 0xFF;
	}
	
	return 0x00;
}

void inline CslRTC_SetBackupReg(void)
{
	BKP_WriteBackupRegister(CSL_RTC_BKP_REG, CSL_RTC_BKP_REG_VALUE);
}

void CslRTC_Init(void)
{
	CslRTC_Date InitDate;
	CslRTC_Time InitTime;
	//NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the RTC Interrupt */
  //NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  //NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //NVIC_Init(&NVIC_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	
	/* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);
	
	BKP_ClearFlag();
	if(RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
	{
		RCC_ClearFlag();
		
		if(CslRTC_CheckBackupReg() == 0x00)
		{
			return;
		}
	}
	CslRTC_SetBackupReg();
	
  /* Reset Backup Domain */
  //BKP_DeInit();

  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  //RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
	
	InitDate.Year = 2017;
	InitDate.Month = 10;
	InitDate.Date = 25;
	
	InitTime.Hou = 03;
	InitTime.Min = 22;
	InitTime.Sec = 00;
	
	CslRTC_SetDate(&InitDate);
	CslRTC_SetTime(&InitTime);
}

void RTC_1IRQHandler(void)
{
  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
    /* Clear the RTC Second interrupt */
    RTC_ClearITPendingBit(RTC_IT_SEC);
		
    /* Enable time update */
    //TimeDisplay = 1;

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    
  }
}







