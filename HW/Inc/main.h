/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "usart.h"
#include "i2c.h"
#include "ADXL345.h"
#include "ITG3200.h"

__IO uint32_t TimingDelay;
__IO uint32_t Tick;
__IO uint32_t TimeoutUs;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void DelayUs(__IO uint32_t nTime);
__IO uint32_t micros(void);
__IO uint32_t millis(void);
void StartTimeoutUs(__IO uint32_t nTime);
int IsReachTimeout(void);

#endif /* __MAIN_H */
