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
#include "states.h"
#include "Alarm.h"
#include "RTC.h"
#include "Interrupts.h"

// TODO: insert other definitions and declarations here


int main(void) {

	char output[5];

	initDisplay();
	initSomGenerator();
	initTimer0();
	initRC5();
	resetTimer0();
	initRTC();
	initRIT();

	clear();


	int arr2[3];
	int arr[3] = {0x00, 0x50, 0x11};
//	setTime(arr);
    readTime(arr2, 0x00);


//    printf("%d\n", arr2[0]);
//    printf("%d\n", arr2[1]);
//    printf("%d\n", arr2[2]);

    sprintf(output, "%d:%d", arr2[2], arr2[1]);

	while (1) {

		printToDisplay(output);


/*		if(initialCommandCount != commandCount){
			sprintf(output, "%d", getCommand(commandCount - 1));

			initialCommandCount = commandCount;
		}

		printToDisplay(output);*/
	}
	return 0;
}

//initRTC();
//
//int arr[3] = {0x30,0x16,0x16};
//int arr2[2];
//int arr3[3] = {0x44, 0x22, 0x01};
//
//// setTime(arr);
//readTime(arr2, 0x01);
////  writeRAM(arr3, 0x08);
//readRAM(arr2, 0x08);


/*		if(commandCount > 5){
			tmp = getCommand(commandCount - 1);
			sprintf(buff, "%d%d%d%d%d", tmp, tmp, tmp, tmp, tmp);
			printToDisplay(buff);
		}*/
