#ifndef __TASK_CONTROL_H__
#define __TASK_CONTROL_H__

#include "FreeRTOS.h"
#include "Task_Common.h"

enum
{
	CMD_CONTROL_POWEROFF = 0,
	CMD_CONTROL_POWERON,
	CMD_CONTROL_START,
	CMD_CONTROL_SUSPEND,
	CMD_CONTROL_STOP,
	CMD_CONTROL_RUN,
	CMD_CONTROL_TEST = 100,
};


void Control_SendMsg(unsigned char cmd);
void vTask_Control( void *pvParameters );


#endif
