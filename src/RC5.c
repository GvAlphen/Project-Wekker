/*
 * RC5.c
 *
 *  Created on: 7 okt. 2014
 *      Author: Martijn
 */

#include "RC5.h"
#include "timer.h"

static short message = 0x0000;
static char RC5rising = 0;
static char RC5middle = 1;
static int messageLocation = 13;

int interrupt = 0;
int commandCount = 0;

unsigned int lastbit;
unsigned int currentbit;
unsigned int lastToggle;
unsigned int currentToggle;
unsigned long command;
unsigned int realCommand;
int count = 0;
unsigned int interval[1000];
unsigned long commands[100];
unsigned int realCommands[100];

int test[2000];

/*unsigned char getCommand(unsigned short message) {
	return message & 0x3F;
}*/

void initRC5() {
	//Set direction to input
	FIO2DIR0 &= ~(0xFFFF);
	//Enable External interrupt 3, at addres 21 of the ISER0 register
	ISER0 |= (1 << 21);
	//Set the interrupt to be edge-sensitive for PIO2_6
	EXTMODE |= (1 << 0);
	//Enable Falling-Edge interrupt for PIO2_6
	IO2IntEnF |= (1 << 6);
	//Enable Rising-Edge interrupt for PIO2_6
	IO2IntEnR |= (1 << 6);
}

void EINT3_IRQHandler() {
	int i;
	if (count == 0) {
		initTimer0();
		command = 0;
		realCommand = 0;
		resetTimer0();
		count++;
	} else if (count == 1) {
		//Startup bit
		currentbit = 1;

		command = command << 1;
		command = command | currentbit;
		command = command << 1;

		lastbit = currentbit;
		resetTimer0();
		count++;
	} else {
		interval[count - 1] = readTimer0();

		if (interval[count - 1] <= 1000 & interval[count - 1] >= 600) {
			//Short pulse (~800 uS)
			if (lastbit == 1) {	 // We're currently at a low
				currentbit = 0;
				command = command | currentbit;
				command = command << 1;
				lastbit = currentbit;
			} else {			 // We're currently at a high
				currentbit = 1;
				command = command | currentbit;
				command = command << 1;
				lastbit = currentbit;
			}
		} else if (interval[count - 1] >= 1400 & interval[count - 1] <= 1800) {
			//Long pulse (~1600uS)
			if (lastbit == 1) {	 // We're currently at a low
				currentbit = 0;
				command = command | currentbit;
				command = command << 2;
				lastbit = currentbit;
			} else {			 // We're currently at a high
				currentbit = 1;
				command = command | currentbit;
				command = command << 1;
				command = command | currentbit;
				command = command << 1;
				lastbit = currentbit;
			}
		} else {
			//Delay is at around 17k so the current command is over
			command = command >> 1;

			//Adds a 0 at the end where there is one missing
			if ((command & 0x4000000) == 0) {
				command = command << 1;
			}

			//Command in manchester
			commands[commandCount] = command & 0xFFF;
			currentToggle = command & 0x400000;
			currentToggle = currentToggle >> 22;
			test[commandCount] = currentToggle;

			//Make this into the correct number
			for (i = 0; i < 5; i++) {
				if ((commands[commandCount] & (0x1 << i * 2))
						== (0x1 << i * 2)) {
					realCommand = realCommand | (0x1 << i);
				}
			}

			if((currentToggle != lastToggle || commandCount == 0) && count > 20){
				realCommands[commandCount] = realCommand;
				commandCount++;
			}

			lastToggle = currentToggle;
			realCommand = 0;
			command = 0;
			count = 0;
		}
		resetTimer0();
		count++;
	}

	IO2IntClr |= (1 << 6);
	__asm("nop");
	__asm("nop");
	//# end reset



/*
	 int timer = readTimer0();

	 test[interrupt] = timer;
	 interrupt++;

	 resetTimer0();

	 IO2IntClr |= (1 << 6);
	 __asm("nop");
	 __asm("nop");
	 //# end reset
*/


	/*	int timer = readTimer0();

	 RC5rising = !RC5rising;

	 // timer around 889 uSec
	 if (timer > 700 && timer < 1100 && messageLocation != 13) {
	 RC5middle = !RC5middle;
	 }

	 if (RC5rising && RC5middle) {
	 message |= 1 << messageLocation--;
	 } else if (!RC5rising && RC5middle) {
	 message &= ~(1 << messageLocation--);
	 }

	 if (messageLocation == -1) {
	 // invert message since IR receiver is inverted
	 int command = getCommand(message) - 1;

	 test[commandCount] = command;
	 commandCount++;

	 //sleep(1);
	 interrupt = 0;
	 messageLocation = 13;
	 RC5rising = 0;
	 RC5middle = 1;
	 message = 0x0000;
	 }

	 interrupt++;

	 // Reset Interrupt
	 IO2IntClr |= (1 << 6);
	 __asm("nop");
	 __asm("nop");
	 //# end reset
	 resetTimer0();*/
}

int getCommand(int pos){
	return realCommands[pos];
}

