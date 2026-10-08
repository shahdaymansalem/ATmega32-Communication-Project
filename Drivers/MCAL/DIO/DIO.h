#ifndef DIO_H_
#define DIO_H_

#include <avr/io.h>
#include "../../Library/Platform_types.h"
#include "../../Library/BIT_MATH.h"

/* Pins */
#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7

/* Ports */
#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3

/* Direction */
#define OUTPUT 1
#define INPUT  0

#define PORT_OUTPUT 0xFF
#define PORT_INPUT  0x00

/* Values */
#define HIGH 1
#define LOW  0

#define PORT_HIGH 0xFF
#define PORT_LOW  0x00


void DIO_initPin(uint8 pinNumber, uint8 port, uint8 pinDirection);

void DIO_initPort(uint8 port, uint8 portDirection);

void DIO_WritePin(uint8 pinNumber, uint8 port, uint8 value);

void DIO_WritePort(uint8 port, uint8 value);

uint8 DIO_ReadPin(uint8 pinNumber, uint8 port);

uint8 DIO_ReadPort(uint8 port);

void DIO_Toggle(uint8 pinNumber, uint8 port);


#endif