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
	readTime(array, 0x00);
//	delay(20);
	//Add 0s at the start if the number is below 10
	if(array[2] < 10){
		sprintf(buff2, "0%d", array[2]);
	} else {
		sprintf(buff2, "%d", array[2]);
	}

	if(array[1] < 10){
		sprintf(buff1, "0%d", array[1]);
	} else {
		sprintf(buff1, "%d", array[1]);
	}

	if(lastValues[2] < 10){
		sprintf(lvbuff2, "0%d", lastValues[2]);
	} else {
		sprintf(lvbuff2, "%d", lastValues[2]);
	}

	if(lastValues[1] < 10){
		sprintf(lvbuff1, "0%d", lastValues[1]);
	} else {
		sprintf(lvbuff1, "%d", lastValues[1]);
	}

	//Pretty much validates what was read from the RTC to be reasonable values
	if((array[2] == lastValues[2] + 1 ) || array[2] == 0){
		if((array[1] == lastValues[1] + 1) || array[1] == 0){
			sprintf(tmp, "%s:%s", buff2, buff1);
			lastValues[1] = array[1];
			lastValues[2] = array[2];
		} else {
			sprintf(tmp, "%s:%s", buff1, lvbuff1);
			lastValues[2] = array[2];
		}
	} else {
		if((array[1] == lastValues[1] + 1) || array[1] == 0){
			sprintf(tmp, "%s:%s", lvbuff2, buff1);
			lastValues[1] = array[1];
		} else {
			sprintf(tmp, "%s:%s", lvbuff2, lvbuff1);
		}
	}

	lastValues[0] = array[0];


	setOutput(tmp);
	RICONTROL |= 0x1;
}
