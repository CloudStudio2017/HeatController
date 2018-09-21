#ifndef __TASK_DEVICECONTROL_H__
#define __TASK_DEVICECONTROL_H__

#include "stdint.h"

#define DC_MSG_TYPE_INIT        0x00
#define DC_MSG_TYPE_RUN         0x01
#define DC_MSG_TYPE_SET         0x02
#define DC_MSG_TYPE_SUSPEND     0x03
#define DC_MSG_TYPE_STOP        0x04


typedef struct DCMsg_t
{
	unsigned char Type;           //Msg type
	unsigned char ID;             //ID of PCB
	unsigned short Value;
}DCMsg_t;


//#define DCB_STATUS_ON        0x01
//#define DCB_STATUS_OFF       0x02

typedef void(*ControlAdj_cb)(int);

typedef struct
{
	unsigned char type;
	unsigned short value;
	ControlAdj_cb ControlAdj;
	void(*Init)(void);
}Device_t;

typedef struct
{
//	unsigned char Status;         //Device Control Block status
	Device_t* Device;             //ptr of device control device
}DCB_t;

typedef struct
{
	int Count;
	DCB_t* Item;
}DCB_TABLE_t;

int DeviceControl_Init(DCB_t* dcb_entry, int count);
void DeviceControl_Process(void *pvParameters);
int DeviceControl_SendMsg(uint8_t Type, uint8_t ID, uint16_t Value);

#define DeviceControl_SendMsg_Run(ID)              DeviceControl_SendMsg(DC_MSG_TYPE_RUN, ID, 1)
#define DeviceControl_SendMsg_Set(ID, Value)       DeviceControl_SendMsg(DC_MSG_TYPE_SET, ID, Value)
#define DeviceControl_SendMsg_Stop(ID)             DeviceControl_SendMsg(DC_MSG_TYPE_STOP, ID, 0)
#define DeviceControl_SendMsg_Init(ID)             DeviceControl_SendMsg(DC_MSG_TYPE_INIT, ID, 0)


#endif
