#include "sysParams.h"
#include "FlashControl.h"

SysParam_TypeDef SysParam;


uint8_t SysParam_CheckBlock(uint8_t BlockIndex)
{
	uint32_t tmpCheckData;
	
	FlashControl_Read((uint8_t*)&tmpCheckData, SYS_PARAM_BLOCK0_CHECK_ADDR, 4);
	if(tmpCheckData != 0x5A5A5A5A)
	{
		return -1;
	}
	return 0;
}

void SysParam_MarkBlock(uint8_t BlockIndex)
{
	uint32_t tmpMarkData = 0x5A5A5A5A;
	
	FlashControl_Write((uint8_t*)&tmpMarkData, SYS_PARAM_BLOCK0_CHECK_ADDR, 4);
}

void SysParam_LoadFromFlash(void)
{
	if(SysParam_CheckBlock(0))
	{
		SysParam.Yuliaoshijian      = 2;
		SysParam.Dianhuoshijian     = 3;
		SysParam.Jinliaoshijian     = 2;
		SysParam.Tingliaoshijian    = 2;
		SysParam.Baohuosongliao     = 2;
		SysParam.Baohuotingliao     = 2;
		SysParam.Kaijiwendu         = 80;
		SysParam.Baohuowendu        = 90;
		SysParam.Gufenghouchui      = 2;
		SysParam.Dinshikaiji        = 12*60 + 0;
		SysParam.Dinshiguanji       = 12*60 + 30;
		
		SysParam.Gufengqianchui     = 2;
		SysParam.Yinfengqianchui    = 2;
		SysParam.Dianhuoyuzhi       = 20;
		SysParam.Yinfengzhihou      = 2;
		SysParam.Gufengzhihou       = 2;
		SysParam.Songliaozhihou     = 2;
		SysParam.Dianhuoyinfeng     = 50;
		SysParam.Dianhuogufeng      = 50;
		SysParam.Zhengchangyinfeng  = 50;
		SysParam.Zhengchanggufeng   = 50;
		SysParam.Baohuoyinfeng      = 50;
		SysParam.Baohuogufeng       = 50;
	}
	else
	{
		FlashControl_Read((uint8_t*)&SysParam, SYS_PARAM_BLOCK0_ADDR, sizeof(SysParam));
	}
}

void SysParam_SaveToFlash(void)
{
	FlashControl_Erase(SYS_PARAM_BLOCK0_ADDR, 0x1000);
	FlashControl_Write((uint8_t*)&SysParam, SYS_PARAM_BLOCK0_ADDR, sizeof(SysParam));
	SysParam_MarkBlock(0);
}

void SysParam_ValueLimitTime16(signed short *pValue)
{
	if(*pValue > 3600-1)
		*pValue = 0;
	if(*pValue < 0)
		*pValue = 3600-1;
}

void SysParam_ValueLimit24Hour(signed short *pValue)
{
	if(*pValue > 24*60-1)
		*pValue = 0;
	if(*pValue < 0)
		*pValue = 24*-1;
}

void SysParam_ValueLimitTime8(signed char *pValue)
{
}

void SysParam_ValueLimitTemp16(signed short *pValue)
{
	if(*pValue > 500)
		*pValue = 0;
	if(*pValue < 0)
		*pValue = 500;
}


