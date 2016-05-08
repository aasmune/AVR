/*
 * Task4.c
 *
 * Created: 4/18/2016 4:54:10 PM
 * Author : Thomas Stenseth
 */ 

/*
* This time you'll have to do all the setup and coding yourself. 
* You are gonna connect the "OLED1 Xplained Pro" extension card to the ATmega324PB kit, 
* and make the LEDs and buttons work on the extension card.
*/

/*
* Connect the OLED1 extension board to EXT1 on the ATmega board.
* Set the proper ports and pins for the LEDs and the buttons on the OLED1, don't enable the LED0 and SW0 on the ATmega
* Checkout the datasheet for the OLED1 extension card to see which pins the different LEDs/buttons are connected to
* Checkout the datasheet for the ATmega to see which ports and pins on the microcontroller that corresponds to those pins from EXT1
* Remember: The ports (DDR - A/B/C/D) on the ATmega can be different for the LEDs/buttons located on the same extension card (EXT1).
*/

// F_CPU
#define F_CPU 16000000UL

// System headers
#include <avr/io.h>
#include <util/delay.h>

// LEDs - OLED1 Xplained Pro
#define LED1 PIND5
#define LED2 PIND4
#define LED3 PINA3

// Buttons - OLED1 Xplained Pro
#define SW1 PINC1 
#define SW2 PINA0
#define SW3 PINA1

void task4()
{

}

int main(void){
	
    /* 
	* Do the following:
	* Set the LEDs as output
	* Set buttons as input
	* Enable pull-ups on the buttons 
	*/

	//Enable LEDs as output
	DDRD |= (1<<LED1) | (1<<LED2);
	DDRA |= (1<<LED3);

	//Turn LEDs default off
	PORTD |=(1<<LED1) | (1<<LED2);
	PORTA |=(1<<LED3);

	//Enable buttons as input
	DDRC &= ~(1<<SW1);
	DDRA &= ~(1<<SW2) | (1<<SW3);

	//Enable pull-up
	PORTC |= (1 << SW1);
	PORTA |= (1 << SW2) | (1 << SW3);

	

	
    while (1){
	    
	    if (!((1<<SW1) & PINC))
	    {
		    PORTD ^= (1<<LED1);
		    _delay_ms(500);
	    }
	    else
	    {
		    PORTD;
	    }

	    if (!((1<<SW2) & PINA))
	    {
		    PORTD ^= (1<<LED2);
		    _delay_ms(500);
	    }
	    else
	    {
		    PORTD;
	    }

	    if (!((1<<SW3) & PINA))
	    {
		    PORTA ^= (1<<LED3);
		    _delay_ms(500);
	    }
	    else
	    {
		    PORTA;
	    }
			//_delay_ms(500);


    }
}

