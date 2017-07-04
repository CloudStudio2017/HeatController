#include "FlashControl.h"
#include "semphr.h"
#include "w25q128.h"

static xSemaphoreHandle xh_Flash; 
static uint8_t IsInit = 0;

uint32_t FlashControl_Init(void)
{
	if(IsInit)
	{
		return 1;
	}
	
	xh_Flash = xSemaphoreCreateMutex();
	if(xh_Flash == NULL)
	{
		return -1;
	}
	
	xSemaphoreTake(xh_Flash, portMAX_DELAY);
	flash_Init();
	xSemaphoreGive(xh_Flash);
	
	IsInit = 1;
	return 0;
}

uint32_t FlashControl_ReadID(void)
{
	uint32_t tmp_id;
	
	xSemaphoreTake(xh_Flash, portMAX_DELAY);
	tmp_id = flash_ReadID();
	xSemaphoreGive(xh_Flash);
	
	return tmp_id;
}

void FlashControl_Read(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
	xSemaphoreTake(xh_Flash, portMAX_DELAY);
	flash_ReadBuffer(pBuffer, ReadAddr, NumByteToRead);
	xSemaphoreGive(xh_Flash);
}

void FlashControl_Write(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
	xSemaphoreTake(xh_Flash, portMAX_DELAY);
	flash_WriteBuffer(pBuffer, WriteAddr, NumByteToWrite);
	xSemaphoreGive(xh_Flash);
}

void FlashControl_Erase(uint32_t EraseAddr, uint32_t NumByteToErase)
{
	xSemaphoreTake(xh_Flash, portMAX_DELAY);
	flash_Erase(EraseAddr, NumByteToErase);
	xSemaphoreGive(xh_Flash);
}
