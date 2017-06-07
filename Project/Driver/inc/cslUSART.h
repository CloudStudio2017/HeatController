// <<< Use Configuration Wizard in Context Menu >>>


#ifndef __CSL_USART_H__
#define __CSL_USART_H__


#include "stm32f10x.h"
#include "cslCommon.h"


//<e> Csl Uart1 Use
#define CSLUSART_1_USE  1
//  <o>TxPin
//    <0=>PA9
//    <1=>PB6
#define CSLUART_1_TXPIN_SEL 0
#if   CSLUART_1_TXPIN_SEL == 0
  #define CSLUSART_1_MAP_A9
#elif CSLUART_1_TXPIN_SEL == 1
  #define CSLUSART_1_MAP_B6
#endif
//  <o>RxPin
//    <0=>PA10
//    <1=>PB7
#define CSLUART_1_RXPIN_SEL 0
#if   CSLUART_1_RXPIN_SEL == 0
  #define CSLUSART_1_MAP_A10
#elif CSLUART_1_RXPIN_SEL == 1
  #define CSLUSART_1_MAP_B7
#endif
//</e>

//<e> Csl Uart2 Use
#define CSLUSART_2_USE  0
//  <o>TxPin
//    <0=>PA2
//    <1=>PD5
#define CSLUART_2_TXPIN_SEL 0
#if   CSLUART_2_TXPIN_SEL == 0
  #define CSLUSART_2_MAP_A2
#elif CSLUART_2_TXPIN_SEL == 1
  #define CSLUSART_2_MAP_D5
#endif
//  <o>RxPin
//    <0=>PA3
//    <1=>PD6
#define CSLUART_2_RXPIN_SEL 0
#if   CSLUART_2_RXPIN_SEL == 0
  #define CSLUSART_2_MAP_A3
#elif CSLUART_2_RXPIN_SEL == 1
  #define CSLUSART_2_MAP_D6
#endif
//</e>

//<e> Csl Uart3 Use
#define CSLUSART_3_USE  0
//  <o>TxPin
//    <0=>PB10
//    <1=>PC10
//    <2=>PD8
#define CSLUART_3_TXPIN_SEL 0
#if   CSLUART_3_TXPIN_SEL == 0
  #define CSLUSART_3_MAP_B10
#elif CSLUART_3_TXPIN_SEL == 1
  #define CSLUSART_3_MAP_C10
#elif CSLUART_3_TXPIN_SEL == 2
  #define CSLUSART_3_MAP_D8
#endif
//  <o>RxPin
//    <0=>PB11
//    <1=>PC11
//    <2=>PD9
#define CSLUART_3_RXPIN_SEL 0
#if   CSLUART_3_RXPIN_SEL == 0
  #define CSLUSART_3_MAP_B11
#elif CSLUART_3_RXPIN_SEL == 1
  #define CSLUSART_3_MAP_C11
#elif CSLUART_3_RXPIN_SEL == 2
  #define CSLUSART_3_MAP_D9
#endif
//</e>

//<e> Csl Uart4 Use
#define CSLUSART_4_USE  0
//  <o>TxPin
//    <0=>PC10
#define CSLUART_4_TXPIN_SEL 0
#if   CSLUART_4_TXPIN_SEL == 0
  #define CSLUSART_4_MAP_C10
#endif
//  <o>RxPin
//    <0=>PC11
#define CSLUART_4_RXPIN_SEL 0
#if   CSLUART_4_RXPIN_SEL == 0
  #define CSLUSART_4_MAP_C11
#endif
//</e>

//<e> Csl Uart5 Use
#define CSLUSART_5_USE  0
//  <o>TxPin
//    <0=>C12
#define CSLUART_5_RXPIN_SEL 0
#if   CSLUART_5_RXPIN_SEL == 0
  #define CSLUSART_5_MAP_C12
#endif
//  <o>RxPin
//    <0=>D2
#define CSLUART_5_RXPIN_SEL 0
#if   CSLUART_5_RXPIN_SEL == 0
  #define CSLUSART_5_MAP_D2
#endif
//</e>

typedef enum
{
	CSLUSART1 = 1,
	CSLUSART2,
	CSLUSART3,
	CSLUSART4,
	CSLUSART5,
}CslUSART_Enum;

#if 0
	#define CSLUSART_1_MAP_A9
	#define CSLUSART_1_MAP_A10
	#define CSLUSART_2_MAP_A2
	#define CSLUSART_2_MAP_A3
	#define CSLUSART_3_MAP_B10
	#define CSLUSART_3_MAP_B11
	#define CSLUSART_4_MAP_A0
	#define CSLUSART_4_MAP_A1
	#define CSLUSART_5_MAP_C12
	#define CSLUSART_5_MAP_D2
#endif




//STM32F103 All USART IO Map Table
//USART1--Tx-A9/B6--Rx-A10/B7
#if CSLUSART_1_USE
	#if defined CSLUSART_1_MAP_A9
		#define CSLUSART_1_Tx_GPIO GPIOA
		#define CSLUSART_1_Tx_PinIndex  GPIO_PinSource9
	#elif defined CSLUSART_1_MAP_B6
		#define CSLUSART_1_Tx_GPIO GPIOB
		#define CSLUSART_1_Tx_PinIndex  GPIO_PinSource6
	#endif
	#if defined CSLUSART_1_MAP_A10
		#define CSLUSART_1_Rx_GPIO GPIOA
		#define CSLUSART_1_Rx_PinIndex  GPIO_PinSource10
	#elif defined CSLUSART_1_MAP_B7
		#define CSLUSART_1_Rx_GPIO GPIOB
		#define CSLUSART_1_Rx_PinIndex  GPIO_PinSource7
	#endif
