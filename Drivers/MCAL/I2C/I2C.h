#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include "../../Library/Platform_types.h"

#define I2C_FREQUENCY 100000UL

void I2C_Init(void);
uint8 I2C_Start(void);
void I2C_Stop(void);
uint8 I2C_Write(uint8 data);
uint8 I2C_Read_ACK(void);
uint8 I2C_Read_NACK(void);

void I2C_SlaveInit(uint8 address);

#endif