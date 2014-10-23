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
#include <string.h>
// TODO: insert other include files here
#include "Project_Microcontrollers_NSH.h"
#include "display.h"
#include "somGenerator.h"
#include "timer.h"
#include "RC5.h"
#include "states.h"
#include "Alarm.h"
#include "RTC.h"
#include "RIT.h"

// TODO: insert other definitions and declarations here
char output[5];
char alarmTime[5] = "99:99";

int main(void) {
	int i;
	int buff1[2];
	int buff2[2];
	initDisplay();
	initTimer0();
	initRC5();
	resetTimer0();
	initRTC();
	initRIT();
	setPriorities();

	int lastAlarmToggle = 0;

	//Read stuff from RAM and put it in our program's variables
	char alarmBit;
	readAlarmBit(&alarmBit);

	int arr[2];
	readRAMtime(arr);
	alarmTime[0] = arr[1]/10 + '0';
	alarmTime[1] = arr[1]%10 + '0';
	alarmTime[2] = ':';
	alarmTime[3] = arr[0]/10 + '0';
	alarmTime[4] = arr[0]%10 + '0';

	int arr2[3];

 	readTime(arr2); // arr2[] = { sec , min, hour}

 	output[0] = (arr2[2] / 10) + '0';
 	output[1] = (arr2[2] % 10) + '0';
 	output[2] = ':';
 	output[3] = (arr2[1] / 10) + '0';
 	output[4] = (arr2[1] % 10) + '0';

	//Set the last known values in RIT.c
	lastValues[0] = arr2[0];
	lastValues[1] = arr2[1];
	lastValues[2] = arr2[2];

	//Give the RNG a seed to work with (sec * minutes * hours)
	initSomGenerator(arr2[0] * arr2[1] * arr2[2]);

	while (1) {

		//Main loop
		while (!isTimeForAlarm(alarmBit) && (getCommand(commandCount - 1) != 15 && getCommand(commandCount - 1) != 11 && getCommand(commandCount - 1) != 13)) {
			//Prints the current time
			printToDisplay(output);
		}

		if (getCommand(commandCount - 1) == 15) {
			addAlarmState();
		}

		if (getCommand(commandCount - 1) == 11 && commandCount != lastAlarmToggle) { // '11' needs to be replaced with an other number, because it's an temporary button

			alarmBit = !alarmBit;
			toggleAlarmState(alarmBit);
			lastAlarmToggle = commandCount;
			setAlarmBit(alarmBit);
			//Give the user some feedback
			for(i=0; i<200; i++){
				asm("nop");
				if(alarmBit == 1){
					printToDisplay("  +  ");
				} else {
					printToDisplay("  -  ");
				}
			}
		}

		if (isTimeForAlarm(alarmBit)) {
			alarmState();
			resetAlarmTime();
		}
		if (getCommand(commandCount - 1) == 13){ // AANPASSEN!!!!!!!
			setTimeState();
		}

		printToDisplay(output);

	}
	return 0;
}

void setOutput(char str[]) {
	int i;
	for (i = 0; i < 5; i++) {
		output[i] = str[i];
	}
}

void setAlarmTime(char str[]){
	int i;
	for (i = 0; i < 5; i++) {
		alarmTime[i] = str[i];
	}
}

int isTimeForAlarm(char alarmBit){
	int i;
	if(alarmBit == 1){
		for(i=0; i<5; i++){
			if(output[i] > alarmTime[i]){
				return 1;
			} else if(output[i] < alarmTime[i]){
				return 0;
			} else {

			}
		}
	} else {
		return 0;
	}

	//If we make it through here, the alarm time is the same as the actual time!
	return 1;
}

void resetAlarmTime(){
	alarmTime[0] = '9';
	alarmTime[1] = '9';
	alarmTime[2] = ':';
	alarmTime[3] = '9';
	alarmTime[4] = '9';
}

void setPriorities(){
	IPR3 |= ( 1 << 5);
	IPR5 |= ( 1 << 11);
	IPR7 |= ( 1 << 14);

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
