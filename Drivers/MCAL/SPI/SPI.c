/*
 * SPI.c
 *
 *  Created on: 22 Feb 2023
 *      Author: Alaa Wahba
 */

#include "SPI.h"

void SPI_Init() {

#ifdef MASTER_MODE
	/* GPIO pins Configuration */

	// SS, MOSI and SCK are outputs
	DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB7);

	// MISO is input
	DDRB &= ~(1 << PB6);


	/* Master Configuration */

	// Enable SPI
	SPCR |= (1 << SPE);

	// Configure it as Master
	SPCR |= (1 << MSTR);

	// shift clock = clk/16
	SPCR |= (1 << SPR1);
	SPCR &= ~(1 << SPR0);

#endif


#ifdef SLAVE_MODE

	/* GPIO pins Configuration */

	// MISO is output
	DDRB |= (1 << PB6);

	// SS, MOSI and SCK are inputs
	DDRB &= ~((1 << PB4) | (1 << PB5) | (1 << PB7));


	/* Slave Configuration */

	// Enable SPI
	SPCR |= (1 << SPE);

	// Configure it as Slave
	SPCR &= ~(1 << MSTR);

#endif

}


uint8 SPI_SendRecieveData(uint8 Data) {

	// Put data into SPI data register
	SPDR = Data;

	// Wait until SPI transfer is complete
	while (!(SPSR & (1 << SPIF)))
	{
		// Wait
	}

	// Return received data
	return SPDR;
}