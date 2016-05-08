//
// task2.c
//
// Created: 07.04.2016
// Author: Asbjørn Espe
//

#define F_CPU 16000000UL

// System headers
#include <avr/io.h>  // Pin io
#include <util/delay.h>  // _delay_ms();
#include <stdbool.h>  // Boolean type
#include <stdlib.h>  // rand(), srand()
//#include <time.h>  // time functions for random number seed

// Project headers
#include "display.h"


#define LED1 PORTD5 //OC1A
#define LED2 PORTD4	//OC1B
#define LED3 PORTA3
#define SW1	PINC1
#define SW2	PINA0
#define SW3 PINA1

// In task 2 we will use the function for writing strings to the display. We want to make a simple game.
// Make the game Simon Says (or any equivalent simple game of your choice).
// The game should display instructions on the screen, and should use LEDs and buttons for interactivity.

// Example: Simon Says
// A pattern is played back on the LEDs. The user is now tasked with repeating the sequence on the buttons.
// If the user repeats the sequence correctly, the difficulty is increased, such that a new random number is added
// to the sequence. When there is a certain number in the sequence and the user correctly repeats the pattern
// the game is won.

// You are encouraged to reuse functions and code from earlier exercises.

void LEDinit()
{
	//Enable LEDs as output
	DDRD |= (1<<LED1) | (1<<LED2);
	DDRA |= (1<<LED3);
	
	//Turn LEDs default off
	PORTD |=(1<<LED1) | (1<<LED2);
	PORTA |=(1<<LED3);
}

void SWinit()
{
	//Enable buttons as input
	DDRC &= ~(1<<SW1);
	DDRA &= ~(1<<SW2) | (1<<SW3);

	//Enable pull-up
	PORTC |= (1 << SW1);
	PORTA |= (1 << SW2) | (1 << SW3);
}

int main()
{

	LEDinit();
	SWinit();
	DISP_init();
	DISP_print("Welcome to\nSimon Says!");
	_delay_ms(3000);
	
	
	const uint8_t numberOfRounds = 10;
	uint8_t answers[numberOfRounds];
	uint8_t guesses[numberOfRounds];
	uint8_t totalNumberOfGuesses = 1;
	uint8_t currentNumberOfGuesses;
	char totalNumbersWhenOver;
	bool won = true;
	
	


	
	// CODE GOES HERE
	//
	// Good luck!




	// Infinite loop to keep the chip going
	while(1)
	{
		DISP_clear();
		DISP_print("Here comes the \nsequence: ");
		_delay_ms(2000);
		
		srand(0);

		for (uint8_t i= 0; i< totalNumberOfGuesses; i++)
		{
			answers[i] = (rand() % 3);

			if(answers[i] == 0)
			{
				PORTD ^= (1<<LED1);
				_delay_ms(500);
				PORTD ^= (1<<LED1);
			}
			else if(answers[i] == 1)
			{
				PORTD ^= (1<<LED2);
				_delay_ms(500);
				PORTD ^= (1<<LED2);
			}
			else if(answers[i] == 2)
			{
				PORTA ^= (1<<LED3);
				_delay_ms(500);
				PORTA ^= (1<<LED3);
			}
				_delay_ms(500);


			}
			DISP_clear();
			DISP_print("Your turn!");
			currentNumberOfGuesses = 0;
			while(currentNumberOfGuesses < totalNumberOfGuesses)
			{
				if (!((1<<SW1) & PINC))
				{
					guesses[currentNumberOfGuesses] = 0;
					currentNumberOfGuesses += 1;
					PORTD ^= (1<<LED1);
					_delay_ms(500);
					PORTD ^= (1<<LED1);

				}

				else if (!((1<<SW2) & PINA))
				{
					guesses[currentNumberOfGuesses] = 1;
					currentNumberOfGuesses += 1;
					PORTD ^= (1<<LED2);
					_delay_ms(500);
					PORTD ^= (1<<LED2);

				}

				else if (!((1<<SW3) & PINA))
				{
				guesses[currentNumberOfGuesses] = 2;
				currentNumberOfGuesses += 1;
					PORTA ^= (1<<LED3);
					_delay_ms(500);
					PORTA ^= (1<<LED3);

				}
			}

			for (uint8_t i = 0; i<currentNumberOfGuesses; i++)
			{
				if (answers[i] != guesses[i])
				{
					won = false;
				}


			}

			DISP_clear();
			if (won)
			{
				if (totalNumberOfGuesses < numberOfRounds)
				{
					totalNumberOfGuesses += 1;
					DISP_print("Correct!");
					_delay_ms((1000));
					DISP_clear();
					DISP_print("Next round");
					_delay_ms(1000);
				
				}
				else if (totalNumberOfGuesses == numberOfRounds)
				{
					DISP_print("You won!\nYou got:\n");
					totalNumbersWhenOver = '0' + totalNumberOfGuesses;
					DISP_putc(totalNumbersWhenOver);
					DISP_print(" points.");
					_delay_ms((5000));
					DISP_clear();
					DISP_print("New game :)");
					_delay_ms(2000);
					totalNumberOfGuesses = 1;
				}
				

				
				_delay_ms(2000);
			}
			else
			{
			DISP_print("You lost!\nYou got:\n");
			totalNumbersWhenOver = '0' + totalNumberOfGuesses - 1;
			//totalNumbersWhenOver -= 1;
			DISP_putc(totalNumbersWhenOver);
			DISP_print(" points.");
			_delay_ms(5000);
			DISP_clear();
			DISP_print("New game");
			_delay_ms(2000);
			totalNumberOfGuesses = 1;
			}

			


		}



	}



