#ifndef __MYLED_H__
#define __MYLED_H__

#include "stm32f10x.h"
#include "cslCommon.h"

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 7

#define LED0_GPIO GPIOB
#define LED1_GPIO GPIOB
#define LED2_GPIO GPIOB
#define LED3_GPIO GPIOB
#define LED4_GPIO GPIOC
#define LED5_GPIO GPIOC
#define LED6_GPIO GPIOB
#define LED7_GPIO GPIOB

#define LED0_PIN GPIO_Pin_13
#define LED1_PIN GPIO_Pin_12
#define LED2_PIN GPIO_Pin_14
#define LED3_PIN GPIO_Pin_15
#define LED4_PIN GPIO_Pin_6
#define LED5_PIN GPIO_Pin_7
#define LED6_PIN GPIO_Pin_8
#define LED7_PIN GPIO_Pin_9

#define LED0_ACTIVE_LEVEL 0
#define LED1_ACTIVE_LEVEL 0
#define LED2_ACTIVE_LEVEL 0
#define LED3_ACTIVE_LEVEL 0
#define LED4_ACTIVE_LEVEL 0
#define LED5_ACTIVE_LEVEL 0
#define LED6_ACTIVE_LEVEL 0
#define LED7_ACTIVE_LEVEL 0

typedef struct MyLed_RegType
{
	GPIO_TypeDef* LedGPIO;
	uint16_t      LedPin;
	uint8_t       ActiveLevel;
}MyLed_RegType;

extern void myLed_Init(void);
extern void myLed_On(uint8_t LedIndex);
extern void myLed_Off(uint8_t LedIndex);



#endif
