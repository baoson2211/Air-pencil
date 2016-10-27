/* Includes ------------------------------------------------------------------*/
#include "HMC5883L.h"

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
  * @brief  HMC5883L Initialize
  * @param  I2C interface you wanna use
  * @retval 0 for done or other for not
  */
int HMC5883L_Initialize(I2C_TypeDef* I2Cx) {
  /* Normal measurment config, Data Output Rate = 15 Hz,
   * 4 samples averaged per measurement output
   */
  I2C_single_write(I2Cx, HMC5883L_ADDR_DEFAUT, HMC5883L_CONF_REG_A,
      ( HMC5883L_REG_A_MA(2) | HMC5883L_REG_A_DO(4) | HMC5883L_REG_A_MS(0) ));
  /* Gain = 1090 LSb/Gauss, Sensor Field Range = ± 1.3 Ga */
  I2C_single_write(I2Cx, HMC5883L_ADDR_DEFAUT, HMC5883L_CONF_REG_B, HMC5883L_REG_B_GA(1));
  /* Continuous-Measurement Mode, disable High Speed I2C */
  I2C_single_write(I2Cx, HMC5883L_ADDR_DEFAUT, HMC5883L_MODE_REG, ZERO);
  return 0;
}

/**
  * @brief  write only one byte to an HMC5883L register
  * @param  I2C interface you wanna use, register address is written and one byte data
  * @retval None
  */
void HMC5883L_single_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t data) {
  I2C_single_write(I2Cx, HMC5883L_ADDR_DEFAUT, REG_addr, data);
}

/**
  * @brief  read only one byte from an HMC5883L register
  * @param  I2C interface you wanna use, register address is read
  * @retval one byte data
  */
uint8_t HMC5883L_single_read(I2C_TypeDef* I2Cx, uint8_t REG_addr) {
  return I2C_single_read(I2Cx, HMC5883L_ADDR_DEFAUT, REG_addr);
}

/**
  * @brief  write multi byte to HMC5883L registers
  * @param  I2C interface you wanna use, first register address is written,
  *         no. of byte is written, and a data array
  * @retval None
  */
void HMC5883L_burst_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data) {
  I2C_burst_write(I2Cx, HMC5883L_ADDR_DEFAUT, REG_addr, n_data, data);
}

/**
  * @brief  read multi byte from HMC5883L registers
  * @param  I2C interface you wanna use, first register address is read,
  *         no. of byte is read, and an array is used to store data
  * @retval None
  */
void HMC5883L_burst_read(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data) {
  I2C_burst_read(I2Cx, HMC5883L_ADDR_DEFAUT, REG_addr, n_data, data);
}

/**
  * @brief  get raw data of X axis
  * @param  I2C interface you wanna use
  * @retval one word data
  */
int16_t get_RawMag_X(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, HMC5883L_ADDR_DEFAUT, HMC5883L_MAG_XOUT_H, 2, data);

  int16_t temp = (int16_t) ( (data[0] << 8) | data[1] );
  return temp;
}

/**
  * @brief  get raw data of Y axis
  * @param  I2C interface you wanna use
  * @retval one word data
  */
int16_t get_RawMag_Y(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, HMC5883L_ADDR_DEFAUT, HMC5883L_MAG_YOUT_H, 2, data);

  int16_t temp = (int16_t) ( (data[0] << 8) | data[1] );
  return temp;
}

/**
  * @brief  get raw data of Z axis
  * @param  I2C interface you wanna use
  * @retval one word data
  */
int16_t get_RawMag_Z(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, HMC5883L_READ, HMC5883L_MAG_ZOUT_H, 2, data);

  int16_t temp = (int16_t) ( (data[0] << 8) | data[1] );
  return temp;
}

/**
  * @brief  get angular velocity around X axis
  * @param  I2C interface you wanna use
  * @retval g-force along X axis (in g unit)
  */
float get_Mag_X(I2C_TypeDef* I2Cx) {
  return 0;
}

/**
  * @brief  get angular velocity around Y axis
  * @param  I2C interface you wanna use
  * @retval g-force on Y axis (in g unit)
  */
float get_Mag_Y(I2C_TypeDef* I2Cx) {
  return 0;
}

/**
  * @brief  get angular velocity around Z axis
  * @param  I2C interface you wanna use
  * @retval g-force on Z axis (in g unit)
  */
float get_Mag_Z(I2C_TypeDef* I2Cx) {
  return 0;
}


/******************************* END OF FILE **********************************/
