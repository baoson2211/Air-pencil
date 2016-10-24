/* Includes ------------------------------------------------------------------*/
#include "main.h"

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
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  uint32_t tick;
  char str[50];

  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */
  /* USART1 Configuration */
  USART_Configuration();

  /* I2C2 Configuration */
  I2C_Configration(I2C2, I2C_FAST_SPEED);
  USART_SendText(USART1, "I2C config done\n\r");

  /* ADXL345 Initialize */
  if (ADXL345_Initialize(I2C2)) {
    while(1);
  }
  USART_SendText(USART1, "ADXL345 Initialize done\n\r");
  //sprintf(str, "Data format: 0x%x\n\r", (( ADXL345_FULL_RES | ADXL345_RANGE(ADXL345_RANGE_PM_16G) ) & 0xFF ));
  //USART_SendText(USART1, str);
  //sprintf(str, "Bandwidth rate: 0x%x\n\r", ( ADXL345_RATE(0x0C) & 0xFF ));
  //USART_SendText(USART1, str);
  //sprintf(str, "Power control: 0x%x\n\r", ( ADXL345_PCTL_MEASURE & 0xFF ));
  //USART_SendText(USART1, str);
  //sprintf(str, "Interrupt: 0x%x\n\r", (ADXL345_DATA_READY & 0xFF ));
  //USART_SendText(USART1, str);

  /* ITG3200 Initialize */
  if (ITG3200_Initialize(I2C2)) {
    while(1);
  }
  USART_SendText(USART1, "ITG3200 Initialize done\n\r");

  /* GPIOC Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* Configure PC1 and PC3 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  SystemInit();
  if (SysTick_Config(SystemCoreClock / 1000000))
  {
    /* Capture error */
    while (1);
  }
  USART_SendText(USART1, "SysTick config done\n\r");

  /* Test math.h library */
  //tick = micros();
  //double z = atan2(7.0,3.0);
  //tick = micros()- tick;
  //sprintf(str,"%ldus: %.10f\n\r", tick, z);
  //USART_SendText(USART1, str);

  //while (1)
  //{
    tick = micros();
    //ITG3200_single_read(I2C2, ITG3200_WHO_AM_I);
    uint8_t data;
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
    USART_SendText(USART1, "1\n\r");

    I2C_GenerateSTART(I2C2, ENABLE);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    USART_SendText(USART1, "2\n\r");

    I2C_Send7bitAddress(I2C2, ITG3200_ADDR_DEFAUT, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    USART_SendText(USART1, "3\n\r");

    I2C_SendData(I2C2, ITG3200_WHO_AM_I);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    USART_SendText(USART1, "4\n\r");

    I2C_GenerateSTART(I2C2, ENABLE);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
    USART_SendText(USART1, "5\n\r");

    I2C_Send7bitAddress(I2C2, ITG3200_ADDR_DEFAUT, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED));
    USART_SendText(USART1, "6\n\r");

    data = I2C_ReceiveData(I2C2);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED));
    USART_SendText(USART1, "7\n\r");

    I2C_AcknowledgeConfig(I2C2, DISABLE);
    USART_SendText(USART1, "8\n\r");

    I2C_GenerateSTOP(I2C2, ENABLE);
    while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
    USART_SendText(USART1, "9\n\r");

    //uint16_t x_axis = get_RawAccel_X(I2C2);
    //uint16_t y_axis = get_RawAccel_Y(I2C2);
    //uint16_t z_axis = get_RawAccel_Z(I2C2);
    //float Xg = get_Accel_X(I2C2);
    //float Yg = get_Accel_Y(I2C2);
    //float Zg = get_Accel_Z(I2C2);
    //tick = micros()- tick;
    //GPIOC->ODR ^= 0x0A;
    //DelayUs(1000000);
    //for(int i = 0 ; i < 500000; i++);

    //sprintf(str,"%ldus %x - %x - %x\n\r", tick, x_axis, y_axis, z_axis);
    //sprintf(str,"%ldus %.3f  %.3f  %.3f\n\r", tick, Xg, Yg, Zg);
    //USART_SendText(USART1, str);
  //}
}

/**
  * @brief  Delay in microsecond.
  * @param  None
  * @retval None
  */
void DelayUs(__IO uint32_t nTime)
{
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

/**
  * @brief  micros
  * @param  None
  * @retval no. of microseconds is gone
  */
__IO uint32_t micros(void)
{
  return Tick;
}

/**
  * @brief  millis
  * @param  None
  * @retval no. of milliseconds is gone
  */
__IO uint32_t millis(void)
{
  return (Tick / 1000);
}

/**
  * @brief  init/start timeout
  * @param  timeout interval
  * @retval None
  */
void StartTimeoutUs(__IO uint32_t nTime)
{
  TimeoutUs = nTime;
}

/**
  * @brief  timeout ended?
  * @param  None
  * @retval 0 (no) or 1 (yes)
  */
int IsReachTimeout(void)
{
  return (TimeoutUs == 0);
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

/*********************************END OF FILE**********************************/
