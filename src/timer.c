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
	T0PRESCALEREG = 1;
}

void resetTimer0(){
	T0CONTROLREG |= 0x2;
	asm("nop");
	asm("nop");
	T0CONTROLREG &= ~0x2;
}

unsigned short readTimer0(){
	return T0COUNTERREG;
}

void sleep(int sec){
	int i;
	for(i = sec*500; i>0;i--){
		 asm("nop");
	}
}

