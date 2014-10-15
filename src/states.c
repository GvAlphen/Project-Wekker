/*
 * states.c
 *
 *  Created on: 14 okt. 2014
 *      Author: Thomas
 */

#include "states.h"

void alarmState(){
	char buff[2];
	char inputTotNuToe[100];
	int alarmCount = 1;

	char* strptr;
	strptr = generateSom();
	char som[30];
	strcpy(som, strptr);
	free(strptr);

	int answer = 9999;

	char antwoordOpSomStr[5];
	strncpy(antwoordOpSomStr, som+6, 5);
	int antwoordOpSom;
	antwoordOpSom = atoi(antwoordOpSomStr);

	int initialCommandCount;

	int inputTotNuToeInt;

	int newInput;

	while(answer != antwoordOpSom){
		//setAlarm(alarmCount);

		initialCommandCount = commandCount;

		while(commandCount == initialCommandCount){
			printToDisplay(som);
		}

		inputTotNuToeInt = getCommand(commandCount);
		sprintf(inputTotNuToe, "%d", inputTotNuToeInt);
		initialCommandCount = commandCount;

		//Change 9 to the value of an OK button
		while(getCommand(commandCount) != 9){
			printToDisplay(inputTotNuToe);
			if(commandCount != initialCommandCount){
				newInput = getCommand(commandCount);
				sprintf(buff, "%d", newInput);
				strcat(inputTotNuToe, buff);
				initialCommandCount = commandCount;
			}
		}
		answer = atoi(inputTotNuToe);
	}
}
