//
// spi.c
//
// Created: 07.04.2016
// Author: Asbjørn Espe
//


// System headers
#include <avr/io.h>

// Project headers
#include "spi.h"

// In this file, you will need to write the contents of the SPI communiaction routines.
// You need to setup SPI communication in SPI_MasterInit() and
// transmit data in SPI_MasterTransmit(...).
//
// HINT: Check out the defines in the file defines.h to see defines
// such as data direction registers and bit positions, and as always:
// RTFD

#define MOSI DDRB5
#define SCK DDRB7
#define SS0 DDRB4


void SPI_MasterInit()
{
	// Initialize the SPI port as master
	// You will need to set MOSI, SCK, SS (slave select) as outputs
	//
	// CODE GOES HERE
	DDRB = (1<<MOSI)|(1<<SCK) | (1<<SS0);




	// Now enable SPI, Master and set clock rate
	//
	// CODE GOES HERE

	SPCR0 = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char cData)
{
	// First select the correct slave by setting the slave select (SS) bit LOW
	//
	PORTB &= ~(1<<SS0);


	// Then start the transmission by assigning the data to the SPI data register
	//
	SPDR0 = cData;


	// Now wait for the data transmission to complete by periodically checking the SPI status register
	//
	while(!(SPSR0 & (1<<SPIF)));


	// Finally set the slave select bit HIGH before leaving the function
	//
	PORTB |= 1<<SS0;

}
