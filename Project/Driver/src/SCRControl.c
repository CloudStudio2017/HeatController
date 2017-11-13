#include "SCRControl.h"

//PC9 Samp
//PD12 PD13

volatile static uint8_t SCRC_DutyData[2] = {0, 0};


void SCRControl_SetDuty(uint8_t NewDuty, uint8_t Channel)
{
	if(NewDuty > SCRControl_DUTY_MAX)
		NewDuty = SCRControl_DUTY_MAX;
	else if(NewDuty < SCRControl_DUTY_MIN)
		NewDuty = 0;
	switch(Channel)
	{
		case 0:
			SCRC_DutyData[0] = NewDuty;
			break;
		case 1:
			SCRC_DutyData[1] = NewDuty;
			break;
		default:
			return;
	}
}

void SCRControl_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(GPIO2RCC(SCRControl_Samp_GPIO) |
	                       GPIO2RCC(SCRControl_CH0_GPIO)  |
	                       GPIO2RCC(SCRControl_CH1_GPIO)  |
	                       RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = SCRControl_Samp_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SCRControl_Samp_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Pin = SCRControl_CH0_PIN;
	GPIO_Init(SCRControl_CH0_GPIO, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = SCRControl_CH1_PIN;
	GPIO_Init(SCRControl_CH1_GPIO, &GPIO_InitStruct);
	
	GPIO_ResetBits(SCRControl_CH0_GPIO, SCRControl_CH0_PIN);
	GPIO_ResetBits(SCRControl_CH1_GPIO, SCRControl_CH1_PIN);
	
	EXTI_InitStruct.EXTI_Line = SCRControl_Samp_PIN;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	GPIO_EXTILineConfig(SCRControl_Samp_PortSource, SCRControl_Scamp_PinSource);
	
  NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_DeInit(TIM4);
	TIM_BaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_BaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStruct.TIM_Period = SCRControl_DUTY_OVERFLOW;
	TIM_BaseInitStruct.TIM_Prescaler = 36 * 200 - 1;  //100 us each duty when APB1 clock is 36MHz
	TIM_BaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_BaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStruct.TIM_Pulse = SCRControl_DUTY_OVERFLOW;
	TIM_OC1Init(TIM4, &TIM_OCInitStruct);
	TIM_OC2Init(TIM4, &TIM_OCInitStruct);
	
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_IT_CC1, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
}

void SCRControl_DelayUpdate(void)
{
	TIM_Cmd(TIM4, DISABLE);
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
	TIM_SetAutoreload(TIM4, SCRControl_DUTY_OVERFLOW);
	TIM_SetCounter(TIM4, 0);
	if(SCRC_DutyData[0] >= SCRControl_DUTY_MIN)
	{
		TIM_SetCompare1(TIM4, 100 - SCRC_DutyData[0]);
	}
	else
	{
		TIM_SetCompare1(TIM4, SCRControl_DUTY_OVERFLOW + 10);
	}
	if(SCRC_DutyData[1] >= SCRControl_DUTY_MIN)
	{
		TIM_SetCompare2(TIM4, 100 - SCRC_DutyData[1]);
	}
	else
	{
		TIM_SetCompare2(TIM4, SCRControl_DUTY_OVERFLOW + 10);
	}
	TIM_Cmd(TIM4, ENABLE);
}

void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line9) != RESET)
  {
		GPIO_ResetBits(SCRControl_CH0_GPIO, SCRControl_CH0_PIN);
		GPIO_ResetBits(SCRControl_CH1_GPIO, SCRControl_CH1_PIN);
		SCRControl_DelayUpdate();
    /* Clear the  EXTI line 9 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line9);
  }
}

void TIM4_IRQHandler(void)
{
	/* Channel 0 */
	if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
	{
		if(SCRC_DutyData[0] >= SCRControl_DUTY_MIN)
			GPIO_SetBits(SCRControl_CH0_GPIO, SCRControl_CH0_PIN);
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);
	}
	
	/* Channel 1 */
	if(TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)
	{
		if(SCRC_DutyData[1] >= SCRControl_DUTY_MIN)
			GPIO_SetBits(SCRControl_CH1_GPIO, SCRControl_CH1_PIN);
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
	}
	
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		TIM_Cmd(TIM4, DISABLE);
		GPIO_ResetBits(SCRControl_CH0_GPIO, SCRControl_CH0_PIN);
		GPIO_ResetBits(SCRControl_CH1_GPIO, SCRControl_CH1_PIN);
	}
}
