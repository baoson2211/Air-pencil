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
int LED_Initialize(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t tick;
  char str[50];

  SystemInit();
  if (SysTick_Config(SystemCoreClock / 1000000))
  {
    /* Capture error */
    while (1);
  }

  /* USART1 Configuration */
  USART_Configuration();

  /* I2C2 Configuration */
  I2C_Configration(I2C2, I2C_FAST_SPEED);
  //for(int i = 0 ; i < 500000; i++);
  USART_SendText(USART1, "I2C config done\n\r");

  /* ADXL345 Initialize */
  if (ADXL345_Initialize(I2C2)) {
    while(1);
  }
  USART_SendText(USART1, "ADXL345 Initialize done\n\r");

  /* ITG3200 Initialize */
  if (ITG3200_Initialize(I2C2)) {
    while(1);
  }
  USART_SendText(USART1, "ITG3200 Initialize done\n\r");

  /* HMC5883L Initialize */
  if(HMC5883L_Initialize(I2C2)) {
    while(1);
  }
  USART_SendText(USART1, "HMC5883L Initialize done\n\r");

  if(LED_Initialize()) {
    while(1);
  }
  USART_SendText(USART1, "LED Initialize done\n\r");

  while (1)
  {
    uint8_t regs[6];
    tick = micros();
    GPIOC->ODR ^= 0x0A;
    tick = micros()- tick;
    //DelayUs(100000);
    for(int i = 0 ; i < 500000; i++);

    ITG3200_burst_read(I2C2, ITG3200_GYRO_XOUT_H,6,regs);
    sprintf(str,"gyro:  %x - %x - %x\n\r", (uint16_t) (regs[0]<<8 | regs[1]),
        (uint16_t) (regs[2]<<8 | regs[3]),
        (uint16_t) (regs[4]<<8 | regs[5]));
    USART_SendText(USART1, str);

    ADXL345_burst_read(I2C2, ADXL345_DATA_X0, 6,regs);
    sprintf(str,"accel: %x - %x - %x\n\r", (uint16_t) (regs[1]<<8 | regs[0]),
        (uint16_t) (regs[3]<<8 | regs[2]),
        (uint16_t) (regs[5]<<8 | regs[4]));
    USART_SendText(USART1, str);

    HMC5883L_burst_read(I2C2, HMC5883L_MAG_XOUT_H, 6,regs);
    sprintf(str,"mag:   %x - %x - %x\n\r", (uint16_t) (regs[1]<<8 | regs[0]),
        (uint16_t) (regs[5]<<8 | regs[4]),
        (uint16_t) (regs[3]<<8 | regs[2]));
    USART_SendText(USART1, str);
  }
}

/**
  * @brief  LED Initialize.
  * @param  None
  * @retval 0 for done or other for not
  */
int LED_Initialize(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* GPIOC Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* Configure PC1 and PC3 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIOC->ODR |= 0x08;
  return 0;
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
