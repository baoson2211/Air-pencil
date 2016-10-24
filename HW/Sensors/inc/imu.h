/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IMU_H
#define __IMU_H

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include "bit.h"
/* Exported types ------------------------------------------------------------*/
typedef struct __imu {
  __IO uint8_t *accel_buff;
  __IO uint16_t accel_x;
  __IO uint16_t accel_y;
  __IO uint16_t accel_z;

  __IO uint8_t *gyro_buff;
  __IO uint16_t gyro_x;
  __IO uint16_t gyro_y;
  __IO uint16_t gyro_z;
} imu;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif /* __IMU_H */
