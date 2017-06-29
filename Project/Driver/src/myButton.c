#include "myButton.h"


enum
{
	Button_NoEvent = -1,
	Button_Down = 0,
	Button_Up,
	Button_Click,
	Button_LongClick,
}MyButton_Events;


static uint32_t Button_Status = 0;

#define MYBUTTON_SUPPORT_MAX  8
static MyButton_RegType myButton_ButtonList[MYBUTTON_SUPPORT_MAX]={0};


void MyButton_Init(void)
{
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
  uint8_t i;
  
  for(i=0;i<MYBUTTON_SUPPORT_MAX;i++)
  {
		if(myButton_ButtonList[i].CallBackFunc == 0)
			continue;
    if(ButtonIsUp(i))
    {
      switch((Button_Status >> (i <<1)) & BUTTON_STATUS_MASK)
      {
      //case BUTTONFREE :
      //  break;
      case BUTTON_STATUS_PRESS:
        Button_Status &= ~BUTTON_STATUS_MASK_(i);
        Button_Status |= BUTTON_FREE_(i);
        break;
      case BUTTON_STATUS_DOWN:
        Button_Status &= ~BUTTON_STATUS_MASK_(i);
        Button_Status |= BUTTON_RELEASE_(i);
        break;
      case BUTTON_STATUS_RELEASE:
        Button_Status &= ~BUTTON_STATUS_MASK_(i);
        Button_Status |= BUTTON_FREE_(i);
        break;
      }
    }
    else
    {
      switch((Button_Status >> (i <<1)) & BUTTON_STATUS_MASK)
      {
      case BUTTON_STATUS_FREE:
        Button_Status &= ~BUTTON_STATUS_MASK_(i);
        Button_Status |= BUTTON_PRESS_(i);
        break;
      case BUTTON_STATUS_PRESS:
        Button_Status &= ~BUTTON_STATUS_MASK_(i);
        Button_Status |= BUTTON_DOWN_(i);
        break;
      //case BUTTONDOWN:
      //  break;
      case BUTTON_STATUS_RELEASE:
        Button_Status &= ~BUTTON_STATUS_MASK_(i);
        Button_Status |= BUTTON_FREE_(i);
        break;
      }
    }
  }
}

void MyButton_Process(void)
{
	uint8_t i;
	static uint32_t TrigCount=0;

  MyButton_UpdateStatus();
  
	for(i=0;i<MYBUTTON_SUPPORT_MAX; i++)
	{
		if(myButton_ButtonList[i].CallBackFunc == NULL)
			continue;

		if(BUTTON_EVENT_PRESS_(i))
		{
			myButton_ButtonList[i].CallBackFunc(i, BUTTON_STATUS_PRESS);
		}
		if(BUTTON_EVENT_RELEASE_(i))
		{
			myButton_ButtonList[i].CallBackFunc(i, BUTTON_STATUS_RELEASE);
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






