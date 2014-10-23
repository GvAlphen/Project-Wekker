/*
 * Interrupts.c
 *
 *  Created on: 16 okt. 2014
 *      Author: Martijn
 */

#include "RIT.h"
#include <stdio.h>

int array[3] = {0x00, 0x00, 0x00};
int lastValues[3];


void initRIT(){
	PCONP |= (1 << 16);
	RICONTROL |= 0xF;// << 0);
	RICOMPVAL = 2500000;
	ISER0 |= (1 << 29);
}

void RIT_IRQHandler(){
	char tmp[5];
	char buff1[3];
	char buff2[3];
	char lvbuff1[3];
	char lvbuff2[3];
	delay(20);
	readTime(array);
//	delay(20);

	//Make the values from the array into 0 formatted strings
	buff2[0] = (array[2] / 10) + '0';
	buff2[1] = (array[2] % 10) + '0';
	buff2[2] = '\0';

	buff1[0] = (array[1] / 10) + '0';
	buff1[1] = (array[1] % 10) + '0';
	buff1[2] = '\0';

	lvbuff2[0] = (lastValues[2] / 10) + '0';
	lvbuff2[1] = (lastValues[2] % 10) + '0';
	lvbuff2[2] = '\0';

	lvbuff1[0] = (lastValues[1] / 10) + '0';
	lvbuff1[1] = (lastValues[1] % 10) + '0';
	lvbuff1[2] = '\0';

	//Pretty much validates what was read from the RTC to be reasonable values
	if((array[2] == lastValues[2] + 1 ) || array[2] == 0){
		if((array[1] == lastValues[1] + 1) || array[1] == 0){
			strcpy(tmp, buff2);
			strcat(tmp, ":");
			strcat(tmp, buff1);
			lastValues[1] = array[1];
			lastValues[2] = array[2];
		} else {
			//Was 1, 1 (Wrong?)
			strcpy(tmp, buff2);
			strcat(tmp, ":");
			strcat(tmp, lvbuff1);
			lastValues[2] = array[2];
		}
	} else {
		if((array[1] == lastValues[1] + 1) || array[1] == 0){
			strcpy(tmp, lvbuff2);
			strcat(tmp, ":");
			strcat(tmp, buff1);
			lastValues[1] = array[1];
		} else {
			strcpy(tmp, lvbuff2);
			strcat(tmp, ":");
			strcat(tmp, lvbuff1);
		}
	}

	lastValues[0] = array[0];


	setOutput(tmp);
	RICONTROL |= 0x1;
}
