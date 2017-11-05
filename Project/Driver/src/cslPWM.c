#include "cslPWM.h"

uint8_t CslPWMOut_SetDuty(TIM_TypeDef* pTIM, uint8_t Channel, uint8_t Duty)
{
	uint32_t tmpPluse;
	
	tmpPluse = pTIM->ARR;
	switch(Channel)
	{
		case 0: pTIM->CCR1 = tmpPluse * Duty / 100; break;
		case 1: pTIM->CCR2 = tmpPluse * Duty / 100; break;
		case 2: pTIM->CCR3 = tmpPluse * Duty / 100; break;
		case 3: pTIM->CCR4 = tmpPluse * Duty / 100; break;
	}
	
	return 0x00;
}

uint8_t CslPWMOut_Init(TIM_TypeDef* pTIM, GPIO_TypeDef* pGPIO, uint16_t Pin, uint8_t Channel, uint32_t Freq)
{
	uint32_t tmpPeriod;
	uint16_t tmpPsc;
	
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TimeBaseInitStruct;
	TIM_OCInitTypeDef  OCInitStruct;
	
	switch((uint32_t)pTIM)
	{
		case (uint32_t)TIM1: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); tmpPeriod = 72000000; break;
		case (uint32_t)TIM2: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); tmpPeriod = 36000000; break;
		case (uint32_t)TIM3: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); tmpPeriod = 36000000; break;
		case (uint32_t)TIM4: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); tmpPeriod = 36000000; break;
		case (uint32_t)TIM5: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); tmpPeriod = 36000000; break;
		case (uint32_t)TIM8: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); tmpPeriod = 72000000; break;
		case (uint32_t)TIM9: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE); tmpPeriod = 72000000; break;
		case (uint32_t)TIM10: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE); tmpPeriod = 72000000; break;
		case (uint32_t)TIM11: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE); tmpPeriod = 72000000; break;
		case (uint32_t)TIM12: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE); tmpPeriod = 36000000; break;
		case (uint32_t)TIM13: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE); tmpPeriod = 36000000; break;
		case (uint32_t)TIM14: RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE); tmpPeriod = 36000000; break;
		case (uint32_t)TIM15: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE); tmpPeriod = 72000000; break;
		case (uint32_t)TIM16: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, ENABLE); tmpPeriod = 72000000; break;
		case (uint32_t)TIM17: RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE); tmpPeriod = 72000000; break;
		default: return (uint8_t)-1;
	}
	RCC_APB2PeriphClockCmd(GPIO2RCC(pGPIO) | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(pGPIO, &GPIO_InitStruct);
	
	tmpPsc = 1;
	while(tmpPeriod / Freq > 65536)
	{
		tmpPeriod /= 10;
		tmpPsc *= 10;
	}
	TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBaseInitStruct.TIM_Period = tmpPeriod / Freq - 1;
	TimeBaseInitStruct.TIM_Prescaler = tmpPsc - 1;
	TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(pTIM, &TimeBaseInitStruct);
	
	OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	OCInitStruct.TIM_Pulse = tmpPeriod / Freq / 2;
	switch(Channel)
	{
		case 0: TIM_OC1Init(pTIM, &OCInitStruct); TIM_OC1PreloadConfig(pTIM, TIM_OCPreload_Enable); break;
		case 1: TIM_OC2Init(pTIM, &OCInitStruct); TIM_OC2PreloadConfig(pTIM, TIM_OCPreload_Enable); break;
		case 2: TIM_OC3Init(pTIM, &OCInitStruct); TIM_OC3PreloadConfig(pTIM, TIM_OCPreload_Enable); break;
		case 3: TIM_OC4Init(pTIM, &OCInitStruct); TIM_OC4PreloadConfig(pTIM, TIM_OCPreload_Enable); break;
		default : return (uint8_t)-1;
	}
	
  TIM_ARRPreloadConfig(pTIM, ENABLE);
	TIM_Cmd(pTIM, ENABLE);
	
	TIM_CtrlPWMOutputs(pTIM, ENABLE);
	
	return 0x00;
}



