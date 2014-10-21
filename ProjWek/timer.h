/*
 * timer.h
 *
 *  Created on: 8 okt. 2014
 *      Author: Thomas
 */

#ifndef TIMER_H_
#define TIMER_H_

#define T0CONTROLREG 	(*(unsigned int *) 0x40004004)
#define T0COUNTERREG 	(*(unsigned int *) 0x40004008)
#define T0PRESCALEREG	(*(unsigned int *) 0x4000400C)

#define T1CONTROLREG 	(*(unsigned int *) 0x40008004)
#define T1COUNTERREG 	(*(unsigned int *) 0x40008008)
#define T1PRESCALEREG	(*(unsigned int *) 0x4000800C)

void initTimer0();
unsigned short readTimer0();
void resetTimer0();
void timer0Off();

void initTimer1();
unsigned short readTimer1();
void resetTimer1();

void delay(int units);
void sleep(int sec);

#endif /* TIMER_H_ */
