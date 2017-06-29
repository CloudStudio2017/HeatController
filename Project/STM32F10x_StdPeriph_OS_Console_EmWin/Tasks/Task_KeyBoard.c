#include "stm32f10x.h"
#include "Task_KeyBoard.h"
#include "myButton.h"
#include "myLed.h"
#include "myBeep.h"


static uint32_t Is_Init=0;

static void KBCB(uint8_t BtnHandle, uint8_t BtnState)
{
	volatile static uint32_t trig = 0;
	
	if(BtnState == BUTTON_STATUS_RELEASE)
	{
		myLed_On(BtnHandle);
	}
	
	switch(BtnHandle)
	{
		case 0:
			if(BtnState == BUTTON_STATUS_RELEASE)
			{
				trig++;
			}
			break;
		case 1:
			if(BtnState == BUTTON_STATUS_PRESS)
			{
				MyBeep_Beep(1);
			}
			if(BtnState == BUTTON_STATUS_RELEASE)
			{
				trig=0;
				MyBeep_Beep(0);
			}
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		default:
			break;
	}
}

void KeyBoard_Regs(void)
{
	MyButton_RegType btn;
	
	btn.CallBackFunc = KBCB;
	btn.ButtonIdleState = SET;
	
	btn.ButtonGPIO = GPIOB;
	btn.ButtonPin = GPIO_Pin_11;
	MyButton_Reg(0, &btn);
	
	btn.ButtonGPIO = GPIOB;
	btn.ButtonPin = GPIO_Pin_10;
	MyButton_Reg(1, &btn);
	
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_5;
	MyButton_Reg(2, &btn);
	
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_4;
	MyButton_Reg(3, &btn);
	
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_3;
	MyButton_Reg(4, &btn);
	
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_2;
	MyButton_Reg(5, &btn);
	
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_1;
	MyButton_Reg(6, &btn);
	
	btn.ButtonGPIO = GPIOC;
	btn.ButtonPin = GPIO_Pin_0;
	MyButton_Reg(7, &btn);
}

void vTask_KeyBoard( void *pvParameters )
{
	MyButton_Init();
	KeyBoard_Regs();
	
	MyBeep_Init();
	
	Is_Init = KEYBOARD_INIT_DONE;
	xQueueSendToBack(InitQueue, &Is_Init, 0);
	
	while(1)
	{
		MyButton_Process();
		vTaskDelay(50);
	}
}
