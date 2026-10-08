#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../../Drivers/MCAL/I2C/I2C.h"
#include "../../Drivers/MCAL/USART/USART.h"
#include "../../Drivers/HAL/LCD/LCD.h"


/* ================================================= */
/* Global Variables                                   */
/* ================================================= */

volatile uint8 high_byte = 0;
volatile uint8 low_byte = 0;

volatile uint8 i2c_state = 0;
volatile uint8 adc_ready = 0;

volatile uint8 usart_status = 0;


/* ================================================= */
/* I2C Slave Interrupt                                */
/* ================================================= */

ISR(TWI_vect)
{
    uint8 status;

    status = TWSR & 0xF8;

    switch(status)
    {
        /* ----------------------------------------- */
        /* Slave Address + Write received            */
        /* ----------------------------------------- */

        case 0x60:

            /*
             * New I2C transaction
             * Next byte will be ADC High Byte
             */

            i2c_state = 0;

            TWCR = (1 << TWINT) |
                   (1 << TWEA)  |
                   (1 << TWEN)  |
                   (1 << TWIE);

            break;


        /* ----------------------------------------- */
        /* Data received + ACK returned              */
        /* ----------------------------------------- */

        case 0x80:

            if(i2c_state == 0)
            {
                /* First byte = ADC High Byte */

                high_byte = TWDR;

                i2c_state = 1;
            }
            else
            {
                /* Second byte = ADC Low Byte */

                low_byte = TWDR;

                adc_ready = 1;

                i2c_state = 0;
            }

            TWCR = (1 << TWINT) |
                   (1 << TWEA)  |
                   (1 << TWEN)  |
                   (1 << TWIE);

            break;


        /* ----------------------------------------- */
        /* STOP condition received                   */
        /* ----------------------------------------- */

        case 0xA0:

            TWCR = (1 << TWINT) |
                   (1 << TWEA)  |
                   (1 << TWEN)  |
                   (1 << TWIE);

            break;


        /* ----------------------------------------- */
        /* Other states                              */
        /* ----------------------------------------- */

        default:

            TWCR = (1 << TWINT) |
                   (1 << TWEA)  |
                   (1 << TWEN)  |
                   (1 << TWIE);

            break;
    }
}


/* ================================================= */
/* USART Receive Interrupt                            */
/* ================================================= */

ISR(USART_RXC_vect)
{
    usart_status = UDR;
}


/* ================================================= */
/* MAIN                                               */
/* ================================================= */

int main(void)
{
    uint16 adc_value;


    /* ================================================= */
    /* Buttons                                           */
    /* ================================================= */

    /* PD2 = ON button */
    DDRD &= ~(1 << PD2);

    /* PD3 = OFF button */
    DDRD &= ~(1 << PD3);

    /* Enable internal pull-up resistors */
    PORTD |= (1 << PD2);
    PORTD |= (1 << PD3);


    /* ================================================= */
    /* Initialize Drivers                                */
    /* ================================================= */

    /* I2C Slave Address = 0x10 */
    I2C_SlaveInit(0x10);

    /* USART */
    USART_Init();

    USART_EnableReceiveInterrupt();

    /* LCD */
    LCD_Init();


    /* ================================================= */
    /* Enable Global Interrupts                          */
    /* ================================================= */

    sei();


    /* ================================================= */
    /* Initial LCD                                       */
    /* ================================================= */

    LCD_SendString((uint8*)"ADC Value:");


    /* ================================================= */
    /* Main Loop                                         */
    /* ================================================= */

    while(1)
    {

        /* ============================================= */
        /* ON BUTTON                                     */
        /* ============================================= */

        if((PIND & (1 << PD2)) == 0)
        {
            /*
             * Send command '1' to MCU1
             * MCU1 will turn LED ON
             */

            USART_SendByte('1');

            _delay_ms(30);

            /*
             * Wait until button is released
             * This prevents multiple transmissions
             */

            while((PIND & (1 << PD2)) == 0);
        }


        /* ============================================= */
        /* OFF BUTTON                                    */
        /* ============================================= */

        if((PIND & (1 << PD3)) == 0)
        {
            /*
             * Send command '0' to MCU1
             * MCU1 will turn LED OFF
             */

            USART_SendByte('0');

            _delay_ms(30);

            /*
             * Wait until button is released
             */

            while((PIND & (1 << PD3)) == 0);
        }


        /* ============================================= */
        /* ADC DATA RECEIVED THROUGH I2C                */
        /* ============================================= */

        if(adc_ready == 1)
        {
            /*
             * Reconstruct 10-bit ADC value
             */

            adc_value = ((uint16)high_byte << 8) | low_byte;


            /* Clear second LCD line */

            LCD_SetCursor(1, 0);

            LCD_SendString((uint8*)"                ");


            /* Display ADC value */

            LCD_SetCursor(1, 0);

            LCD_SendNumber(adc_value);


            /* ADC data processed */

            adc_ready = 0;
        }


        /* ============================================= */
        /* USART STATUS FROM MCU1                        */
        /* ============================================= */

        if(usart_status == '1')
        {
            /*
             * MCU1 confirms LED ON
             */

            LCD_SetCursor(0, 0);

            LCD_SendString((uint8*)"LED ON          ");

            usart_status = 0;
        }


        else if(usart_status == '0')
        {
            /*
             * MCU1 confirms LED OFF
             */

            LCD_SetCursor(0, 0);

            LCD_SendString((uint8*)"LED OFF         ");

            usart_status = 0;
        }

    }

    return 0;
}