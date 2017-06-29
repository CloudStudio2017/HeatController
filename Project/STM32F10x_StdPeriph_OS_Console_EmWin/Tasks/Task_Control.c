#include "stm32f10x.h"
#include "Task_Control.h"
#include "myButton.h"
#include "myLed.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)

static volatile uint16_t ADCConvertedValue;

static void Control_ADC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	DMA_DeInit(DMA1_Channel1);
  DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStruct.DMA_MemoryBaseAddr     = (uint32_t)&ADCConvertedValue;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = 1;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_High;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStruct);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_InitStruct.ADC_Mode               = ADC_Mode_Independent;
  ADC_InitStruct.ADC_ScanConvMode       = ENABLE;
  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStruct.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
  ADC_InitStruct.ADC_DataAlign          = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_NbrOfChannel       = 1;
  ADC_Init(ADC1, &ADC_InitStruct);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_55Cycles5);
	
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));
	
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

static void Control_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void Control_LowLevel_Init(void)
{
	Control_IO_Init();
	Control_ADC_Init();
	
	myLed_Init();
	myLed_Off(0);
	myLed_Off(1);
	myLed_Off(2);
	myLed_Off(3);
	myLed_Off(4);
	myLed_Off(5);
	myLed_Off(6);
	myLed_Off(7);
}

static uint32_t Is_Init=0;

void vTask_Control( void *pvParameters )
{
	Control_LowLevel_Init();
	
	Is_Init = CONTROL_INIT_DONE;
	xQueueSendToBack(InitQueue, &Is_Init, 0);
	
	while(1)
	{
		myLed_On(0);
		vTaskDelay(200);
		myLed_On(1);
		vTaskDelay(200);
		myLed_On(2);
		vTaskDelay(200);
		myLed_On(3);
		vTaskDelay(200);
		myLed_On(4);
		vTaskDelay(200);
		myLed_On(5);
		vTaskDelay(200);
		myLed_On(6);
		vTaskDelay(200);
		myLed_On(7);
		vTaskDelay(200);
		
		myLed_Off(0);
		vTaskDelay(200);
		myLed_Off(1);
		vTaskDelay(200);
		myLed_Off(2);
		vTaskDelay(200);
		myLed_Off(3);
		vTaskDelay(200);
		myLed_Off(4);
		vTaskDelay(200);
		myLed_Off(5);
		vTaskDelay(200);
		myLed_Off(6);
		vTaskDelay(200);
		myLed_Off(7);
		vTaskDelay(200);
	}
}
