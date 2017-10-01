#ifndef __MY_BUTTON_H__
#define __MY_BUTTON_H__

#include "stm32f10x.h"
#include "cslCommon.h"


#define BUTTON0 0
#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3
#define BUTTON4 4
#define BUTTON5 5
#define BUTTON6 6
#define BUTTON7 7

/* MYBUTTON_MAX_COUNT can be modified by user */
#define MYBUTTON_MAX_COUNT  8




#define MYBUTTON_ST_COUNT   ((MYBUTTON_MAX_COUNT - 1) / 8 + 1)

#define BUTTON_STATUS_BIT                   (3)
#define BUTTON_STATUS_BIT_COUNT             (24 / BUTTON_STATUS_BIT)

#define BUTTON_STATUS_FREE                  (0x00)
#define BUTTON_STATUS_PRESS                 (0x01)
#define BUTTON_STATUS_DOWN                  (0x02)
#define BUTTON_STATUS_RELEASE               (0x03)
#define BUTTON_STATUS_HOLD                  (0x04)
#define BUTTON_STATUS_MASK                  ((1 << BUTTON_STATUS_BIT) - 1)

#define BUTTON_STATUS_MASK_(Button_Index)   (BUTTON_STATUS_MASK << (Button_Index * BUTTON_STATUS_BIT))

#define BUTTON_FREE_(Button_Index)          (BUTTON_STATUS_FREE    << (Button_Index * BUTTON_STATUS_BIT))
#define BUTTON_PRESS_(Button_Index)         (BUTTON_STATUS_PRESS   << (Button_Index * BUTTON_STATUS_BIT))
#define BUTTON_DOWN_(Button_Index)          (BUTTON_STATUS_DOWN    << (Button_Index * BUTTON_STATUS_BIT))
#define BUTTON_RELEASE_(Button_Index)       (BUTTON_STATUS_RELEASE << (Button_Index * BUTTON_STATUS_BIT))
#define BUTTON_HOLD_(Button_Index)          (BUTTON_STATUS_HOLD    << (Button_Index * BUTTON_STATUS_BIT))



typedef enum
{
	Button_NoEvent = -1,
	Button_Down = 0,
	Button_Up,
	Button_Click,
	Button_Hold,
}MyButton_Events;

typedef void (*MyButton_CBType)(uint8_t BtnHandle, uint8_t BtnState);
typedef struct MyButton_RegType
{
	GPIO_TypeDef*   ButtonGPIO;       //Key phy GPIO GPIOA-GPIOK
	uint16_t        ButtonPin;        //Key phy Pin  0-15
	uint8_t         ButtonIdleState;  //Idle state level 0:low level  1:high level
	uint8_t         ButtonTrigMask;   //Mask of
	MyButton_CBType CallBackFunc;     //Call back function
}MyButton_RegType;


extern void MyButton_UpdateStatus(void);
extern uint8_t MyButton_Init(void);
extern uint8_t MyButton_Reg(uint8_t RegButtonIndex, MyButton_RegType* RegButton);
extern uint8_t MyButton_UnReg(uint8_t RegButtonIndex);
extern void MyButton_Process(void);


#endif
