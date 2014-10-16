/*
 * Interrupts.h
 *
 *  Created on: 16 okt. 2014
 *      Author: Martijn
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#define ISER0 		(* (unsigned int *) 0xE000E100)
#define RICOMPVAL 	(* (unsigned int *) 0x400B0000)
#define RICONTROL 	(* (unsigned int *) 0x400B0008)

void initRIT();
void RIT_IRQHandler();

#endif /* INTERRUPTS_H_ */
