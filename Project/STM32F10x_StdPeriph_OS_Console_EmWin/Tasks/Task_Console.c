#include "Task_Console.h"
#include "CslConsole.h"

static uint32_t Is_Init=0;

void vTask_Console( void *pvParameters )
{
	CslConsole_Init();
	
	Is_Init = CONSOLE_INIT_DONE;
	xQueueSendToBack(InitQueue, &Is_Init, portMAX_DELAY);
	
	CslConsole_Process();
	while(1)
	{
	}
}
