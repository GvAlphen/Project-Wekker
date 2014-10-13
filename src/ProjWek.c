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
	char buff[30];
	int tmp;
	initDisplay();
//	initSomGenerator();
	initTimer0();
	initRC5();
	resetTimer0();

//	char* strptr;
//	char banaan[10];
//	int a;
//	strptr = generateSom();
//
//	strcpy(banaan, strptr);
//	free(strptr);

	//printf(banaan);
	clear();
	while (1) {
		if(commandCount > 5){
			tmp = getCommand(commandCount - 1);
			sprintf(buff, "%d%d%d%d%d", tmp, tmp, tmp, tmp, tmp);
			printToDisplay(buff);
		}
	}
	return 0;
}
