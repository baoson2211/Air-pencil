/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HMC5883L_H
#define __HMC5883L_H

/* Includes ------------------------------------------------------------------*/
#include "imu.h"
#include "main.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

// if communication select I2C, the device address = 0x3C

// Register Map
// Configuration Registers
#define HMC5883L_CONF_REG_A                  0x00 // RW
#define HMC5883L_CONF_REG_B                  0x01 // RW
#define HMC5883L_MODE_REG                    0x02 // RW
// Output data registers
#define HMC5883L_MAG_XOUT_H                  0x03 // R
#define HMC5883L_MAG_XOUT_L                  0x04 // R
#define HMC5883L_MAG_ZOUT_H                  0x05 // R
#define HMC5883L_MAG_ZOUT_L                  0x06 // R
#define HMC5883L_MAG_YOUT_H                  0x07 // R
#define HMC5883L_MAG_YOUT_L                  0x08 // R
// Status register
#define HMC5883L_STATUS_REG                  0x09 // R
// Identification Registers
#define HMC5883L_ID_REG_A                    0x10 // R
#define HMC5883L_ID_REG_B                    0x11 // R
#define HMC5883L_ID_REG_C                    0x12 // R

// ----registrer bit definition ------//
/* HMC5883L Configuration Register A bit definition */
#define HMC5883L_REG_A_MA(x)                 (((x) & 0x3) << 5) // Measurement Samples Averaged
#define HMC5883L_REG_A_DO(x)                 (((x) & 0x7) << 2) // Data Output Rate
#define HMC5883L_REG_A_MS(x)                 (((x) & 0x3) << 0) // Measurement Mode

/* HMC5883L Configuration Register B bit definition */
#define HMC5883L_REG_B_GA(x)                 (((x) & 0x7) << 5) // Gain Configuration

/* HMC5883L Mode Register bit definition */
#define HMC5883L_MODE_REG_HS                 (1 << 7)           // High Speed I2C 3400kHz
#define HMC5883L_MODE_REG_MD(x)              (((x) & 0x3) << 0) // Operating Mode

/* HMC5883L Status Register bit definition */
#define HMC5883L_STATUS_REG_LOCK             (1 << 1)
#define HMC5883L_STATUS_REG_RDY              (1 << 0)

/* HMC5883L Identification Register values definition */
#define HMC5883L_ID_REG_A_VALUE              0x48
#define HMC5883L_ID_REG_B_VALUE              0x34
#define HMC5883L_ID_REG_C_VALUE              0x33

// ----  I2C address definition ----//
#define HMC5883L_ADDR                        0x1E
#define HMC5883L_READ                        ((HMC5883L_ADDR << 1) | 0x01 )
#define HMC5883L_WRITE                       ((HMC5883L_ADDR << 1) & 0xFE )
#define HMC5883L_ADDR_DEFAUT                 ((HMC5883L_ADDR << 1) & 0xFE )

/* Exported functions ------------------------------------------------------- */
int HMC5883L_Initialize(I2C_TypeDef* I2Cx);
void HMC5883L_single_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t data);
uint8_t HMC5883L_single_read(I2C_TypeDef* I2Cx, uint8_t REG_addr);
void HMC5883L_burst_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data);
void HMC5883L_burst_read(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data);
int16_t get_RawMag_X(I2C_TypeDef* I2Cx);
int16_t get_RawMag_Y(I2C_TypeDef* I2Cx);
int16_t get_RawMag_Z(I2C_TypeDef* I2Cx);

#endif /* __HMC5883L_H */
