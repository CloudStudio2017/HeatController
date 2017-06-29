#include "myLed.h"

#define MYLED_SUPPORT_MAX  16
static MyLed_RegType myLed_LedList[MYLED_SUPPORT_MAX]={
	{LED0_GPIO, LED0_PIN, LED0_ACTIVE_LEVEL},
	{LED1_GPIO, LED1_PIN, LED1_ACTIVE_LEVEL},
	{LED2_GPIO, LED2_PIN, LED2_ACTIVE_LEVEL},
	{LED3_GPIO, LED3_PIN, LED3_ACTIVE_LEVEL},
	{LED4_GPIO, LED4_PIN, LED4_ACTIVE_LEVEL},
	{LED5_GPIO, LED5_PIN, LED5_ACTIVE_LEVEL},
	{LED6_GPIO, LED6_PIN, LED6_ACTIVE_LEVEL},
	{LED7_GPIO, LED7_PIN, LED7_ACTIVE_LEVEL}};

void myLed_Init(void)
{
	uint8_t i;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	for(i=0;i<8;i++)
	{
		RCC_APB2PeriphClockCmd(GPIO2RCC(myLed_LedList[i].LedGPIO), ENABLE);
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin = myLed_LedList[i].LedPin;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(myLed_LedList[i].LedGPIO, &GPIO_InitStructure);
	}
}

void myLed_On(uint8_t LedIndex)
{
	if(LedIndex > MYLED_SUPPORT_MAX)
		return;
	
	if(myLed_LedList[LedIndex].LedGPIO)
	{
		if(myLed_LedList[LedIndex].ActiveLevel)
		{
			GPIO_SetBits(myLed_LedList[LedIndex].LedGPIO, myLed_LedList[LedIndex].LedPin);
		}
		else
		{
			GPIO_ResetBits(myLed_LedList[LedIndex].LedGPIO, myLed_LedList[LedIndex].LedPin);
		}
	}
}

void myLed_Off(uint8_t LedIndex)
{
	if(LedIndex > MYLED_SUPPORT_MAX)
		return;
	
	if(myLed_LedList[LedIndex].LedGPIO)
	{
		if(!myLed_LedList[LedIndex].ActiveLevel)
		{
			GPIO_SetBits(myLed_LedList[LedIndex].LedGPIO, myLed_LedList[LedIndex].LedPin);
		}
		else
		{
			GPIO_ResetBits(myLed_LedList[LedIndex].LedGPIO, myLed_LedList[LedIndex].LedPin);
		}
	}
}


