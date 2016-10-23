#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_conf.h"

void Rcc_Configuration(void);
void UsartGPIO_Configuration(void);
void USART_Configuration(void);
void UsartGPIO_CTRT_Configuration(void);
void USART_CTRT_Configuartion(void);
void USART_SendText(USART_TypeDef* USARTx, char* Str);
void USART_SendNumber(USART_TypeDef* USARTx, uint32_t x);
//

#endif /*_USART_H*/
