/*
 * RC5.c
 *
 *  Created on: 7 okt. 2014
 *      Author: Martijn
 */

#include "RC5.h"
#include "timer.h"

static short message         = 0x0000;
static char  RC5rising       = 0;
static char  RC5middle       = 1;
static int   messageLocation = 13;

int command;

int interrupt = 0;

unsigned char getCommand(unsigned short message) {
	return message & 0x3F;
}
void initRC5(){
	//Set direction to input
	FIO2DIR0 &= ~(0xFFFF);
	//Enable External interrupt 3, at addres 21 of the ISER0 register
	ISER0 |= ( 1 << 21 );
	//Set the interrupt to be edge-sensitive for PIO2_6
	EXTMODE |= ( 1 << 0);
	//Enable Falling-Edge interrupt for PIO2_6
	IO2IntEnF |= ( 1 << 6);
	//Enable Rising-Edge interrupt for PIO2_6
	IO2IntEnR |= ( 1 << 6);
}

void EINT3_IRQHandler(){
	interrupt++;
	int timer = readTimer0();

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
		command = getCommand(message) - 1;

		sleep(1);
		messageLocation = 13;
		RC5rising       = 0;
		RC5middle       = 1;
		message         = 0x0000;
	}

	// Reset Interrupt
	IO2IntClr |= ( 1 << 6);
	__asm("nop");
	__asm("nop");
	//# end reset
	resetTimer0();

}