//NVIC Config
  #define CSLUSART_1_NVIC_IRQCPP 2  //PreemptionPriority
	#define CSLUSART_1_NVIC_SP     2  //SubPriority
#endif

//USART2--Tx-A2/D5--Rx-A3/D6
#if CSLUSART_2_USE
	#if defined CSLUSART_2_MAP_A2
		#define CSLUSART_2_Tx_GPIO GPIOA
		#define CSLUSART_2_Tx_PinIndex  GPIO_PinSource2
	#elif defined CSLUSART_2_MAP_D5
		#define CSLUSART_2_Tx_GPIO GPIOD
		#define CSLUSART_2_Tx_PinIndex  GPIO_PinSource5
	#endif
	#if defined CSLUSART_2_MAP_A3
		#define CSLUSART_2_Rx_GPIO GPIOA
		#define CSLUSART_2_Rx_PinIndex  GPIO_PinSource3
	#elif defined CSLUSART_2_MAP_D6
		#define CSLUSART_2_Rx_GPIO GPIOD
		#define CSLUSART_2_Rx_PinIndex  GPIO_PinSource6
	#endif
//NVIC Config
  #define CSLUSART_2_NVIC_IRQCPP 2  //PreemptionPriority
	#define CSLUSART_2_NVIC_SP     2  //SubPriority
#endif


//USART3--Tx-B10/C10/D8--Rx-B11/C11/D9
#if CSLUSART_3_USE
	#if defined CSLUSART_3_MAP_B10
		#define CSLUSART_3_Tx_GPIO GPIOB
		#define CSLUSART_3_Tx_PinIndex  GPIO_PinSource10
	#elif defined CSLUSART_3_MAP_C10
		#define CSLUSART_3_Tx_GPIO GPIOC
		#define CSLUSART_3_Tx_PinIndex  GPIO_PinSource10
	#elif defined CSLUSART_3_MAP_D8
	  #define CSLUSART_3_Tx_GPIO GPIOD
		#define CSLUSART_3_Tx_PinIndex  GPIO_PinSource8
	#endif
	#if defined CSLUSART_3_MAP_B11
		#define CSLUSART_3_Rx_GPIO GPIOB
		#define CSLUSART_3_Rx_PinIndex  GPIO_PinSource11
	#elif defined CSLUSART_3_MAP_C11
		#define CSLUSART_3_Rx_GPIO GPIOC
		#define CSLUSART_3_Rx_PinIndex  GPIO_PinSource11
	#elif defined CSLUSART_3_MAP_D9
	  #define CSLUSART_3_Rx_GPIO GPIOD
	  #define CSLUSART_3_Rx_PinIndex  GPIO_PinSource9
	#endif
//NVIC Config
  #define CSLUSART_3_NVIC_IRQCPP 2  //PreemptionPriority
	#define CSLUSART_3_NVIC_SP     2  //SubPriority
#endif

//USART4--Tx-C10--Rx-C11
#if CSLUSART_4_USE
	#if defined CSLUSART_4_MAP_C10
	  #define CSLUSART_4_Tx_GPIO GPIOC
		#define CSLUSART_4_Tx_PinIndex  GPIO_PinSource10
	#endif
	#if defined CSLUSART_4_MAP_C11
	  #define CSLUSART_4_Rx_GPIO GPIOC
		#define CSLUSART_4_Rx_PinIndex  GPIO_PinSource11
	#endif
//NVIC Config
  #define CSLUSART_4_NVIC_IRQCPP 2  //PreemptionPriority
	#define CSLUSART_4_NVIC_SP     2  //SubPriority
#endif


//USART5--Tx-C12--Rx-D2
#if CSLUSART_5_USE
	#if defined CSLUSART_5_MAP_C12
		#define CSLUSART_5_Tx_GPIO GPIOC
		#define CSLUSART_5_Tx_PinIndex  GPIO_PinSource12
	#else
		#define CSLUSART_5_Tx_GPIO GPIOC
		#define CSLUSART_5_Tx_PinIndex  GPIO_PinSource12
	#endif
	#if defined CSLUSART_5_MAP_D2
	  #define CSLUSART_5_Rx_GPIO GPIOD
		#define CSLUSART_5_Rx_PinIndex  GPIO_PinSource2
	#else
		#define CSLUSART_5_Rx_GPIO GPIOD
		#define CSLUSART_5_Rx_PinIndex  GPIO_PinSource2
	#endif
//NVIC Config
  #define CSLUSART_5_NVIC_IRQCPP 2  //PreemptionPriority
	#define CSLUSART_5_NVIC_SP     2  //SubPriority
#endif


typedef struct USARTCB_Struct
{
	void(*InitFunc)(void);
	void(*DataRecFunc)(unsigned char);
	void(*DataSendFunc)(unsigned char);
}USARTCB_Type;


typedef enum
{
	USART_NoEvent = -1,
	USART_RxEvent  = 0,
	USART_TxEvent,
	USART_ErrEvent,
}CSLUSART_Events;


typedef void (*CslUSART_CBType)(uint16_t);
typedef struct CslUSART_RegStruct
{
	CslUSART_CBType USART_TxHandler;
	CslUSART_CBType USART_RxHandler;
	uint32_t       USART_BaudRate;
	uint16_t       USART_Mode;
	uint16_t       USART_Parity;
}CslUSART_RegType;


extern uint8_t CslUSART_Reg(CslUSART_Enum CslUSART_Port, CslUSART_RegType* pCslUSART_RegStruct);
extern uint8_t CslUSART_UnReg(CslUSART_Enum CslUSART_Port);
extern uint8_t CslUSART_SendByte(CslUSART_Enum CslUSART_Port, uint16_t wData);
extern uint8_t CslUSART_ReciveByte(CslUSART_Enum CslUSART_Port);

#endif
