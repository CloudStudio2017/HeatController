#ifndef __TASK_COMMON_H__
#define __TASK_COMMON_H__

#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"

enum SysInit_Flag
{
	CONSOLE_INIT_DONE = 0,
	CONTROL_INIT_DONE,
	KEYBOARD_INIT_DONE,
	INIT_TOTAL_COUNT,
};

typedef enum
{
	FLASH_CCMD_INIT = 0,
	FLASH_CCMD_READID,
	FLASH_CCMD_WRITE,
	FLASH_CCMD_READ,
	FLASH_CCMD_ERASE_SECTOR,
}FLASH_CCMD_Type;

typedef struct Common_FlashControlBlock
{
	FLASH_CCMD_Type FlashCmd;
	uint8_t CmdStatus;
	uint32_t Param[3];
}Common_FlashControlBlock;


extern xQueueHandle InitQueue;
extern xQueueHandle FlashQueue;
extern xQueueHandle KeyBoardQueue;

#endif
