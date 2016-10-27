/*
 * i2c.c
 *
 *  Created on: Oct 23, 2016
 *      Author: b4050n
 */


/* Includes ------------------------------------------------------------------*/
#include "i2c.h"
#include "main.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define OwnAddress 0x01

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

// Configue I2C1 (pin PB6  and PB7 )
// Configue I2C2 (pin PB10 and PB11)
int I2C_Configration(I2C_TypeDef* I2Cx, int ClockSpeed)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  I2C_InitTypeDef   I2C_InitStructure;

  // Enable GPIOB clocks
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  // Configure I2C clock and GPIO
  GPIO_StructInit(&GPIO_InitStructure);

  /* I2Cx clock enable */
  RCC_APB1PeriphClockCmd(I2Cx == I2C1 ? RCC_APB1Periph_I2C1 : RCC_APB1Periph_I2C2, ENABLE);
  if (I2Cx == I2C1){
    /* I2C1 SDA and SCL configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* I2C1 Reset */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
  }
  else {
    /* I2C2 SDA and SCL configuration */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /* I2C2  Reset */
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
  }

  /* Configure I2Cx */
  I2C_StructInit(&I2C_InitStructure);
  I2C_DeInit(I2Cx);

  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  if (ClockSpeed == I2C_FAST_SPEED)
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;
  else if (ClockSpeed == I2C_NORMAL_SPEED)
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  else
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = OwnAddress;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = ClockSpeed;

  I2C_Init(I2Cx, &I2C_InitStructure);
  I2C_Cmd(I2Cx, ENABLE);

  return 0;
}


void I2C_single_write(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t REG_addr, uint8_t data)
{
  I2C_GenerateSTART(I2Cx, ENABLE);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2Cx, HW_address, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_SendData(I2Cx, REG_addr);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  I2C_SendData(I2Cx, data);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  I2C_GenerateSTOP(I2Cx, ENABLE);
    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
}

void I2C_burst_write(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t REG_addr, uint8_t n_data, uint8_t *data)
{
  I2C_GenerateSTART(I2Cx, ENABLE);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2Cx, HW_address, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_SendData(I2Cx, REG_addr);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  while(n_data--) {
    I2C_SendData(I2Cx, *data++);
      while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  }
  I2C_GenerateSTOP(I2Cx, ENABLE);
    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
}

uint8_t I2C_single_read(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t REG_addr)
{
  uint8_t data;
    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
  I2C_GenerateSTART(I2Cx, ENABLE);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2Cx, HW_address, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_Cmd(I2Cx, ENABLE);
  I2C_SendData(I2Cx, REG_addr);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  I2C_GenerateSTART(I2Cx, ENABLE);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2Cx, HW_address, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
  data = I2C_ReceiveData(I2Cx);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
  I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current);
  I2C_AcknowledgeConfig(I2Cx, DISABLE);
  I2C_GenerateSTOP(I2Cx, ENABLE);
    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
  I2C_AcknowledgeConfig(I2Cx, ENABLE);
  return data;
}

// OK
void I2C_burst_read(I2C_TypeDef* I2Cx, uint8_t HW_address, uint8_t REG_addr, uint8_t n_data, uint8_t *data)
{
    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
  I2C_GenerateSTART(I2Cx, ENABLE);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2Cx, HW_address, I2C_Direction_Transmitter);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_Cmd(I2Cx, ENABLE);
  I2C_SendData(I2Cx, REG_addr);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  I2C_GenerateSTART(I2Cx, ENABLE);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2Cx, HW_address, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  while(n_data--) {
      while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
    *data++ = I2C_ReceiveData(I2Cx);
    if(!n_data) I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current);
    else I2C_AcknowledgeConfig(I2Cx, ENABLE);
  }
  I2C_AcknowledgeConfig(I2Cx, DISABLE);
  I2C_GenerateSTOP(I2Cx, ENABLE);
    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
  I2C_AcknowledgeConfig(I2Cx, ENABLE);
}
