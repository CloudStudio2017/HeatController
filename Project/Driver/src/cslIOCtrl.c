#include "CslIOCtrl.h"


uint8_t CslIOCtrl_Reg(CslIOCtrl_RegTypeDef* pIO)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(GPIO2RCC(pIO->GPIO), ENABLE);
	
	switch(pIO->IOMode)
	{
		case IOMode_Level_Out:
			if(pIO->Device.AsLevel == NULL)
				return (uint8_t)-1;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_InitStruct.GPIO_Pin = pIO->Pin;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
			GPIO_Init(pIO->GPIO, &GPIO_InitStruct);
			break;
		case IOMode_Level_In:
			if(pIO->Device.AsLevel == NULL)
				return (uint8_t)-1;
			switch(pIO->Device.AsLevel->Res)
			{
				case 0: GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; break;
				case 1: GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; break;
				case 2: GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; break;
			}
			GPIO_InitStruct.GPIO_Pin = pIO->Pin;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
			GPIO_Init(pIO->GPIO, &GPIO_InitStruct);
			break;
		case IOMode_PWM_Out:
			if(pIO->Device.AsPWM == NULL)
				return (uint8_t)-1;
			break;
		case IOMode_PWM_In:
			if(pIO->Device.AsPWM == NULL)
				return (uint8_t)-1;
			break;
		case IOMode_Analog_Out:
			if(pIO->Device.AsAnalog == NULL)
				return (uint8_t)-1;
			break;
		case IOMode_Analog_In:
			if(pIO->Device.AsAnalog == NULL)
				return (uint8_t)-1;
			break;
		case IOMode_SCR_Out:
			if(pIO->Device.AsSCR == NULL)
				return (uint8_t)-1;
			break;
		case IOMode_NULL:
			return (uint8_t)-1;
	}
	
	return 0x00;
}

uint8_t CslIOCtrl_SetLevelOut(CslIOCtrl_RegTypeDef* pIO, uint8_t NewMode)
{
	uint8_t tmp;
	
	if(pIO->IOMode == IOMode_Level_Out)
	{
		NewMode = NewMode?1:0;
		tmp = pIO->Device.AsLevel->ActiveLevel?1:0;
		if(NewMode ^ tmp)
		{
			GPIO_ResetBits(pIO->GPIO, pIO->Pin);
		}
		else
		{
			GPIO_SetBits(pIO->GPIO, pIO->Pin);
		}
		return 0x00;
	}
	return (uint8_t)-1;
}

uint8_t CslIOCtrl_GetLevelIn(CslIOCtrl_RegTypeDef* pIO, uint8_t* pResult)
{
	uint8_t tmp;
	
	if(pIO->IOMode == IOMode_Level_In)
	{
		if(GPIO_ReadInputDataBit(pIO->GPIO, pIO->Pin) != RESET)
		{
			*pResult = 1;
		}
		else
		{
			*pResult = 0;
		}
		return 0x00;
	}
	return (uint8_t)-1;
}

uint8_t CslIOCtrl_SetPWMOut(CslIOCtrl_RegTypeDef* pIO, uint32_t Duty)
{
	if(pIO->IOMode == IOMode_PWM_Out)
	{
	}
	return (uint8_t)-1;
}

uint8_t CslIOCtrl_SetSCROut(CslIOCtrl_RegTypeDef* pIO, uint8_t Duty)
{
	if(pIO->IOMode == IOMode_SCR_Out)
	{
		SCRControl_SetDuty(Duty, pIO->Device.AsSCR->Channel);
		return 0x00;
	}
	return (uint8_t)-1;
}

