#include "max6675.h"



unsigned char MAX6675_GetTemp(unsigned short* pData)
{
	volatile unsigned char j;
	unsigned char i;
	unsigned short tmpData = 0;
	
	MAX6675_CS_1;
	MAX6675_SCK_0;
	MAX6675_CS_0;

	for(i=0;i<16;i++)
	{
		MAX6675_SCK_1;
		for(j=0;j<100;j++);
		tmpData <<= 1;
		if(MAX6675_SO != RESET)
		{
			tmpData |= 0x0001;
		}
		MAX6675_SCK_0;
		for(j=0;j<100;j++);
	}
	
	MAX6675_CS_1;
	
	if(((MAX6675_LineDataType*)&tmpData)->DeviceID)
	{
		return MAX6675_ERR_DEVICE;
	}
	if(((MAX6675_LineDataType*)&tmpData)->SensorOffline)
	{
		return MAX6675_ERR_SENSOR;
	}
	*pData = ((MAX6675_LineDataType*)&tmpData)->Data / 4;
	
	return MAX6675_NOERR;
}

unsigned char MAX6675_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(GPIO2RCC(MAX6675_SCK_GPIO) | GPIO2RCC(MAX6675_CS_GPIO) | GPIO2RCC(MAX6675_SO_GPIO), ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = MAX6675_CS_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(MAX6675_CS_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = MAX6675_SCK_PIN;
	GPIO_Init(MAX6675_SCK_GPIO, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = MAX6675_SO_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(MAX6675_SO_GPIO, &GPIO_InitStruct);
	
	return 0;
}
