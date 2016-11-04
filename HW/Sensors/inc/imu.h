/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IMU_H
#define __IMU_H

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include "bit.h"
/* Exported types ------------------------------------------------------------*/
typedef struct __imu {
  __IO float accel[3];
  __IO float gyro[3];

  __IO int16_t accel_offset[3];
  __IO int16_t gyro_offset[3];

  __IO uint8_t accel_gain[3];
  __IO uint8_t gyro_gain[3];
} imu;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
imu imudata;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif /* __IMU_H */
