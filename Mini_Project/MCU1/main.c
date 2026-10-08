#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../../Drivers/MCAL/ADC/ADC.h"
#include "../../Drivers/MCAL/I2C/I2C.h"
#include "../../Drivers/MCAL/USART/USART.h"

volatile uint8 usart_command = 0;

ISR(USART_RXC_vect)
{
    usart_command = UDR;
}

int main(void)
{
    uint16 adc_value;

    /* LED on PB0 */
    DDRB |= (1 << PB0);

    /* LED OFF initially */
    PORTB &= ~(1 << PB0);

    /* Initialize */
    ADC_Init(ADC_REF_AVCC, ADC_PRESCALER_64);
    I2C_Init();
    USART_Init();

    USART_EnableReceiveInterrupt();

    sei();

    while(1)
    {
        /* Read potentiometer */
        adc_value = ADC_Read(0);

        /* ========================= */
        /* Send ADC through I2C       */
        /* ========================= */

        I2C_Start();

        /* Slave address 0x10 + Write */
        I2C_Write(0x20);

        /* Send High Byte */
        I2C_Write((uint8)(adc_value >> 8));

        /* Send Low Byte */
        I2C_Write((uint8)(adc_value & 0xFF));

        I2C_Stop();

        /* ========================= */
        /* USART Command              */
        /* ========================= */

        if(usart_command == '1')
        {
            PORTB |= (1 << PB0);

            USART_SendByte('1');

            usart_command = 0;
        }

        else if(usart_command == '0')
        {
            PORTB &= ~(1 << PB0);

            USART_SendByte('0');

            usart_command = 0;
        }

        _delay_ms(100);
    }

    return 0;
}