#ifndef __SYS_PARAMS_H__
#define __SYS_PARAMS_H__


typedef struct
{
	signed short Yuliaoshijian;
	signed short Dianhuoshijian;
	signed short Jinliaoshijian;
	signed short Tingliaoshijian;
	signed short Baohuosongliao;
	signed short Baohuotingliao;
	signed short Kaijiwendu;
	signed short Baohuowendu;
	signed short Gufenghouchui;
	signed short Yinfenghouchui;
	signed short Dinshikaiji;
	signed short Dinshiguanji;
	
	signed short Gufengqianchui;
	signed short Yinfengqianchui;
	signed short Dianhuoyuzhi;
	signed short Yinfengzhihou;
	signed short Gufengzhihou;
	signed short Songliaozhihou;
	signed short Dianhuoyinfeng;
	signed short Dianhuogufeng;
	signed short Zhengchangyinfeng;
	signed short Zhengchanggufeng;
	signed short Baohuoyinfeng;
	signed short Baohuogufeng;
}SysParam_TypeDef;

extern SysParam_TypeDef SysParam;

extern void SysParam_LoadFromFlash(void);
extern void SysParam_SaveToFlash(void);
extern void SysParam_ValueLimitTime16(signed short *pValue);
extern void SysParam_ValueLimitTime8(signed char *pValue);
extern void SysParam_ValueLimitTemp16(signed short *pValue);

#endif
