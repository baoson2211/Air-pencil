/* Includes ------------------------------------------------------------------*/
#include "ADXL345.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const float alpha = 0.5;
float fXg = 0;
float fYg = 0;
float fZg = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  ADXL345 Initialize
  * @param  I2C interface you wanna use
  * @retval 0 for done or other for not
  */
int ADXL345_Initialize(I2C_TypeDef* I2Cx) {
  memset(imudata.accel_gain, 1, sizeof(imudata.accel_gain) / sizeof(imudata.accel_gain[0]));
  /* range ±16g (13 bit raw data) and full resolution */
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_FORMAT, (( ADXL345_FULL_RES | ADXL345_RANGE(ADXL345_RANGE_PM_16G) ) & 0x0B) );
  /* bandwitdh and output rate - see more Table 7 in datasheet rev. D */
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_BW_RATE, (ADXL345_RATE(0x0C) & 0xFF) );
  /* measuarment mode */
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_POWER_CTL, (ADXL345_PCTL_MEASURE & 0x08) );
  /* only DATA_READY */
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_INT_ENABLE, (ADXL345_DATA_READY & 0x80) );
  /* 3 axis offset */
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_OFSX, ZERO );
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_OFSY, ZERO );
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_OFSZ, ZERO );
  /* FIFO is not used */
  return 0;
}

/**
  * @brief  write only one byte to an ADXL345 register
  * @param  I2C interface you wanna use, register address is written and one byte data
  * @retval None
  */
void ADXL345_single_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t data) {
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, REG_addr, data);
}

/**
  * @brief  read only one byte from an ADXL345 register
  * @param  I2C interface you wanna use, register address is read
  * @retval one byte data
  */
__IO uint8_t ADXL345_single_read(I2C_TypeDef* I2Cx, uint8_t REG_addr) {
  return I2C_single_read(I2Cx, ADXL345_ADDR_DEFAUT, REG_addr);
}

/**
  * @brief  write multi byte to ADXL345 registers
  * @param  I2C interface you wanna use, first register address is written,
  *         no. of byte is written, and a data array
  * @retval None
  */
void ADXL345_burst_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data) {
  I2C_burst_write(I2Cx, ADXL345_ADDR_DEFAUT, REG_addr, n_data, data);
}

/**
  * @brief  read multi byte from ADXL345 registers
  * @param  I2C interface you wanna use, first register address is read,
  *         no. of byte is read, and an array is used to store data
  * @retval None
  */
void ADXL345_burst_read(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data) {
  I2C_burst_read(I2Cx, ADXL345_ADDR_DEFAUT, REG_addr, n_data, data);
}

/**
  * @brief  get raw data of X axis
  * @param  I2C interface you wanna use
  * @retval one word data
  */
__IO int16_t get_RawAccel_X(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_X0, 2, data);

  int16_t temp = (int16_t) ( (data[1] << 8) | data[0] );
  return temp;
}

/**
  * @brief  get raw data of Y axis
  * @param  I2C interface you wanna use
  * @retval one word data
  */
__IO int16_t get_RawAccel_Y(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_Y0, 2, data);

  int16_t temp = (int16_t) ( (data[1] << 8) | data[0] );
  return temp;
}

/**
  * @brief  get raw data of Z axis
  * @param  I2C interface you wanna use
  * @retval one word data
  */
__IO int16_t get_RawAccel_Z(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_Z0, 2, data);

  int16_t temp = (int16_t) ( (data[1] << 8) | data[0] );
  return temp;
}

/* Value in G = Measurement Value * (G-range/(2^Resolution))
 * Range ± 2g (=  4g) - Resolution: 10 bits
 * Range ± 4g (=  8g) - Resolution: 11 bits
 * Range ± 8g (= 16g) - Resolution: 12 bits
 * Range ±16g (= 32g) - Resolution: 13 bits
 * E.g: Range ±16g
 *   => Value in G = [Signed] Measurement Value * (32 / (2^13))
 */
/* Without low pass filter */
/**
  * @brief  get g-force along X axis
  * @param  I2C interface you wanna use
  * @retval g-force along X axis (in g unit)
  */
__IO float get_Accel_X(I2C_TypeDef* I2Cx) {
  return (float) ( (get_RawAccel_X(I2Cx) - imudata.accel_offset[0]) * 0.0039 / imudata.accel_gain[0]);
}

/**
  * @brief  get g-force along Y axis
  * @param  I2C interface you wanna use
  * @retval g-force on Y axis (in g unit)
  */
__IO float get_Accel_Y(I2C_TypeDef* I2Cx) {
  return (float) ( (get_RawAccel_Y(I2Cx) - imudata.accel_offset[1]) * 0.0039 / imudata.accel_gain[1]);
}

/**
  * @brief  get g-force along Z axis
  * @param  I2C interface you wanna use
  * @retval g-force on Z axis (in g unit)
  */
