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
#include "FreeRTOS.h"
#include "task.h"
#include "CslPrintf.h"
#include "CslScanf.h"
#include "CslRTC.h"
#include "Task_Console.h"
#include "Task_UI.h"
#include "Task_Control.h"
#include "Task_KeyBoard.h"
#include "Task_Common.h"

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
  /* Add your application code here
     */
	//CslRTC_Init();
	
	InitQueue = xQueueCreate( 5, sizeof(uint32_t));
	FlashQueue = xQueueCreate( 4, sizeof(uint32_t));
	
	xTaskCreate(vTask_Console, "Task_Console", 1024, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vTask_UI, "Task_UI", 1024, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vTask_Control, "Task_Control", 1024, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vTask_KeyBoard, "Task_KeyBoard", 256, NULL, tskIDLE_PRIORITY, NULL);

	vTaskStartScheduler();
  /* Infinite loop */
  while (1)
  {
		i++;
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
