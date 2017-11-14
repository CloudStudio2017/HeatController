#ifndef __TASK_UI_H__
#define __TASK_UI_H__

#include "FreeRTOS.h"
#include "Task_Common.h"
#include "CsUI_Font.h"
//#include "UI_Sources.h"

extern volatile uint8_t UI_Index;   //0:Main   1:Config1  2:Config2  3:Test

extern void vTask_UI( void *pvParameters );


#endif
