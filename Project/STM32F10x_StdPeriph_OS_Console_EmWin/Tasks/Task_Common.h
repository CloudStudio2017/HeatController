#ifndef __TASK_COMMON_H__
#define __TASK_COMMON_H__

#include "FreeRTOS.h"
#include "queue.h"

enum SysInit_Flag
{
	CONSOLE_INIT_DONE = 1,
	CONTROL_INIT_DONE,
	UI_INIT_DONE,
};


extern xQueueHandle InitQueue;;

#endif
