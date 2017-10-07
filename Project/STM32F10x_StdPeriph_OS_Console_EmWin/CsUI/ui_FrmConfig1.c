#include "ui_FrmConfig1.h"


CS_FRAME(FrmConfig1, NULL, 0, 0, 480, 320, CSUI_RED, NULL);


void ui_FrmConfig1_Init(void)
{
	
}

void ui_FrmConfig1_ShowFrame(void)
{
	//Config1 frame redraw
	FrmConfig1.Obj.Draw(&FrmConfig1);
}

void ui_FrmConfig1_Process(void)
{
	
	while(1)
	{
		if(UI_Index != 1)
		{
			return;
		}
	}
}

