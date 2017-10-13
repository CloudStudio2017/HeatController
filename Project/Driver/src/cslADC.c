#include "cslADC.h"
#include "board.h"

#define ADC1_DR_Address    ((uint32_t)0x4001244C)
static volatile uint16_t CslADC_Value[3];

uint8_t CslADC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | GPIO2RCC(_ADC_CH1_GPIO) | GPIO2RCC(_ADC_CH2_GPIO) | GPIO2RCC(_ADC_CH3_GPIO), ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = _ADC_CH1_PIN | _ADC_CH2_PIN | _ADC_CH3_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	DMA_DeInit(DMA1_Channel1);
  DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStruct.DMA_MemoryBaseAddr     = (uint32_t)&CslADC_Value;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = 3;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_High;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStruct);
	
	
	ADC_InitStruct.ADC_Mode               = ADC_Mode_Independent;
  ADC_InitStruct.ADC_ScanConvMode       = ENABLE;
  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStruct.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
  ADC_InitStruct.ADC_DataAlign          = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_NbrOfChannel       = 3;
  ADC_Init(ADC1, &ADC_InitStruct);
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 3, ADC_SampleTime_55Cycles5);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_DMACmd(ADC1, ENABLE);
	
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

uint16_t CslADC_GetADCValue(uint8_t Channel)
{
	if(Channel < 3)
		return CslADC_Value[Channel];
	else
		return -1;
}




