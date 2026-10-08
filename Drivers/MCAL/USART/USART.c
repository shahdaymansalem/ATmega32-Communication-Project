#include "USART.h"

void USART_Init(void)
{
    /* Baud Rate = 9600 bps
       F_CPU = 8 MHz
       UBRR = 51
    */
    UBRRH = 0;
    UBRRL = 51;

    /* Enable Transmitter and Receiver */
    UCSRB = (1 << RXEN) | (1 << TXEN);

    /* 8-bit Data, 1 Stop Bit, No Parity */
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}

void USART_SendByte(uint8 data)
{
    while((UCSRA & (1 << UDRE)) == 0);

    UDR = data;
}

uint8 USART_ReceiveByte(void)
{
    while((UCSRA & (1 << RXC)) == 0);

    return UDR;
}

void USART_SendString(uint8 *string)
{
    uint8 i = 0;

    while(string[i] != '\0')
    {
        USART_SendByte(string[i]);
        i++;
    }
}
void USART_EnableReceiveInterrupt(void)
{
    UCSRB |= (1 << RXCIE);
}