__IO float get_Accel_Z(I2C_TypeDef* I2Cx) {
  return (float) ( (get_RawAccel_Z(I2Cx) - imudata.accel_offset[2]) * 0.0039 / imudata.accel_gain[2]);
}

/* With low pass filter */
//float get_Accel_X(I2C_TypeDef* I2Cx) {
//  fXg = (float) ( (( get_RawAccel_X(I2Cx) * 0.0039 ) * alpha ) + fXg * (1.0 - alpha) );
//  return fXg;
//}
//
//float get_Accel_Y(I2C_TypeDef* I2Cx) {
//  fYg = (float) ( (( get_RawAccel_Y(I2Cx) * 0.0039 ) * alpha ) + fYg * (1.0 - alpha) );
//  return fYg;
//}
//
//float get_Accel_Z(I2C_TypeDef* I2Cx) {
//  fZg = (float) ( (( get_RawAccel_Z(I2Cx) * 0.0039 ) * alpha ) + fZg * (1.0 - alpha) );
//  return fZg;
//}

/**
  * @brief  Accelerometer calibration
  * @param  I2C interface you wanna use, number of samples
  * @retval 0 for done or other for not
  */
int AccelCalibrate(I2C_TypeDef* I2Cx) {
  char str[50];
  int16_t AccelMinX = 0;
  int16_t AccelMaxX = 0;
  int16_t AccelMinY = 0;
  int16_t AccelMaxY = 0;
  int16_t AccelMinZ = 0;
  int16_t AccelMaxZ = 0;

  imudata.accel_offset[0] = 0;
  imudata.accel_offset[1] = 0;
  imudata.accel_offset[2] = 0;

  imudata.accel_gain[0] = 1;
  imudata.accel_gain[1] = 1;
  imudata.accel_gain[2] = 1;

  DelayMs(1000);
  USART_SendText(USART1, "Start Accelerometer Calibrate\n\r");
  DelayMs(20);

  for(uint16_t i = 6; i > 0; i--) {
    switch (i) {
      case 6:
        USART_SendText(USART1, "stay upward\n\r");
        break;
      case 5:
        USART_SendText(USART1, "turn left\n\r");
        break;
      case 4:
        USART_SendText(USART1, "turn right\n\r");
        break;
      case 3:
        USART_SendText(USART1, "nose down\n\r");
        break;
      case 2:
        USART_SendText(USART1, "nose up\n\r");
        break;
      case 1:
        USART_SendText(USART1, "turn back\n\r");
        break;
      default:
        break;
    }

    USART_SendText(USART1, "Press any key when ready... \n\r");
    USART_ReceiveData(USART1);
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

    imudata.accel[0] = get_RawAccel_X(I2Cx);
    imudata.accel[1] = get_RawAccel_Y(I2Cx);
    imudata.accel[2] = get_RawAccel_Z(I2Cx);

    AccelMinX = imudata.accel[0] < AccelMinX ? imudata.accel[0] : AccelMinX;
    AccelMaxX = imudata.accel[0] > AccelMaxX ? imudata.accel[0] : AccelMaxX;

    AccelMinY = imudata.accel[1] < AccelMinY ? imudata.accel[1] : AccelMinY;
    AccelMaxY = imudata.accel[1] > AccelMaxY ? imudata.accel[1] : AccelMaxY;

    AccelMinZ = imudata.accel[2] < AccelMinZ ? imudata.accel[2] : AccelMinZ;
    AccelMaxZ = imudata.accel[2] > AccelMaxZ ? imudata.accel[2] : AccelMaxZ;
  }
  /* The offset values and gain factors are calculated with the following equations as stated
   * in the Application Note from Analog Devices (page 8: equations 17 and 18):
   * http://www.analog.com/media/en/technical-documentation/application-notes/AN-1057.pdf
   */
  imudata.accel_offset[0] = (AccelMaxX + AccelMinX) / 2;
  imudata.accel_offset[1] = (AccelMaxY + AccelMinY) / 2;
  imudata.accel_offset[2] = (AccelMaxZ + AccelMinZ) / 2;

  sprintf(str, "DONE!!\n\rAccel Offset x: %d   y: %d   z: %d\n\r", imudata.accel_offset[0],
        imudata.accel_offset[1], imudata.accel_offset[2]);
  USART_SendText(USART1, str);

  imudata.accel_gain[0] = (AccelMaxX - AccelMinX) / (2.00 * 256) + 0.5;
  imudata.accel_gain[1] = (AccelMaxY - AccelMinY) / (2.00 * 256) + 0.5;
  imudata.accel_gain[2] = (AccelMaxZ - AccelMinZ) / (2.00 * 256) + 0.5;

  sprintf(str, "Accel Gain x: %d   y: %d   z: %d\n\r", imudata.accel_gain[0],
        imudata.accel_gain[1], imudata.accel_gain[2]);
  USART_SendText(USART1, str);

  DelayMs(3000);

  return 0;
}

/******************************* END OF FILE **********************************/
