#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include "../../Library/Platform_types.h"

void USART_Init(void);
void USART_SendByte(uint8 data);
uint8 USART_ReceiveByte(void);
void USART_SendString(uint8 *string);
void USART_EnableReceiveInterrupt(void);

#endif