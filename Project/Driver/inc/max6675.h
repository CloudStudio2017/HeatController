#ifndef __MAX6675_H__
#define __MAX6675_H__

#include "cslCommon.h"
#include "stm32f10x.h"
#include "board.h"


#define MAX6675_SCK_GPIO   _MAX6675_SCK_GPIO
#define MAX6675_SCK_PIN    _MAX6675_SCK_PIN

#define MAX6675_CS_GPIO    _MAX6675_CS_GPIO
#define MAX6675_CS_PIN     _MAX6675_CS_PIN

#define MAX6675_SO_GPIO    _MAX6675_SO_GPIO
#define MAX6675_SO_PIN     _MAX6675_SO_PIN

#define MAX6675_SCK_1      GPIO_SetBits(MAX6675_SCK_GPIO, MAX6675_SCK_PIN)
#define MAX6675_SCK_0      GPIO_ResetBits(MAX6675_SCK_GPIO, MAX6675_SCK_PIN)

#define MAX6675_CS_1       GPIO_SetBits(MAX6675_CS_GPIO, MAX6675_CS_PIN)
#define MAX6675_CS_0       GPIO_ResetBits(MAX6675_CS_GPIO, MAX6675_CS_PIN)

#define MAX6675_SO         GPIO_ReadInputDataBit(MAX6675_SO_GPIO, MAX6675_SO_PIN)

typedef struct
{
	unsigned short State         : 1;
	unsigned short DeviceID      : 1;
	unsigned short SensorOffline : 1;
	unsigned short Data          : 12;
	unsigned short DUMMY         : 1;
}MAX6675_LineDataType;

#define  MAX6675_NOERR         0
#define  MAX6675_ERR_SENSOR    1
#define  MAX6675_ERR_DEVICE    2

unsigned char MAX6675_GetTemp(unsigned short* pData);
unsigned char MAX6675_Init(void);

#endif
