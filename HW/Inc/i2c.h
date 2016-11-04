/*
 * i2c.h
 *
 *  Created on: Oct 23, 2016
 *      Author: b4050n
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define I2C_NORMAL_SPEED 100000
#define I2C_FAST_SPEED   400000

/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

int I2C_Configration(I2C_TypeDef* I2Cx, int ClockSpeed);
void I2C_single_write(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t REG_addr, uint8_t data);
void I2C_burst_write(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t REG_addr, uint8_t n_data, uint8_t *data);
__IO uint8_t I2C_single_read(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t REG_addr);
void I2C_burst_read(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t REG_addr, uint8_t n_data, uint8_t *data);

#endif /* INC_I2C_H_ */
