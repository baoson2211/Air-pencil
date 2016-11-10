/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "AHRS.h"

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
extern imu imudata;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int LED_Initialize(void);
void DelayMs(__IO uint32_t nTime);

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

  /* LED Initialize */
  if(LED_Initialize()) {
    while(1);
  }
  USART_SendText(USART1, "LED Initialize done\n\r");

  /* Gyro calibrate */
  if(GyroCalibrate(I2C2, GYRO_CAL_N_SAMPLE)) {
    while(1);
  }

  __IO char res;
  StartTimeoutUs(5000000);
  USART_SendText(USART1, "Are you wanna calibrate your accelerometer? (Y/n). Timeout in 5 seconds ...");
  while(!IsReachTimeout()) {
    //if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
      res = (char) USART_ReceiveData(USART1);
  }
  USART_SendText(USART1, "\n\r");

  if(res == 'Y' || res == 'y' || res == 0x20 || res == 0x10 || res == 0x13) {
    /* Accel calibrate */
    if(AccelCalibrate(I2C2)) {
      while(1);
    }
  } else {
    USART_SendText(USART1, "Accelerometer is NOT calibrated!\n\r");
  }

  USART_SendText(USART1, "Press any key to start... \n\r");
  USART_ReceiveData(USART1);
  while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

  while (1)
  {
    uint8_t regs[6];
    tick = micros();
    GPIOC->ODR ^= 0x0A;
    tick = micros()- tick;
    DelayUs(10000);
    for(int i = 0 ; i < 500000; i++);
//    sprintf(str,"gyro:  %d  %d  %d\n\r", get_RawAccel_X(I2C2),
//        get_RawAccel_Y(I2C2),
//        get_RawAccel_Z(I2C2));
//    USART_SendText(USART1, str);

    ITG3200_burst_read(I2C2, ITG3200_GYRO_XOUT_H,6,regs);
    sprintf(str,"gyro:  %f  %f  %f\n\r", get_Gyro_X(I2C2),
        get_Gyro_Y(I2C2),
        get_Gyro_Z(I2C2));
    USART_SendText(USART1, str);

    ADXL345_burst_read(I2C2, ADXL345_DATA_X0, 6,regs);
    sprintf(str,"accel: %f  %f  %f\n\r", get_Accel_X(I2C2),
        get_Accel_Y(I2C2),
        get_Accel_Z(I2C2));
    USART_SendText(USART1, str);

//    HMC5883L_burst_read(I2C2, HMC5883L_MAG_XOUT_H, 6,regs);
//    sprintf(str,"mag:   %x - %x - %x\n\r", (uint16_t) (regs[1]<<8 | regs[0]),
//        (uint16_t) (regs[5]<<8 | regs[4]),
//        (uint16_t) (regs[3]<<8 | regs[2]));
//    USART_SendText(USART1, str);
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
  * @brief  Delay in microsecond.
  * @param  None
  * @retval None
  */
void DelayMs(__IO uint32_t nTime)
{
  while (nTime--)
  DelayUs(1000);
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
