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
	T0PRESCALEREG = 0;
}

void timer0Off(){
	//Turn on Timer
	T0CONTROLREG &= ~0x0;
}

void resetTimer0(){
	T0CONTROLREG |= 0x2;
	delay(2);
	T0CONTROLREG &= ~0x2;
}

unsigned short readTimer0(){
	return T0COUNTERREG;
}

void initTimer1(){
	//Turn on Timer
	T1CONTROLREG |= 0x1;
	//Set prescale
	//MAAK HIER EEN GOEDE PRESCALE VAN VOOR HET SYSTEMATISCH UITLEZEN VAN DE RTC, DUDE
	T1PRESCALEREG = 0;
}

void resetTimer1(){
	T1CONTROLREG |= 0x2;
	delay(2);
	T1CONTROLREG &= ~0x2;
}

unsigned short readTimer1(){
	return T0COUNTERREG;
}

void delay(int units){
	int i;
	for(i=0; i<units; i++){
		asm("nop");
	}
}

void sleep(int sec){
	int i;
	for(i = sec*500; i>0;i--){
		 asm("nop");
	}
}

