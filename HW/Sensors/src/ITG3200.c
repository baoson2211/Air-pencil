/* Includes ------------------------------------------------------------------*/
#include "ITG3200.h"

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
  * @brief  ITG3200 Initialize
  * @param  I2C interface you wanna use
  * @retval 0 for done or other for not
  */
int ITG3200_Initialize(I2C_TypeDef* I2Cx) {
  /* Factory reset */
  I2C_single_write(I2Cx, ITG3200_ADDR_DEFAUT, ITG3200_PWR_MGM, ITG3200_PWR_MGM_H_RESET);
  /* Full scale and F_internal = 8kHz, LPF Bandwidth = 256Hz */
  I2C_single_write(I2Cx, ITG3200_ADDR_DEFAUT, ITG3200_DLPF_FS, ( ITG3200_DLPF_FS_SEL(3) | ITG3200_DLPF_CFG(0) ));
  /* Divider as 19
   * F_sample = F_internal / (divider + 1) = 8000 / (19 + 1) = 400Hz
   */
  I2C_single_write(I2Cx, ITG3200_ADDR_DEFAUT, ITG3200_SMPLRT_DIV, ( ITG3200_SMPLRT_DIV_VAL(19) ));
  /* Disalbe interrupt */
  I2C_single_write(I2Cx, ITG3200_ADDR_DEFAUT, ITG3200_INT_CFG, ZERO);
  /* Using internal oscillator */
  I2C_single_write(I2Cx, ITG3200_ADDR_DEFAUT, ITG3200_PWR_MGM, ( ITG3200_PWR_MGM_CLK_SEL(0) ));
  return 0;
}

/**
  * @brief  write only one byte to an ITG3200 register
  * @param  I2C interface you wanna use, register address is written and one byte data
  * @retval None
  */
void ITG3200_single_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t data) {
  I2C_single_write(I2Cx, ITG3200_ADDR_DEFAUT, REG_addr, data);
}

/**
  * @brief  read only one byte from an ITG3200 register
  * @param  I2C interface you wanna use, register address is read
  * @retval one byte data
  */
uint8_t ITG3200_single_read(I2C_TypeDef* I2Cx, uint8_t REG_addr) {
  return I2C_single_read(I2Cx, ITG3200_ADDR_DEFAUT, REG_addr);
}

/**
  * @brief  write multi byte to ITG3200 registers
  * @param  I2C interface you wanna use, first register address is written,
  *         no. of byte is written, and a data array
  * @retval None
  */
void ITG3200_burst_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data) {
  I2C_burst_write(I2Cx, ITG3200_ADDR_DEFAUT, REG_addr, n_data, data);
}

/**
  * @brief  read multi byte from ITG3200 registers
  * @param  I2C interface you wanna use, first register address is read,
  *         no. of byte is read, and an array is used to store data
  * @retval None
  */
void ITG3200_burst_read(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data) {
  I2C_burst_read(I2Cx, ITG3200_ADDR_DEFAUT, REG_addr, n_data, data);
}

/**
  * @brief  get raw data of X axis
  * @param  I2C interface you wanna use
  * @retval one word data
  */
int16_t get_RawGyro_X(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ITG3200_ADDR_DEFAUT, ITG3200_GYRO_XOUT_H, 2, data);

  int16_t temp = (int16_t) ( (data[0] << 8) | data[1] );
  return temp;
}

/**
  * @brief  get raw data of Y axis
  * @param  I2C interface you wanna use
  * @retval one word data
  */
int16_t get_RawGyro_Y(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ITG3200_ADDR_DEFAUT, ITG3200_GYRO_YOUT_H, 2, data);

  int16_t temp = (int16_t) ( (data[0] << 8) | data[1] );
  return temp;
}

/**
  * @brief  get raw data of Z axis
  * @param  I2C interface you wanna use
  * @retval one word data
  */
int16_t get_RawGyro_Z(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ITG3200_ADDR_DEFAUT, ITG3200_GYRO_ZOUT_H, 2, data);

  int16_t temp = (int16_t) ( (data[0] << 8) | data[1] );
  return temp;
}

/**
  * @brief  get angular velocity around X axis
  * @param  I2C interface you wanna use
  * @retval g-force along X axis (in g unit)
  */
float get_Gyro_X(I2C_TypeDef* I2Cx) {
  return 0;
}

/**
  * @brief  get angular velocity around Y axis
  * @param  I2C interface you wanna use
  * @retval g-force on Y axis (in g unit)
  */
float get_Gyro_Y(I2C_TypeDef* I2Cx) {
  return 0;
}

/**
  * @brief  get angular velocity around Z axis
  * @param  I2C interface you wanna use
  * @retval g-force on Z axis (in g unit)
  */
float get_Gyro_Z(I2C_TypeDef* I2Cx) {
  return 0;
}


/******************************* END OF FILE **********************************/
