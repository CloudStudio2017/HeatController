#include "sysParams.h"
#include "FlashControl.h"

SysParam_TypeDef SysParam;


void SysParam_LoadFromFlash(void)
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

void SysParam_SaveToFlash(void)
{
}

void SysParam_ValueLimitTime16(signed short *pValue)
{
	if(*pValue > 3600-1)
		*pValue = 0;
	if(*pValue < 0)
		*pValue = 3600-1;
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


