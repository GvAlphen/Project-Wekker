/*
 * timer.c
 *
 *  Created on: 8 okt. 2014
 *      Author: Thomas
 */
#include "timer.h"

void initTimer0(){
	//Turn on Timer
	T0CONTROLREG |= 0x1;
	//Set prescale
	T0PRESCALEREG = 3;
}

void resetTimer0(){
	T0CONTROLREG |= 0x2;
	asm("nop");
	T0CONTROLREG &= ~0x2;
}

int readTimer0(){
	int a = T0COUNTERREG;
	return a;
}


