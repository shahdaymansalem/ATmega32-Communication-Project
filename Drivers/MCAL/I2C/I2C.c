#include "I2C.h"

void I2C_Init(void)
{
    /*
     * F_CPU = 8 MHz
     * I2C = 100 kHz
     */
    TWBR = 32;
    TWSR = 0x00;

    TWCR = (1 << TWEN);
}

uint8 I2C_Start(void)
{
    uint8 status;

    TWCR = (1 << TWINT) |
           (1 << TWSTA) |
           (1 << TWEN);

    while((TWCR & (1 << TWINT)) == 0);

    status = TWSR & 0xF8;

    return status;
}

void I2C_Stop(void)
{
    TWCR = (1 << TWINT) |
           (1 << TWSTO) |
           (1 << TWEN);
}

uint8 I2C_Write(uint8 data)
{
    uint8 status;

    TWDR = data;

    TWCR = (1 << TWINT) |
           (1 << TWEN);

    while((TWCR & (1 << TWINT)) == 0);

    status = TWSR & 0xF8;

    return status;
}

uint8 I2C_Read_ACK(void)
{
    TWCR = (1 << TWINT) |
           (1 << TWEN) |
           (1 << TWEA);

    while((TWCR & (1 << TWINT)) == 0);

    return TWDR;
}

uint8 I2C_Read_NACK(void)
{
    TWCR = (1 << TWINT) |
           (1 << TWEN);

    while((TWCR & (1 << TWINT)) == 0);

    return TWDR;
}

/* ========================= */
/* I2C SLAVE                 */
/* ========================= */

void I2C_SlaveInit(uint8 address)
{
    /* Slave address = 0x10 */
    TWAR = (address << 1);

    /*
     * Enable:
     * TWINT
     * TWEA
     * TWEN
     * TWIE = TWI Interrupt
     */
    TWCR = (1 << TWINT) |
           (1 << TWEA)  |
           (1 << TWEN)  |
           (1 << TWIE);
}