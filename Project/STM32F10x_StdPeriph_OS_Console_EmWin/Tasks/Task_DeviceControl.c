#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "Task_DeviceControl.h"

static QueueHandle_t msg_handle;
static DCMsg_t msg;

static DCB_TABLE_t dcb_table;


int DeviceControl_Init(DCB_t* dcb_entry, int count)
{
	int i;
	//Create a message queue
	msg_handle = xQueueCreate(4, sizeof(DCMsg_t));
	if(!msg_handle)
		return -1;
	
	//init dcb table
	dcb_table.Count = count;
	dcb_table.Item = dcb_entry;
	for(i=0; i<count; i++)
	{
		if(dcb_table.Item[i].Device->Init)
		{
			dcb_table.Item[i].Device->value = 0;
			dcb_table.Item[i].Device->Init();
		}
		//dcb_table.Item[i].Status = DCB_STATUS_OFF;
	}
	
	xTaskCreate(DeviceControl_Process, "Task_DCP", 256, NULL, tskIDLE_PRIORITY, NULL);
	return 0;
}


void DeviceControl_Process(void *pvParameters)
{
	int tick_now;
	int i;
	
	while(1)
	{
		if(xQueueReceive(msg_handle, &msg, 20) == pdPASS)     //get msg each 20ms
		{
			switch(msg.Type)
			{
				case DC_MSG_TYPE_INIT:           //Procedure Control Block's init
					break;
				case DC_MSG_TYPE_RUN:            //Procedure Control Block's execute
				case DC_MSG_TYPE_SET:
					if(msg.ID >= dcb_table.Count)  //ID must little than count
					{
						//invalid id
						break;
					}
					dcb_table.Item[msg.ID].Device->value = msg.Value;
					dcb_table.Item[msg.ID].Device->ControlAdj(msg.Value);
					break;
				case DC_MSG_TYPE_SUSPEND:        //Procedure Control Block's suspend
					//TODO: not support yet
					break;
				case DC_MSG_TYPE_STOP:           //Procedure Control Block's stop
					if(msg.ID >= dcb_table.Count)
					{
						break;
					}
					dcb_table.Item[msg.ID].Device->value = 0;
					dcb_table.Item[msg.ID].Device->ControlAdj(0);
					break;
			}
		}
		//process
		tick_now = xTaskGetTickCount();
	}
}

int DeviceControl_SendMsg(uint8_t Type, uint8_t ID, uint16_t Value)
{
	DCMsg_t msg;
	
	msg.Type = Type;
	msg.ID = ID;
	msg.Value = Value;
	xQueueSend(msg_handle, &msg, portMAX_DELAY);

	return 0;
}
