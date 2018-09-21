#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "myBeep.h"
#include "Task_Beep.h"

static QueueHandle_t msg_handle;

typedef struct beep_msg_t
{
	unsigned int count : 8;
	unsigned int sec_h : 12;
	unsigned int sec_l : 12;
}beep_msg_t;

static beep_msg_t beep_msg;

void Task_Beep_Process(void* p)
{
	int i;
	while(1)
	{
		if(xQueueReceive(msg_handle, &beep_msg, portMAX_DELAY) == pdPASS)
		{
			while(beep_msg.count)
			{
				MyBeep_Beep(1);
				vTaskDelay(beep_msg.sec_h);
				MyBeep_Beep(0);
				beep_msg.count--;
				if(!beep_msg.count)
					break;
				vTaskDelay(beep_msg.sec_l);
			}
		}
	}
}

void Task_Beep_Init(void)
{
	MyBeep_Init();
	msg_handle = xQueueCreate(2, sizeof(beep_msg_t));
	xTaskCreate(Task_Beep_Process, "Task_Beep", 30, NULL, 1,NULL);
}

void Task_Beep(int count, int sec_h, int sec_l)
{
	beep_msg_t msg;
	
	msg.count = count;
	msg.sec_h = sec_h;
	msg.sec_l = sec_l;
	xQueueSend(msg_handle, &msg, portMAX_DELAY);
}
