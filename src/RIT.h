/*
 * Interrupts.h
 *
 *  Created on: 16 okt. 2014
 *      Author: Martijn
 */

#ifndef RIT_H_
#define RIT_H_

#include "RTC.h"
#include "Project_Microcontrollers_NSH.h"
#include "timer.h"

#define PCONP 		(* (unsigned int *) 0x400FC0C4)
#define ISER0 		(* (unsigned int *) 0xE000E100)
#define RICOMPVAL 	(* (unsigned int *) 0x400B0000)
#define RICONTROL 	(* (unsigned int *) 0x400B0008)

extern int lastValues[3];

void initRIT();
void RIT_IRQHandler();

#endif /* RIT_H_ */
