#ifndef __SYS_PARAMS_H__
#define __SYS_PARAMS_H__

#define SYS_PARAM_BLOCK0_ADDR        (0x0000)
#define SYS_PARAM_BLOCK1_ADDR        (0x1000)

#define SYS_PARAM_BLOCK_SIZE         (sizeof(SysParam_TypeDef))
#define SYS_PARAM_BLOCK0_CHECK_ADDR  (SYS_PARAM_BLOCK0_ADDR + SYS_PARAM_BLOCK_SIZE)
#define SYS_PARAM_BLOCK1_CHECK_ADDR  (SYS_PARAM_BLOCK1_ADDR + SYS_PARAM_BLOCK_SIZE)
#define SYS_PARAM_BLOCK0_FLAG_ADDR   (SYS_PARAM_BLOCK0_ADDR + 0x1000 - 0x4)
#define SYS_PARAM_BLOCK1_FLAG_ADDR   (SYS_PARAM_BLOCK1_ADDR + 0x1000 - 0x4)

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
extern void SysParam_ValueLimit24Hour(signed short *pValue);
extern void SysParam_ValueLimitTime8(signed char *pValue);
extern void SysParam_ValueLimitTemp16(signed short *pValue);

#endif
