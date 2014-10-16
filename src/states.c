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
