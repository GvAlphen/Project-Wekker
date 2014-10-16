/*
 * Interrupts.c
 *
 *  Created on: 16 okt. 2014
 *      Author: Martijn
 */

#include "Interrupts.h"
#include <stdio.h>

void initRIT(){

	ISER0 |= (1 << 29);

	RICOMPVAL = 1000000;

//	RICONTROL |= (1 << 0);
	RICONTROL |= 0x1;
	RICONTROL |= 0x2;
	RICONTROL |= 0x4;

}

void RIT_IRQHandler(){




	printf("Hallo/n");
}
