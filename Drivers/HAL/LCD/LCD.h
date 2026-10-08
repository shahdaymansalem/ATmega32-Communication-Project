#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include "../../Library/Platform_types.h"
#include "../../Library/BIT_MATH.h"

#define LCD_DATA_PORT PORTB
#define LCD_DATA_DDR  DDRB

#define LCD_CTRL_PORT PORTA
#define LCD_CTRL_DDR  DDRA

#define LCD_RS 1
#define LCD_RW 2
#define LCD_EN 3

void LCD_Init(void);
void LCD_SendCommand(uint8 command);
void LCD_SendChar(uint8 data);
void LCD_SendString(uint8 *string);
void LCD_Clear(void);
void LCD_SetCursor(uint8 row, uint8 column);
void LCD_SendNumber(uint16 number);

#endif