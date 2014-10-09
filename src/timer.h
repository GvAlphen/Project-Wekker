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

void initTimer0();
int readTimer0();
void resetTimer0();

#endif /* TIMER_H_ */
