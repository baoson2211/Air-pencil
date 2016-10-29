/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ITG3200_H
#define __ITG3200_H

/* Includes ------------------------------------------------------------------*/
#include "imu.h"
#include "main.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

// if communication select I2C, the device id is setting by AD0 pin
// ad0 = 0, device address = 0x68
// ad0 = 1, device address = 0x69

// Register Map
#define ITG3200_WHO_AM_I                    0x00 // RW
#define ITG3200_SMPLRT_DIV                  0x15 // RW
#define ITG3200_DLPF_FS                     0x16 // RW
#define ITG3200_INT_CFG                     0x17 // RW
// Interrupt status register
#define ITG3200_INT_STATUS                  0x1A // R
// Temperature data registers
#define ITG3200_TEMP_OUT_H                  0x1B // R
#define ITG3200_TEMP_OUT_L                  0x1C // R
// Gyro data registers
#define ITG3200_GYRO_XOUT_H                 0x1D // R
#define ITG3200_GYRO_XOUT_L                 0x1E // R
#define ITG3200_GYRO_YOUT_H                 0x1F // R
#define ITG3200_GYRO_YOUT_L                 0x20 // R
#define ITG3200_GYRO_ZOUT_H                 0x21 // R
#define ITG3200_GYRO_ZOUT_L                 0x22 // R
// Power management register
#define ITG3200_PWR_MGM                     0x3E // RW

// ----registrer bit definitioin ------//
/* ITG3200_ID definition */
#define ITG3200_ID(x)                       (((x) & 0x3F) << 1)

/* ITG3200_SMPLRT_DIV definition */
#define ITG3200_SMPLRT_DIV_VAL(x)           ((x) & 0xFF)

/* ITG3200_DLPF_FS definition */
#define ITG3200_DLPF_FS_SEL(x)              (((x) & 0x3) << 3)
#define ITG3200_DLPF_CFG(x)                 ((x) & 0x7)

/* ITG3200_INT_CFG definition */
#define ITG3200_INT_CFG_ACTL                (1 << 7)
#define ITG3200_INT_CFG_OPEN                (1 << 6)
#define ITG3200_INT_CFG_LATCH_INT_EN        (1 << 5)
#define ITG3200_INT_CFG_INT_ANYRD_2CLEAR    (1 << 4)
#define ITG3200_INT_CFG_ITG_RDY_EN          (1 << 2)
#define ITG3200_INT_CFG_RAW_RDY_EN          (1 << 0)

/* ITG3200_INT_STATUS definition */
#define ITG3200_INT_STATUS_ITG_RDY          (1 << 2)
#define ITG3200_INT_STATUS_RAW_DATA_RDY     (1 << 0)

/* ITG3200_PWR_MGM definition */
#define ITG3200_PWR_MGM_H_RESET             (1 << 7)
#define ITG3200_PWR_MGM_SLEEP               (1 << 6)
#define ITG3200_PWR_MGM_STBY_XG             (1 << 5)
#define ITG3200_PWR_MGM_STBY_YG             (1 << 4)
#define ITG3200_PWR_MGM_STBY_ZG             (1 << 3)
#define ITG3200_PWR_MGM_CLK_SEL(x)          ((x) & 0x7)

// ----  I2C address definition ----//
//if pin AD0 ADDRESS(pin 9) as GND, I2C address as 0x68.
//if pin AD0 ADDRESS(pin 9) as VCC, I2C address as 0x69.
#ifndef __AD0_ITG3200
  #define ITG3200_ADDR                      0x68
#else
  #define ITG3200_ADDR                      0x69
#endif
#define ITG3200_READ                        (((ITG3200_ADDR << 1) & 0xFE) | 0x01)
#define ITG3200_WRITE                       ((ITG3200_ADDR << 1) & 0xFE )
#define ITG3200_ADDR_DEFAUT                 ((ITG3200_ADDR << 1) & 0xFE )

/* Exported functions ------------------------------------------------------- */
int ITG3200_Initialize(I2C_TypeDef* I2Cx);
void ITG3200_single_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t data);
uint8_t ITG3200_single_read(I2C_TypeDef* I2Cx, uint8_t REG_addr);
void ITG3200_burst_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data);
void ITG3200_burst_read(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data);
int16_t get_RawGyro_X(I2C_TypeDef* I2Cx);
int16_t get_RawGyro_Y(I2C_TypeDef* I2Cx);
int16_t get_RawGyro_Z(I2C_TypeDef* I2Cx);
float get_Gyro_X(I2C_TypeDef* I2Cx);
float get_Gyro_Y(I2C_TypeDef* I2Cx);
float get_Gyro_Z(I2C_TypeDef* I2Cx);

#endif /* __ITG3200_H */
