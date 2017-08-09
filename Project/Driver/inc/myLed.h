#ifndef __MYLED_H__
#define __MYLED_H__

#include "stm32f10x.h"
#include "cslCommon.h"
#include "board.h"

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
//#define LED6 6
//#define LED7 7

#define LED0_GPIO _OUT_L1_GPIO
#define LED1_GPIO _OUT_L2_GPIO
#define LED2_GPIO _OUT_L3_GPIO
#define LED3_GPIO _OUT_L4_GPIO
#define LED4_GPIO _OUT_RWP_GPIO
#define LED5_GPIO _OUT_LWP_GPIO
//#define LED6_GPIO GPIOB
//#define LED7_GPIO GPIOB

#define LED0_PIN _OUT_L1_PIN
#define LED1_PIN _OUT_L2_PIN
#define LED2_PIN _OUT_L3_PIN
#define LED3_PIN _OUT_L4_PIN
#define LED4_PIN _OUT_RWP_PIN
#define LED5_PIN _OUT_LWP_PIN
//#define LED6_PIN GPIO_Pin_8
//#define LED7_PIN GPIO_Pin_9

#define LED0_ACTIVE_LEVEL 0
#define LED1_ACTIVE_LEVEL 0
#define LED2_ACTIVE_LEVEL 0
#define LED3_ACTIVE_LEVEL 0
#define LED4_ACTIVE_LEVEL 0
#define LED5_ACTIVE_LEVEL 0
//#define LED6_ACTIVE_LEVEL 0
//#define LED7_ACTIVE_LEVEL 0

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
