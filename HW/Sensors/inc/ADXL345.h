/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADXL345_H
#define __ADXL345_H

/* Includes ------------------------------------------------------------------*/
#include "imu.h"
#include "main.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

// if communication select I2C, the device id is setting by alt/sdo pin
// alt = 0, device address = 0x53
// alt = 1, device address = 0x1d

// Register Map
#define ADXL345_DEVICE_ID	     0x00
#define ADXL345_THRESH_TAP     0x1D
#define ADXL345_OFSX           0x1E
#define ADXL345_OFSY           0x1F
#define ADXL345_OFSZ           0x20
#define ADXL345_DUR            0x21
#define ADXL345_LATENT         0x22
#define ADXL345_WINDOW         0x23
#define ADXL345_THRESH_ACK     0x24
#define ADXL345_THRESH_INACT   0x25
#define ADXL345_TIME_INACT     0x26
#define ADXL345_ACT_INACT_CTL  0x27
#define ADXL345_THRESH_FF      0x28
#define ADXL345_TIME_FF        0x29
#define ADXL345_TAP_AXES       0x2A
#define ADXL345_ACT_TAP_STATUS 0x2B
#define ADXL345_BW_RATE        0x2C
#define ADXL345_POWER_CTL      0x2D

#define ADXL345_INT_ENABLE     0x2E
#define ADXL345_INT_MAP        0x2F
#define ADXL345_INT_SOURCE     0x30
#define ADXL345_DATA_FORMAT    0x31
#define ADXL345_DATA_X0        0x32
#define ADXL345_DATA_X1        0x33
#define ADXL345_DATA_Y0        0x34
#define ADXL345_DATA_Y1        0x35
#define ADXL345_DATA_Z0        0x36
#define ADXL345_DATA_Z1        0x37
#define ADXL345_FIFO_CTL       0x38
#define ADXL345_FIFO_STATUS    0x39

// ----registrer bit definitioin ------//
/* ADXL345_ACT_INACT_CTL definition */
#define ADXL345_ACT_ACDC        (1 << 7)
#define ADXL345_ACT_X_EN        (1 << 6)
#define ADXL345_ACT_Y_EN        (1 << 5)
#define ADXL345_ACT_Z_EN        (1 << 4)
#define ADXL345_INACT_ACDC      (1 << 3)
#define ADXL345_INACT_X_EN      (1 << 2)
#define ADXL345_INACT_Y_EN      (1 << 1)
#define ADXL345_INACT_Z_EN      (1 << 0)

/* ADXL345_TAP_AXES definition */
#define ADXL345_SUPPRESS        (1 << 3)
#define ADXL345_TAP_X_EN        (1 << 2)
#define ADXL345_TAP_Y_EN        (1 << 1)
#define ADXL345_TAP_Z_EN        (1 << 0)

/* ADXL345_ACT_TAP_STATUS definition */
#define ADXL345_ACT_X_SRC       (1 << 6)
#define ADXL345_ACT_Y_SRC       (1 << 5)
#define ADXL345_ACT_Z_SRC       (1 << 4)
#define ADXL345_ASLEEP          (1 << 3)
#define ADXL345_TAP_X_SRC       (1 << 2)
#define ADXL345_TAP_Y_SRC       (1 << 1)
#define ADXL345_TAP_Z_SRC       (1 << 0)

/* ADXL345_BW_RATE definition */
#define ADXL345_LOW_POWER       (1 << 4)
#define ADXL345_RATE(x)         ((x) & 0xF)

/* ADXL345_POWER_CTL definition */
#define ADXL345_PCTL_LINK       (1 << 5)
#define ADXL345_PCTL_AUTO_SLEEP (1 << 4)
#define ADXL345_PCTL_MEASURE    (1 << 3)
#define ADXL345_PCTL_SLEEP      (1 << 2)
#define ADXL345_PCTL_WAKEUP(x)  ((x) & 0x3)

