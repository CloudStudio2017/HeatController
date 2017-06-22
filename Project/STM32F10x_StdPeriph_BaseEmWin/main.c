/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "cslLCD.h"
#include "GUI.h"
#include "stdlib.h"
#include "dialog.h"

extern WM_HWIN CreateFramewin(void);;

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	volatile uint32_t i = 0;
	volatile uint16_t xx[40];
	
  /* Add your application code here
     */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
  /* Infinite loop */
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick_Config(72000);
	GUI_Init();
	
	GUI_EnableAlpha(0);
	
	GUI_SetBkColor(1 << 24 | GUI_RED);
	GUI_SetColor(1 << 24 | GUI_GREEN);
	GUI_Clear();
	
	GUI_SetFont(GUI_FONT_COMIC24B_1);
	
	GUI_FillRect(10,100, 100, 200);
	GUI_SetColor(1 << 24 | GUI_BLUE);
	GUI_FillRect(40,140, 140, 240);
	GUI_DispStringAt("Hello", 20, 120);
	//GUI_SetFont(&GUI_Fontword1);
	//GUI_DispStringAt("");
	GUI_UC_SetEncodeUTF8();
	srand(100);
	//GUI_Clear();
	//uint32_t tx,ty;
	//tx = 100;
	//ty = 100;
	WM_HWIN aa;
	aa = CreateFramewin();
	WM_SetFocus(aa);
  while (1)
  {
		GUI_Delay(10);
		//tx += rand() % 3 -1;
		//ty += rand() % 3 -1;
		//GUI_DispStringAt("Hello", tx, ty);
		//i++;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
