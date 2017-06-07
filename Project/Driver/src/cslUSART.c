#include "CslUSART.h"

static uint8_t         CslUSART_Status_tbl[6]={0};
static CslUSART_CBType CslUSART_TxHandler_tbl[6];
static CslUSART_CBType CslUSART_RxHandler_tbl[6];


uint8_t CslUSART_Reg(CslUSART_Enum CslUSART_Port, CslUSART_RegType* pCslUSART_RegStruct)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	uint16_t NVIC_USART_IT_Config = 0x0000;
	
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
	
	USART_InitStructure.USART_BaudRate            = pCslUSART_RegStruct->USART_BaudRate;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = pCslUSART_RegStruct->USART_Mode;
	USART_InitStructure.USART_Parity              = pCslUSART_RegStruct->USART_Parity;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;

	switch(CslUSART_Port)
	{
#if CSLUSART_1_USE
		case CSLUSART1:
			if(CslUSART_Status_tbl[0] != 0)
				return (uint8_t)-2;
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
			if(USART_InitStructure.USART_Mode & USART_Mode_Tx)
			{
				RCC_APB2PeriphClockCmd(GPIO2RCC(CSLUSART_1_Tx_GPIO), ENABLE);
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Pin = GPIOPinIndex2Pin(CSLUSART_1_Tx_PinIndex);
				GPIO_Init(CSLUSART_1_Tx_GPIO, &GPIO_InitStructure);
			}
			if(USART_InitStructure.USART_Mode & USART_Mode_Rx)
			{
				RCC_APB2PeriphClockCmd(GPIO2RCC(CSLUSART_1_Rx_GPIO), ENABLE);
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_InitStructure.GPIO_Pin = GPIOPinIndex2Pin(CSLUSART_1_Rx_PinIndex);
				GPIO_Init(CSLUSART_1_Rx_GPIO, &GPIO_InitStructure);
			}
			USART_Init(USART1, &USART_InitStructure);
			USART_Cmd(USART1, ENABLE);
			
			if((pCslUSART_RegStruct->USART_TxHandler == NULL) &&
				 (pCslUSART_RegStruct->USART_RxHandler == NULL))
			{
				NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
			}
			else
			{
				NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CSLUSART_1_NVIC_IRQCPP;
				NVIC_InitStructure.NVIC_IRQChannelSubPriority        = CSLUSART_1_NVIC_SP;
				NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
				if(pCslUSART_RegStruct->USART_TxHandler != NULL)
				{
					NVIC_USART_IT_Config |= USART_IT_TXE;
					CslUSART_TxHandler_tbl[0] = pCslUSART_RegStruct->USART_TxHandler;
				}
				if(pCslUSART_RegStruct->USART_RxHandler != NULL)
				{
					NVIC_USART_IT_Config |= USART_IT_RXNE;
					CslUSART_RxHandler_tbl[0] = pCslUSART_RegStruct->USART_RxHandler;
				}
				USART_ITConfig(USART1, NVIC_USART_IT_Config, ENABLE);
			}
			NVIC_Init(&NVIC_InitStructure);
			break;
#endif
#if CSLUSART_2_USE
		case CSLUSART2:
			if(CslUSART_Status_tbl[1] != 0)
				return (uint8_t)-2;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
			if(USART_InitStructure.USART_Mode & USART_Mode_Tx)
			{
				RCC_APB2PeriphClockCmd(GPIO2RCC(CSLUSART_2_Tx_GPIO), ENABLE);
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Pin = GPIOPinIndex2Pin(CSLUSART_2_Tx_PinIndex);
				GPIO_Init(CSLUSART_2_Tx_GPIO, &GPIO_InitStructure);
			}
			if(USART_InitStructure.USART_Mode & USART_Mode_Rx)
			{
				RCC_APB2PeriphClockCmd(GPIO2RCC(CSLUSART_2_Rx_GPIO), ENABLE);
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_InitStructure.GPIO_Pin = GPIOPinIndex2Pin(CSLUSART_2_Rx_PinIndex);
				GPIO_Init(CSLUSART_2_Rx_GPIO, &GPIO_InitStructure);
			}
			USART_Init(USART2, &USART_InitStructure);
			USART_Cmd(USART2, ENABLE);
			
			if((pCslUSART_RegStruct->USART_TxHandler == NULL) &&
				 (pCslUSART_RegStruct->USART_RxHandler == NULL))
			{
				NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
			}
			else
			{
				NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CSLUSART_2_NVIC_IRQCPP;
				NVIC_InitStructure.NVIC_IRQChannelSubPriority        = CSLUSART_2_NVIC_SP;
				NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn;
				if(pCslUSART_RegStruct->USART_TxHandler != NULL)
				{
					NVIC_USART_IT_Config |= USART_IT_TXE;
					CslUSART_TxHandler_tbl[1] = pCslUSART_RegStruct->USART_TxHandler;
				}
				if(pCslUSART_RegStruct->USART_RxHandler != NULL)
				{
					NVIC_USART_IT_Config |= USART_IT_RXNE;
					CslUSART_RxHandler_tbl[1] = pCslUSART_RegStruct->USART_RxHandler;
				}
				USART_ITConfig(USART2, NVIC_USART_IT_Config, ENABLE);
			}
			NVIC_Init(&NVIC_InitStructure);
			break;
#endif
#if CSLUSART_3_USE
		case CSLUSART3:
			if(CslUSART_Status_tbl[2] != 0)
				return (uint8_t)-2;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
			if(USART_InitStructure.USART_Mode & USART_Mode_Tx)
			{
				RCC_APB2PeriphClockCmd(GPIO2RCC(CSLUSART_3_Tx_GPIO), ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIOPinIndex2Pin(CSLUSART_3_Tx_PinIndex);
				GPIO_Init(CSLUSART_3_Tx_GPIO, &GPIO_InitStructure);
			}
			if(USART_InitStructure.USART_Mode & USART_Mode_Rx)
			{
				RCC_APB2PeriphClockCmd(GPIO2RCC(CSLUSART_3_Rx_GPIO), ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIOPinIndex2Pin(CSLUSART_3_Rx_PinIndex);
				GPIO_Init(CSLUSART_3_Rx_GPIO, &GPIO_InitStructure);
			}
			USART_Init(USART3, &USART_InitStructure);
			USART_Cmd(USART3, ENABLE);
			
			if((pCslUSART_RegStruct->USART_TxHandler == NULL) &&
				 (pCslUSART_RegStruct->USART_RxHandler == NULL))
			{
				NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
			}
			else
			{
				NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CSLUSART_3_NVIC_IRQCPP;
				NVIC_InitStructure.NVIC_IRQChannelSubPriority        = CSLUSART_3_NVIC_SP;
				NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
				if(pCslUSART_RegStruct->USART_TxHandler != NULL)
				{
					NVIC_USART_IT_Config |= USART_IT_TXE;
					CslUSART_TxHandler_tbl[2] = pCslUSART_RegStruct->USART_TxHandler;
				}
				if(pCslUSART_RegStruct->USART_RxHandler != NULL)
				{
					NVIC_USART_IT_Config |= USART_IT_RXNE;
					CslUSART_RxHandler_tbl[2] = pCslUSART_RegStruct->USART_RxHandler;
				}
				USART_ITConfig(USART3, NVIC_USART_IT_Config, ENABLE);
			}
			NVIC_Init(&NVIC_InitStructure);
			break;
#endif
#if CSLUSART_4_USE
		case CSLUSART4:
			if(CslUSART_Status_tbl[3] != 0)
				return (uint8_t)-2;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
			if(USART_InitStructure.USART_Mode & USART_Mode_Tx)
			{
				RCC_APB2PeriphClockCmd(GPIO2RCC(CSLUSART_4_Tx_GPIO), ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIOPinIndex2Pin(CSLUSART_4_Tx_PinIndex);
				GPIO_Init(CSLUSART_4_Tx_GPIO, &GPIO_InitStructure);
			}
			if(USART_InitStructure.USART_Mode & USART_Mode_Rx)
			{
				RCC_APB2PeriphClockCmd(GPIO2RCC(CSLUSART_4_Rx_GPIO), ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIOPinIndex2Pin(CSLUSART_4_Rx_PinIndex);
				GPIO_Init(CSLUSART_4_Rx_GPIO, &GPIO_InitStructure);
			}
			USART_Init(UART4, &USART_InitStructure);
			USART_Cmd(UART4, ENABLE);
			
			if((pCslUSART_RegStruct->USART_TxHandler == NULL) &&
				 (pCslUSART_RegStruct->USART_RxHandler == NULL))
			{
				NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
			}
			else
			{
				NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CSLUSART_4_NVIC_IRQCPP;
				NVIC_InitStructure.NVIC_IRQChannelSubPriority        = CSLUSART_4_NVIC_SP;
				NVIC_InitStructure.NVIC_IRQChannel                   = UART4_IRQn;
				if(pCslUSART_RegStruct->USART_TxHandler != NULL)
				{
					NVIC_USART_IT_Config |= USART_IT_TXE;
					CslUSART_TxHandler_tbl[3] = pCslUSART_RegStruct->USART_TxHandler;
				}
				if(pCslUSART_RegStruct->USART_RxHandler != NULL)
				{
					NVIC_USART_IT_Config |= USART_IT_RXNE;
					CslUSART_RxHandler_tbl[3] = pCslUSART_RegStruct->USART_RxHandler;
				}
				USART_ITConfig(UART4, NVIC_USART_IT_Config, ENABLE);
			}
			NVIC_Init(&NVIC_InitStructure);
			break;
#endif
#if CSLUSART_5_USE
		case CSLUSART5:
			if(CslUSART_Status_tbl[4] != 0)
				return (uint8_t)-2;
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
			if(USART_InitStructure.USART_Mode & USART_Mode_Tx)
			{
				RCC_APB2PeriphClockCmd(GPIO2RCC(CSLUSART_5_Tx_GPIO), ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIOPinIndex2Pin(CSLUSART_5_Tx_PinIndex);
				GPIO_Init(CSLUSART_5_Tx_GPIO, &GPIO_InitStructure);
			}
			if(USART_InitStructure.USART_Mode & USART_Mode_Rx)
			{
				RCC_APB2PeriphClockCmd(GPIO2RCC(CSLUSART_5_Rx_GPIO), ENABLE);
				GPIO_InitStructure.GPIO_Pin = GPIOPinIndex2Pin(CSLUSART_5_Rx_PinIndex);
				GPIO_Init(CSLUSART_5_Rx_GPIO, &GPIO_InitStructure);
			}
			USART_Init(UART5, &USART_InitStructure);
			USART_Cmd(UART5, ENABLE);
			
			if((pCslUSART_RegStruct->USART_TxHandler == NULL) &&
				 (pCslUSART_RegStruct->USART_RxHandler == NULL))
			{
				NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
			}
			else
			{
				NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CSLUSART_5_NVIC_IRQCPP;
				NVIC_InitStructure.NVIC_IRQChannelSubPriority        = CSLUSART_5_NVIC_SP;
				NVIC_InitStructure.NVIC_IRQChannel                   = UART5_IRQn;
				if(pCslUSART_RegStruct->USART_TxHandler != NULL)
				{
					NVIC_USART_IT_Config |= USART_IT_TXE;
					CslUSART_TxHandler_tbl[4] = pCslUSART_RegStruct->USART_TxHandler;
				}
				if(pCslUSART_RegStruct->USART_RxHandler != NULL)
				{
					NVIC_USART_IT_Config |= USART_IT_RXNE;
					CslUSART_RxHandler_tbl[4] = pCslUSART_RegStruct->USART_RxHandler;
				}
				USART_ITConfig(UART5, NVIC_USART_IT_Config, ENABLE);
			}
			NVIC_Init(&NVIC_InitStructure);
			break;
#endif
		default:
			return (uint8_t)-1;
	}
	return 0;
}

uint8_t CslUSART_UnReg(CslUSART_Enum CslUSART_Port)
{
	switch(CslUSART_Port)
	{
#if CSLUSART_1_USE
		case CSLUSART1:
			CslUSART_Status_tbl[0] = 0;
			CslUSART_TxHandler_tbl[0] = NULL;
			CslUSART_RxHandler_tbl[0] = NULL;
			break;
#endif
#if CSLUSART_2_USE
		case CSLUSART2:
			CslUSART_Status_tbl[1] = 0;
			CslUSART_TxHandler_tbl[1] = NULL;
			CslUSART_RxHandler_tbl[1] = NULL;
			break;
#endif
#if CSLUSART_3_USE
		case CSLUSART3:
			CslUSART_Status_tbl[2] = 0;
			CslUSART_TxHandler_tbl[2] = NULL;
			CslUSART_RxHandler_tbl[2] = NULL;
			break;
#endif
#if CSLUSART_4_USE
		case CSLUSART4:
			CslUSART_Status_tbl[3] = 0;
			CslUSART_TxHandler_tbl[3] = NULL;
			CslUSART_RxHandler_tbl[3] = NULL;
			break;
#endif
#if CSLUSART_5_USE
		case CSLUSART5:
			CslUSART_Status_tbl[4] = 0;
			CslUSART_TxHandler_tbl[4] = NULL;
			CslUSART_RxHandler_tbl[4] = NULL;
			break;
#endif
		default:
			return (uint8_t)-1;
	}
	return 0;
}

uint8_t CslUSART_SendByte(CslUSART_Enum CslUSART_Port, uint16_t wData)
{
	switch(CslUSART_Port)
	{
#if CSLUSART_1_USE
		case CSLUSART1:
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE == RESET));
			USART_SendData(USART1, wData);
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
			break;
#endif
#if CSLUSART_2_USE
		case CSLUSART2:
			while(USART_GetFlagStatus(USART2, USART_FLAG_TXE == RESET));
			USART_SendData(USART2, wData);
			while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
			break;
#endif
#if CSLUSART_3_USE
		case CSLUSART3:
			while(USART_GetFlagStatus(USART3, USART_FLAG_TXE == RESET));
			USART_SendData(USART3, wData);
			while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
			break;
#endif
#if CSLUSART_4_USE
		case CSLUSART4:
			while(USART_GetFlagStatus(UART4, USART_FLAG_TXE == RESET));
			USART_SendData(UART4, wData);
			while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
			break;
#endif
#if CSLUSART_5_USE
		case CSLUSART5:
			while(USART_GetFlagStatus(UART5, USART_FLAG_TXE == RESET));
			USART_SendData(UART5, wData);
			while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);
			break;
#endif
		default:
			return (uint8_t)-1;
	}
	return 0;
}

uint8_t CslUSART_ReciveByte(CslUSART_Enum CslUSART_Port)
{
	switch(CslUSART_Port)
	{
#if CSLUSART_1_USE
		case CSLUSART1:
			while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
			return (uint8_t)USART_ReceiveData(USART1);
#endif
#if CSLUSART_2_USE
		case CSLUSART2:
			while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
			return (uint8_t)USART_ReceiveData(USART2);
#endif
#if CSLUSART_3_USE
		case CSLUSART3:
			while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
			return (uint8_t)USART_ReceiveData(USART3);
#endif
#if CSLUSART_4_USE
		case CSLUSART4:
			while(USART_GetFlagStatus(UART4, USART_FLAG_RXNE) == RESET);
			return (uint8_t)USART_ReceiveData(UART4);
#endif
#if CSLUSART_5_USE
		case CSLUSART5:
			while(USART_GetFlagStatus(UART5, USART_FLAG_RXNE) == RESET);
			return (uint8_t)USART_ReceiveData(UART5);
#endif
		default:
			return (uint8_t)-1;
	}
	return 0xFF;
}

//USART Interrupt Service Code Area
#if CSLUSART_1_USE
void USART1_IRQHandler(void)
{
	uint8_t TempData;
	
	if((CslUSART_TxHandler_tbl[0] != NULL) &&
		 (USART_GetFlagStatus(USART1, USART_FLAG_TXE) != RESET))
	{
		USART_ClearITPendingBit(USART1, USART_IT_TXE);
		(CslUSART_TxHandler_tbl[0])(0);
	}
	if((CslUSART_RxHandler_tbl[0] != NULL) &&
		 (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET))
	{
		TempData = USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		(CslUSART_RxHandler_tbl[0])(TempData);
	}
}
#endif
#if CSLUSART_2_USE
void USART2_IRQHandler(void)
{
	uint8_t TempData;
	
	if((CslUSART_TxHandler_tbl[1] != NULL) &&
		 (USART_GetFlagStatus(USART2, USART_FLAG_TXE) != RESET))
	{
		USART_ClearITPendingBit(USART2, USART_IT_TXE);
		(CslUSART_TxHandler_tbl[1])(0);
	}
	if((CslUSART_RxHandler_tbl[1] != NULL) &&
		 (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET))
	{
		TempData = USART_ReceiveData(USART2);
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		(CslUSART_RxHandler_tbl[1])(TempData);
	}
}
#endif
#if CSLUSART_3_USE
void USART3_IRQHandler(void)
{
	uint8_t TempData;
	
	if((CslUSART_TxHandler_tbl[2] != NULL) &&
		 (USART_GetFlagStatus(USART3, USART_FLAG_TXE) != RESET))
	{
		USART_ClearITPendingBit(USART3, USART_IT_TXE);
		(CslUSART_TxHandler_tbl[2])(0);
	}
	if((CslUSART_RxHandler_tbl[2] != NULL) &&
		 (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) != RESET))
	{
		TempData = USART_ReceiveData(USART3);
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		(CslUSART_RxHandler_tbl[2])(TempData);
	}
}
#endif
#if CSLUSART_4_USE
void UART4_IRQHandler(void)
{
	uint8_t TempData;
	
	if((CslUSART_TxHandler_tbl[3] != NULL) &&
		 (USART_GetFlagStatus(UART4, USART_FLAG_TXE) != RESET))
	{
		USART_ClearITPendingBit(UART4, USART_IT_TXE);
		(CslUSART_TxHandler_tbl[3])(0);
	}
	if((CslUSART_RxHandler_tbl[3] != NULL) &&
		 (USART_GetFlagStatus(UART4, USART_FLAG_RXNE) != RESET))
	{
		TempData = USART_ReceiveData(UART4);
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
		(CslUSART_RxHandler_tbl[3])(TempData);
	}
}
#endif
#if CSLUSART_5_USE
void UART5_IRQHandler(void)
{
	uint8_t TempData;
	
	if((CslUSART_TxHandler_tbl[4] != NULL) &&
		 (USART_GetFlagStatus(UART5, USART_FLAG_TXE) != RESET))
	{
		USART_ClearITPendingBit(UART5, USART_IT_TXE);
		(CslUSART_TxHandler_tbl[4])(0);
	}
	if((CslUSART_RxHandler_tbl[4] != NULL) &&
		 (USART_GetFlagStatus(UART5, USART_FLAG_RXNE) != RESET))
	{
		TempData = USART_ReceiveData(USART1);
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
		(CslUSART_RxHandler_tbl[4])(TempData);
	}
}
#endif


