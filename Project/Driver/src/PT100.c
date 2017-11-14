#include "PT100.h"
#include "math.h"

#define A   0.00390802 //3.9083e-3
#define B   -5.802E-07 //-5.775e-7
#define C   -4.2735E-12 //-4.183e-12

#define X100      600    //For   0¡æ
#define X138_5   3000    //For 100¡æ
static const float k = 38.5 / (X138_5 - X100);
static const float b = 100 - k * X100;

float PT100_R2T(float PT100_ResValue)
{
	int i;
	float T0,T1;
	float R = PT100_ResValue;

	T0 = (R / 100 - 1) / A;
	if(R >= 18.52 && R < 100)
	{
		for(i=0; i<50; i++)
		{
			T1 = T0 + (R - 100 * (1 + A*T0 + B*T0*T0 - 100*C*T0*T0*T0 + C*T0*T0*T0*T0)) / (100 * (A + 2*B*T0 - 300*C*T0*T0 + 4*C*T0*T0*T0));
			if(fabs(T1 - T0) < 0.001)
				break;
			else
				T0 = T1;
		}
	}
	else if(R >= 100 && R <= 390.481)
	{
		for(i=0; i<50; i++)
		{
			T1 = T0 + (R - 100 * (1 + A*T0 + B*T0*T0)) / (100 * (A + A*B*T0));
			if(fabs(T1 - T0) < 0.001)
				break;
			else
				T0 = T1;
		}
	}
	else
	{
		T1 = 0.0/0.0;
	}
	return T1;
}

uint8_t PT100_Init(void)
{
	CslADC_Init();
}

float PT100_GetTempValue(void)
{
	uint16_t ADCValue;
	float ResValue;
	float tmpRet;
	
	ADCValue = CslADC_GetADCValue(1);
	ResValue = k * ADCValue + b;

	tmpRet = PT100_R2T(ResValue);
	
	return tmpRet;
}

