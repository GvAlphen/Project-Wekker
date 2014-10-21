/*
 * states.c
 *
 *  Created on: 14 okt. 2014
 *      Author: Thomas
 */

#include "states.h"

void alarmState(){
	int i;

	char buff[2];
	char inputTotNuToe[100] = "";
	int alarmCount = 0;

	char* strptr;
	strptr = generateSom();
	char som[30];
	strcpy(som, strptr);
	free(strptr);

	int answer = 9999;

	char antwoordOpSomStr[6];
	strncpy(antwoordOpSomStr, som+6, 5);
	int antwoordOpSom;
	antwoordOpSom = atoi(antwoordOpSomStr);

	int initialCommandCount;
	int inputTotNuToeInt;
	int newInput;

	while(answer != antwoordOpSom){
		alarmCount++;
		setAlarm(alarmCount);

		initialCommandCount = commandCount;

		while(commandCount == initialCommandCount){
			printToDisplay(som);
		}

		inputTotNuToeInt = getCommand(commandCount - 1);
		sprintf(inputTotNuToe, "%d", inputTotNuToeInt);
		initialCommandCount = commandCount;

		//Change 9 to the value of an OK button
		while(getCommand(commandCount - 1) != 22){
			printToDisplay(inputTotNuToe);
			if(commandCount != initialCommandCount){
				if(getCommand(commandCount - 1) == 23){
					//Removes the last char
					inputTotNuToe[strlen(inputTotNuToe) - 1] = '\0';
					initialCommandCount = commandCount;
				} else if(getCommand(commandCount - 1) != 22) {
					newInput = getCommand(commandCount - 1);
					sprintf(buff, "%d", newInput);
					strcat(inputTotNuToe, buff);
					initialCommandCount = commandCount;
				} else {
					initialCommandCount = commandCount;
				}
			}
		}
		answer = atoi(inputTotNuToe);
		for(i=0; i<5; i++){
			inputTotNuToe[i] = '\0';
		}
	}
	setAlarm(0);
}

void addAlarmState(){
	int initialCommandCount;
	char hoursInput[20] = "";
	char minuteInput[20] = "";
	char toPrint[20] = "";
	char defToPrint[20] = "";

	//char inputTotNuToe[100] = "";
	int newInput;
	char buff[5];

	initialCommandCount = commandCount;

	while(commandCount == initialCommandCount){
		printToDisplay("00:00");
	}

	while(getCommand(commandCount - 1) != 22 || strlen(hoursInput) != 2){
		printToDisplay(hoursInput);
		if(commandCount != initialCommandCount){
			if(getCommand(commandCount - 1) == 23){
				//Removes the last char
				hoursInput[strlen(hoursInput) - 1] = '\0';
				initialCommandCount = commandCount;
			} else if(getCommand(commandCount - 1) != 22) {
				newInput = getCommand(commandCount - 1);
				sprintf(buff, "%d", newInput);
				strcat(hoursInput, buff);
				initialCommandCount = commandCount;
			} else {
				initialCommandCount = commandCount;
			}
		}
	}
	strcat(toPrint, hoursInput);
	strcat(toPrint, ":");
	strcpy(defToPrint, toPrint);

	while(getCommand(commandCount - 1) != 22 || strlen(minuteInput) != 2){
		printToDisplay(toPrint);
		if(commandCount != initialCommandCount){
			if(getCommand(commandCount - 1) == 23){
				//Removes the last char
				minuteInput[strlen(minuteInput) - 1] = '\0';
				strcpy(toPrint, defToPrint);
				strcat(toPrint, minuteInput);
				initialCommandCount = commandCount;
			} else if(getCommand(commandCount - 1) != 22) {
				newInput = getCommand(commandCount - 1);
				sprintf(buff, "%d", newInput);
				strcat(minuteInput, buff);
				strcpy(toPrint, defToPrint);
				strcat(toPrint, minuteInput);
				initialCommandCount = commandCount;
			} else {
				initialCommandCount = commandCount;
			}
		}
	}

	//User confirmed both inputs
	sprintf(buff, "%c%c:%c%c", hoursInput[0], hoursInput[1], minuteInput[0], minuteInput[1]);
	setAlarmTime(buff);
}

//Redundant
void toggleAlarmState(char alarmBit){ // RAM-addres for alarm; on/off is 0x10
	setAlarmBit(alarmBit);
}
