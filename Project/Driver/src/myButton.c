#include "myButton.h"



static uint32_t Button_Status[MYBUTTON_ST_COUNT]={0};
static uint32_t Button_HoldTime[MYBUTTON_MAX_COUNT]={0};
static MyButton_RegType myButton_ButtonList[MYBUTTON_MAX_COUNT]={0};


#define GetStatusBits(Button_Index)  ((Button_Status[Button_Index / BUTTON_STATUS_BIT_COUNT] >> ((Button_Index % BUTTON_STATUS_BIT_COUNT) * BUTTON_STATUS_BIT)) & BUTTON_STATUS_MASK)

#define BUTTON_EVENT_FREE_(Button_Index)    (GetStatusBits(Button_Index) == BUTTON_STATUS_FREE)
#define BUTTON_EVENT_PRESS_(Button_Index)   (GetStatusBits(Button_Index) == BUTTON_STATUS_PRESS)
#define BUTTON_EVENT_DOWN_(Button_Index)    (GetStatusBits(Button_Index) == BUTTON_STATUS_DOWN)
#define BUTTON_EVENT_RELEASE_(Button_Index) (GetStatusBits(Button_Index) == BUTTON_STATUS_RELEASE)
#define BUTTON_EVENT_HOLD_(Button_Index)    (GetStatusBits(Button_Index) == BUTTON_STATUS_HOLD)

uint8_t MyButton_Init(void)
{
	return 0;
}

uint8_t ButtonIsUp(uint8_t Index)
{
	volatile uint8_t keyState;
	keyState = GPIO_ReadInputDataBit(myButton_ButtonList[Index].ButtonGPIO, myButton_ButtonList[Index].ButtonPin);
	if((keyState == Bit_SET )&&(myButton_ButtonList[Index].ButtonIdleState == SET))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void MyButton_UpdateStatus(void)
{
  uint8_t i,j;
	uint8_t status;
	uint32_t *pStatus;
  
  for(i=0;i<MYBUTTON_MAX_COUNT;i++)
  {
    if(myButton_ButtonList[i].CallBackFunc == 0)
      continue;
		
		j = i % BUTTON_STATUS_BIT_COUNT;
		pStatus = &Button_Status[i / BUTTON_STATUS_BIT_COUNT];
		status = GetStatusBits(i);
    if(ButtonIsUp(i))
    {
      switch(status)
      {
      case BUTTON_STATUS_PRESS:
        *pStatus &= ~BUTTON_STATUS_MASK_(j);
        *pStatus |= BUTTON_FREE_(j);
        break;
      case BUTTON_STATUS_DOWN:
			case BUTTON_STATUS_HOLD:
        *pStatus &= ~BUTTON_STATUS_MASK_(j);
        *pStatus |= BUTTON_RELEASE_(j);
        break;
      case BUTTON_STATUS_RELEASE:
        *pStatus &= ~BUTTON_STATUS_MASK_(j);
        *pStatus |= BUTTON_FREE_(j);
        break;
      }
    }
    else
    {
      switch(status)
      {
      case BUTTON_STATUS_FREE:
        *pStatus &= ~BUTTON_STATUS_MASK_(j);
        *pStatus |= BUTTON_PRESS_(j);
        break;
      case BUTTON_STATUS_PRESS:
        *pStatus &= ~BUTTON_STATUS_MASK_(j);
        *pStatus |= BUTTON_DOWN_(j);
				Button_HoldTime[i] = 0;
        break;
			case BUTTON_STATUS_DOWN:
				Button_HoldTime[i]++;
				if(Button_HoldTime[i] >= 20)
				{
					*pStatus &= ~BUTTON_STATUS_MASK_(j);
					*pStatus |= BUTTON_HOLD_(j);
				}
				break;
      case BUTTON_STATUS_RELEASE:
        *pStatus &= ~BUTTON_STATUS_MASK_(j);
        *pStatus |= BUTTON_FREE_(j);
        break;
			case BUTTON_STATUS_HOLD:
				break;
      }
    }
  }
}

void MyButton_Process(void)
{
	uint8_t i;
	uint8_t status;

	MyButton_UpdateStatus();

	for(i=0;i<MYBUTTON_MAX_COUNT; i++)
	{
		if(myButton_ButtonList[i].CallBackFunc == NULL)
			continue;

		status = GetStatusBits(i);
		switch(status)
		{
			case BUTTON_STATUS_PRESS:
			case BUTTON_STATUS_RELEASE:
			case BUTTON_STATUS_HOLD:
				//if(myButton_ButtonList[i].ButtonTrigMask & (1 << status))
				{
					myButton_ButtonList[i].CallBackFunc(i, status);
				}
				break;
		}
	}
}

uint8_t MyButton_Reg(unsigned char RegButtonIndex, MyButton_RegType* RegButton)
{
  uint32_t GPIO_RCC;
	if(RegButton->CallBackFunc == NULL)
		return (uint8_t)-2;

	if(myButton_ButtonList[RegButtonIndex].CallBackFunc != 0)
		return (uint8_t)-1;

	myButton_ButtonList[RegButtonIndex].ButtonGPIO      = RegButton->ButtonGPIO;
	myButton_ButtonList[RegButtonIndex].ButtonPin       = RegButton->ButtonPin;
	myButton_ButtonList[RegButtonIndex].CallBackFunc    = RegButton->CallBackFunc;
	myButton_ButtonList[RegButtonIndex].ButtonIdleState = RegButton->ButtonIdleState;

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_RCC = GPIO2RCC(RegButton->ButtonGPIO);
	RCC_APB2PeriphClockCmd(GPIO_RCC, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct.GPIO_Pin = RegButton->ButtonPin;
	GPIO_Init(RegButton->ButtonGPIO, &GPIO_InitStruct);

	return 0;
}

uint8_t MyButton_UnReg(uint8_t RegButtonIndex)
{
	if(myButton_ButtonList[RegButtonIndex].CallBackFunc == NULL)
		return (uint8_t)-3;

	myButton_ButtonList[RegButtonIndex].CallBackFunc = 0;
	return 0;
}






