#ifndef __FLASHCONTROL_H__
#define __FLASHCONTROL_H__

#include "FreeRTOS.h"

extern uint32_t FlashControl_Init(void);
extern uint32_t FlashControl_ReadID(void);
extern void FlashControl_Read(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
extern void FlashControl_Write(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
extern void FlashControl_Erase(uint32_t EraseAddr, uint32_t NumByteToErase);


#endif
