/*
 * RC5.h
 *
 *  Created on: 7 okt. 2014
 *      Author: Martijn
 */

#ifndef RC5_H_
#define RC5_H_

#define FIO2DIR0 	(* (unsigned int *) 0x2009C040)
#define ISER0 		(* (unsigned int *) 0xE000E100)
#define EXTMODE 	(* (unsigned int *) 0x400FC148)
#define IO2IntEnR 	(* (unsigned int *) 0x400280B0)
#define IO2IntEnF 	(* (unsigned int *) 0x400280B4)
#define IO2IntClr 	(* (unsigned int *) 0x400280AC)

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

void initRC5();
void EINT0_IRQHandler();
void EINT1_IRQHandler();
void EINT2_IRQHandler();
void EINT3_IRQHandler();
#endif /* RC5_H_ */