/* ADXL345_INT_ENABLE / ADXL345_INT_MAP / ADXL345_INT_SOURCE definition */
#define ADXL345_DATA_READY      (1 << 7)
#define ADXL345_SINGLE_TAP      (1 << 6)
#define ADXL345_DOUBLE_TAP      (1 << 5)
#define ADXL345_ACTIVITY        (1 << 4)
#define ADXL345_INACTIVITY      (1 << 3)
#define ADXL345_FREE_FALL       (1 << 2)
#define ADXL345_WATERMARK       (1 << 1)
#define ADXL345_OVERRUN         (1 << 0)

/* ADXL345_DATA_FORMAT definition */
#define ADXL345_SELF_TEST       (1 << 7)
#define ADXL345_SPI             (1 << 6)
#define ADXL345_INT_INVERT      (1 << 5)
#define ADXL345_FULL_RES        (1 << 3)
#define ADXL345_JUSTIFY         (1 << 2)
#define ADXL345_RANGE(x)        ((x) & 0x3)

/* ADXL345_RANGE(x) options */
#define ADXL345_RANGE_PM_2G     0
#define ADXL345_RANGE_PM_4G     1
#define ADXL345_RANGE_PM_8G     2
#define ADXL345_RANGE_PM_16G    3

/* ADXL345_FIFO_CTL definition */
#define ADXL345_FIFO_MODE(x)    (((x) & 0x3) << 6)
#define ADXL345_TRIGGER         (1 << 5)
#define ADXL345_SAMPLES(x)      ((x) & 0x1F)

/* ADXL345_FIFO_MODE(x) options */
#define ADXL345_FIFO_BYPASS     0
#define ADXL345_FIFO_FIFO       1
#define ADXL345_FIFO_STREAM     2
#define ADXL345_FIFO_TRIGGER    3

/* ADXL345_FIFO_STATUS definition */
#define ADXL345_FIFO_TRIG       (1 << 7)
#define ADXL345_ENTRIES(x)      ((x) & 0x3F)

/* ADXL345 Full Resolution Scale Factor */
#define ADXL345_SCALE_FACTOR    4
/* ADXL345 Power Save Mode */
#define MEASURE_MODE            0x01
#define STANBY_MODE             0x00

// ----  I2C address definition ----//
//if pin ALT ADDRESS(pin 12) as GND, I2C address as 0x53.
//if pin ALT ADDRESS(pin 12) as VCC, I2C address as 0x1D.
#ifndef __ALT_ADXL345
  #define ADXL345_ADDR          0x53
#else
  #define ADXL345_ADDR          0x1D
#endif
#define ADXL345_READ            (((ADXL345_ADDR << 1) & 0xFE) | 0x01)
#define ADXL345_WRITE           ((ADXL345_ADDR << 1) & 0xFE)
#define ADXL345_ADDR_DEFAUT     ((ADXL345_ADDR << 1) & 0xFE)

/* Exported functions ------------------------------------------------------- */
int ADXL345_Initialize(I2C_TypeDef* I2Cx);
void ADXL345_single_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t data);
uint8_t ADXL345_single_read(I2C_TypeDef* I2Cx, uint8_t REG_addr);
void ADXL345_burst_write(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data);
void ADXL345_burst_read(I2C_TypeDef* I2Cx, uint8_t REG_addr, uint8_t n_data, uint8_t *data);
int16_t get_RawAccel_X(I2C_TypeDef* I2Cx);
int16_t get_RawAccel_Y(I2C_TypeDef* I2Cx);
int16_t get_RawAccel_Z(I2C_TypeDef* I2Cx);
float get_Accel_X(I2C_TypeDef* I2Cx);
float get_Accel_Y(I2C_TypeDef* I2Cx);
float get_Accel_Z(I2C_TypeDef* I2Cx);

#endif /* __ADXL345_H */
