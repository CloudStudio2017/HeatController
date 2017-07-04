#ifndef __W25Q128_H__
#define __W25Q128_H__

#include "stm32f10x.h"

extern void flash_DeInit(void);
extern void flash_Init(void);
extern uint32_t flash_ReadID(void);
extern void flash_EraseSector(uint32_t SectorAddr);
extern void flash_EraseBulk(void);
extern void flash_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
extern void flash_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
extern void flash_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
extern void flash_Erase(uint32_t EraseAddr, uint32_t NumByteToErase);

#define flash_EraseChip  flash_EraseBulk

#endif
