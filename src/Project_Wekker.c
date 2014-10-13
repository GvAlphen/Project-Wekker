/*
 * Project_Wekker.c
 *
 *  Created on: 9 okt. 2014
 *      Author: Martijn
 */


/*
 ===============================================================================
 Name : Project_Microcontroller_MT.c
 Author : $(author)
 Version :
 Copyright : $(copyright)
 Description : main definition
 ===============================================================================
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <cr_section_macros.h>
#include <stdio.h>
// TODO: insert other include files here
#include "display.h"
#include "somGenerator.h"
#include "timer.h"
#include "RC5.h"
// TODO: insert other definitions and declarations here
int main(void) {
//	initDisplay();
//	initSomGenerator();
	initTimer0();
	resetTimer0();
	initRC5();

//	char* strptr;
//	char banaan[10];
//	int a;
//	strptr = generateSom();
//
//	strcpy(banaan, strptr);
//	free(strptr);

	//printf(banaan);

	while (1) {
		//printToDisplay(banaan);

	}
	return 0;
}
