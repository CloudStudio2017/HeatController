#ifndef __TASK_MONITOR_H__
#define __TASK_MONITOR_H__

#include "FreeRTOS.h"
#include "Task_Common.h"


extern void vTask_Monitor( void *pvParameters );
extern void vTask_Monitor_Init(void);

#endif
