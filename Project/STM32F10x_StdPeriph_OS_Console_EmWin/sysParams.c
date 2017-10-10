#include "sysParams.h"


SysParam_TypeDef SysParam;


void SysParam_LoadFromFlash(void)
{
	SysParam.Yuliaoshijian = 100;
	SysParam.Dianhuoshijian = 100;
	SysParam.Jinliaoshijian = 100;
	SysParam.Tingliaoshijian = 100;
	SysParam.Baohuosongliao = 100;
	SysParam.Baohuotingliao = 100;
	SysParam.Kaijiwendu = 100;
	SysParam.Baohuowendu = 400;
	SysParam.Gufenghouchui = 100;
	SysParam.Dinshikaiji = 100;
	SysParam.Dinshiguanji = 100;
	
	SysParam.Gufengqianchui = 100;
	SysParam.Yinfengqianchui = 100;
	SysParam.Dianhuoyuzhi = 100;
	SysParam.Yinfengzhihou = 100;
	SysParam.Gufengzhihou = 100;
	SysParam.Songliaozhihou = 100;
	SysParam.Dianhuoyinfeng = 100;
	SysParam.Dianhuogufeng = 100;
	SysParam.Zhengchangyinfeng = 100;
	SysParam.Zhengchanggufeng = 100;
	SysParam.Baohuoyinfeng = 100;
	SysParam.Baohuogufeng = 100;
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


