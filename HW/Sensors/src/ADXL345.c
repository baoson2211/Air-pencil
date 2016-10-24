/* Includes ------------------------------------------------------------------*/
#include "ADXL345.h"

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
  * @brief  ADXL345 Initialize
  * @param  I2C interface you wanna use
  * @retval 0 for done or other for not
  */
int ADXL345_Initialize(I2C_TypeDef* I2Cx) {
  /* range 16g (13 bit raw data) and full resolution */
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_FORMAT, (( ADXL345_FULL_RES | ADXL345_RANGE(ADXL345_RANGE_PM_16G) ) & 0xFF) );
  /* bandwitdh and output rate - see more Table 7 in datasheet rev. D */
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_BW_RATE, (ADXL345_RATE(0x0C) & 0xFF) );
  /* measuarment mode */
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_POWER_CTL, (ADXL345_PCTL_MEASURE & 0x08) );
  /* only DATA_READY */
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_INT_ENABLE, (ADXL345_DATA_READY & 0x80) );
  /* 3 axis offset */
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_OFSX, ZERO );
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_OFSY, ZERO );
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_OFSZ, BIT5 );
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
uint8_t ADXL345_single_read(I2C_TypeDef* I2Cx, uint8_t REG_addr) {
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
uint16_t get_RawAccel_X(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_X0, 2, data);

  uint16_t temp = ( (data[1] << 8) | data[0] );
  return temp;
}

/**
  * @brief  get raw data of Y axis
  * @param  I2C interface you wanna use
  * @retval one word data
  */
uint16_t get_RawAccel_Y(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_Y0, 2, data);

  uint16_t temp = ( (data[1] << 8) | data[0] );
  return temp;
}

/**
  * @brief  get raw data of Z axis
  * @param  I2C interface you wanna use
  * @retval one word data
  */
uint16_t get_RawAccel_Z(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_Z0, 2, data);

  uint16_t temp = ( (data[1] << 8) | data[0] );
  return temp;
}


/******************************* END OF FILE **********************************/
