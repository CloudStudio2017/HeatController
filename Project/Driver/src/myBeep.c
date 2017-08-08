#include "myBeep.h"
#include "board.h"



void MyBeep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(GPIO2RCC(_BEEP_GPIO), ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = _BEEP_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(_BEEP_GPIO, &GPIO_InitStruct);
}

void MyBeep_Beep(uint8_t Mode)
{
	if(Mode)
	{
		GPIO_SetBits(_BEEP_GPIO, _BEEP_PIN);
	}
	else
	{
		GPIO_ResetBits(_BEEP_GPIO, _BEEP_PIN);
	}
}
