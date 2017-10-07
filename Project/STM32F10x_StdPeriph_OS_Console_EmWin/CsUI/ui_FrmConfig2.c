#include "ui_FrmConfig2.h"


CS_FRAME(FrmConfig2, NULL, 0, 0, 480, 320, CSUI_BLACK, NULL);

void ui_FrmConfig2_Init(void)
{
}

void ui_FrmConfig2_ShowFrame(void)
{
	//Config1 frame redraw
	FrmConfig2.Obj.Draw(&FrmConfig2);
}

void ui_FrmConfig2_Process(void)
{
	
	while(1)
	{
		if(UI_Index != 2)
		{
			return;
		}
	}
}

