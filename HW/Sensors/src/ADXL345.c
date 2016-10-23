/* Includes ------------------------------------------------------------------*/
#include "ADXL345.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
imu accellero;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int ADXL345_Initialize(I2C_TypeDef* I2Cx) {
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_FORMAT, (( ADXL345_FULL_RES | ADXL345_RANGE(ADXL345_RANGE_PM_16G) ) & 0xFF) );
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_BW_RATE, (ADXL345_RATE(0x0C) & 0xFF) );
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_POWER_CTL, (ADXL345_PCTL_MEASURE & 0xFF) );
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_INT_ENABLE, (ADXL345_DATA_READY & 0xFF) );
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_OFSX, ZERO );
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_OFSY, ZERO );
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_OFSZ, BIT5 );
  return 0;
}

void ADXL345_single_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t data) {
  I2C_single_write(I2Cx, ADXL345_ADDR_DEFAUT, REG_addr, data);
}

uint8_t ADXL345_single_read(I2C_TypeDef* I2Cx, uint8_t REG_addr) {
  return I2C_single_read(I2Cx, ADXL345_ADDR_DEFAUT, REG_addr);
}

void ADXL345_burst_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data) {
  I2C_burst_write(I2Cx, ADXL345_ADDR_DEFAUT, REG_addr, n_data, data);
}

void ADXL345_burst_read(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data) {
  I2C_burst_read(I2Cx, ADXL345_ADDR_DEFAUT, REG_addr, n_data, data);
}

uint16_t get_RawAccel_X(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_X0, 2, data);

  uint16_t temp = ( (data[1] << 8) | data[0] );
  return temp;
}

uint16_t get_RawAccel_Y(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_Y0, 2, data);

  uint16_t temp = ( (data[1] << 8) | data[0] );
  return temp;
}

uint16_t get_RawAccel_Z(I2C_TypeDef* I2Cx) {
  uint8_t data[2];
  I2C_burst_read(I2Cx, ADXL345_ADDR_DEFAUT, ADXL345_DATA_Z0, 2, data);

  uint16_t temp = ( (data[1] << 8) | data[0] );
  return temp;
}


/******************************* END OF FILE **********************************/
