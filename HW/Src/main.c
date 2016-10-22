/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body.
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
#include "stm32f10x_it.h"
#include "stm32f10x_conf.h"

/* Scheduler includes --------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "list.h"

/* Sensors includes --------------------------------------------------------*/
#include "ADXL345.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TaskHandle_t T1_handle;
TaskHandle_t T2_handle;
TaskHandle_t T3_handle;
const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

/* Private function prototypes -----------------------------------------------*/
void GPIO_Configuration(void);
static void prvSetupHardware( void );
static void Led1(void *pvParameters);
static void Led2(void *pvParameters);
static void Led3(void *pvParameters);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */

  /* To achieve GPIO toggling maximum frequency, the following  sequence is mandatory.
     You can monitor PC1 or PC3 or PC13 on the scope to measure the output signal.
     If you need to fine tune this frequency, you can add more GPIO set/reset
     cycles to minimize more the infinite loop timing.
     This code needs to be compiled with high speed optimization option.  */

  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );  //Needed for STM32F10x
  GPIO_Configuration();

  xTaskCreate( Led1, "Task1", 128, NULL, 3, &T1_handle);
  xTaskCreate( Led2, "Task2", 128, NULL, 2, &T2_handle);
  xTaskCreate( Led3, "Task3", 128, NULL, 1, &T3_handle);
  vTaskStartScheduler();
}

static void prvSetupHardware( void )
{
  SystemInit();
  /* Configure HCLK clock as SysTick clock source. */
  SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK );
}

void GPIO_Configuration(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  /* GPIOC Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* Configure PC1, PC3 and PC13 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Configure SysTick Timer */
  if (SysTick_Config(SystemCoreClock / 1000))
    while (1);
}

static void Led1(void *pvParameters) // This is Task1
{
  while(1){
    // toggle led
    GPIOC->ODR ^= 0x02;
    vTaskDelay(2000);
  }
}


static void Led2(void *pvParameters)
{
  while(1){
    // toggle led
    GPIOC->ODR ^= 0x08;
    vTaskDelay(1000);
  }
}

static void Led3(void *pvParameters)
{
  while(1){
    // toggle led
    GPIOC->ODR ^= 0x2000;
    vTaskDelay(5000);
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

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
