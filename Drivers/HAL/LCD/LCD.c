#define F_CPU 8000000UL

#include "LCD.h"
#include <util/delay.h>

static void LCD_Send4Bits(uint8 data)
{
    LCD_DATA_PORT &= 0x0F;
    LCD_DATA_PORT |= (data & 0xF0);

    SET(LCD_CTRL_PORT, LCD_EN);
    _delay_ms(1);
    CLEAR(LCD_CTRL_PORT, LCD_EN);
    _delay_ms(1);
}

void LCD_SendCommand(uint8 command)
{
    CLEAR(LCD_CTRL_PORT, LCD_RS);
    CLEAR(LCD_CTRL_PORT, LCD_RW);

    LCD_Send4Bits(command);

    LCD_DATA_PORT &= 0x0F;
    LCD_DATA_PORT |= ((command << 4) & 0xF0);

    SET(LCD_CTRL_PORT, LCD_EN);
    _delay_ms(1);
    CLEAR(LCD_CTRL_PORT, LCD_EN);

    _delay_ms(2);
}

void LCD_SendChar(uint8 data)
{
    SET(LCD_CTRL_PORT, LCD_RS);
    CLEAR(LCD_CTRL_PORT, LCD_RW);

    LCD_Send4Bits(data);

    LCD_DATA_PORT &= 0x0F;
    LCD_DATA_PORT |= ((data << 4) & 0xF0);

    SET(LCD_CTRL_PORT, LCD_EN);
    _delay_ms(1);
    CLEAR(LCD_CTRL_PORT, LCD_EN);

    _delay_ms(1);
}

void LCD_Init(void)
{
    /* PB4 - PB7 as output */
    LCD_DATA_DDR |= 0xF0;

    /* PA0, PA1, PA2 as output */
    SET(LCD_CTRL_DDR, LCD_RS);
    SET(LCD_CTRL_DDR, LCD_RW);
    SET(LCD_CTRL_DDR, LCD_EN);

    CLEAR(LCD_CTRL_PORT, LCD_RS);
    CLEAR(LCD_CTRL_PORT, LCD_RW);
    CLEAR(LCD_CTRL_PORT, LCD_EN);

    _delay_ms(20);

    /* 4-bit initialization */
    LCD_Send4Bits(0x30);
    _delay_ms(5);

    LCD_Send4Bits(0x30);
    _delay_us(150);

    LCD_Send4Bits(0x20);
    _delay_ms(1);

    LCD_SendCommand(0x28);   /* 4-bit, 2 lines */
    LCD_SendCommand(0x0C);   /* Display ON */
    LCD_SendCommand(0x06);   /* Increment cursor */
    LCD_SendCommand(0x01);   /* Clear */
    _delay_ms(2);
}

void LCD_SendString(uint8 *string)
{
    uint8 i = 0;

    while(string[i] != '\0')
    {
        LCD_SendChar(string[i]);
        i++;
    }
}

void LCD_Clear(void)
{
    LCD_SendCommand(0x01);
    _delay_ms(2);
}

void LCD_SetCursor(uint8 row, uint8 column)
{
    uint8 address;

    if(row == 0)
        address = 0x80 + column;
    else
        address = 0xC0 + column;

    LCD_SendCommand(address);
}

void LCD_SendNumber(uint16 number)
{
    uint8 digits[5];
    uint8 i = 0;

    if(number == 0)
    {
        LCD_SendChar('0');
        return;
    }

    while(number > 0)
    {
        digits[i] = (number % 10) + '0';
        number /= 10;
        i++;
    }

    while(i > 0)
    {
        i--;
        LCD_SendChar(digits[i]);
    }
}