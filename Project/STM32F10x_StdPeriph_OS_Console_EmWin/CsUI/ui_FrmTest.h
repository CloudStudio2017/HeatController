#ifndef __UI_FRMTEST_H__
#define __UI_FRMTEST_H__

#include "CsUI.h"
#include "Task_UI.h"
#include "ui_source_bitmap.h"

typedef struct
{
	int8_t DianhuoStatus;
	int8_t LiaojiStatus;
	int8_t GufengStatus;
	int8_t YinfengStatus;
}TestStatusTypeDef;

extern void ui_FrmTest_Init(void);
extern void ui_FrmTest_ShowFrame(void);
extern void ui_FrmTest_Process(void);

#endif
