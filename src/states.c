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

	int toWrite[2];

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
		inputTotNuToe[0] = (inputTotNuToeInt / 10) + '0';
		inputTotNuToe[0] = (inputTotNuToeInt % 10) + '0';
		inputTotNuToe[1] = '\0';
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
					buff[0] = (newInput % 10) + '0';
					buff[1] = '\0';
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
	//Set the alarm time inside the RTC to an unreachable value
	toWrite[0] = 0x99;
	toWrite[1] = 0x99;

	setRAMtime(toWrite);

	setAlarm(0);
}

void addAlarmState(){
	int initialCommandCount;
	char hoursInput[20] = "";
	char minuteInput[20] = "";
	char toPrint[20] = "";
	char defToPrint[20] = "";

	int newInput;
	char buff[5];

	int hours;
	int minutes;
	int toWrite[2];

	initialCommandCount = commandCount;

	while(commandCount == initialCommandCount){
		printToDisplay("00:00");
	}

	while(getCommand(commandCount - 1) != 22 || strlen(hoursInput) != 2 || atoi(hoursInput) > 24){
		printToDisplay(hoursInput);
		if(commandCount != initialCommandCount){
			if(getCommand(commandCount - 1) == 23){
				//Removes the last char
				hoursInput[strlen(hoursInput) - 1] = '\0';
				initialCommandCount = commandCount;
			} else if(getCommand(commandCount - 1) != 22) {
				if(strlen(hoursInput) < 2){
					newInput = getCommand(commandCount - 1);
					buff[0] = (newInput % 10) + '0';
					buff[1] = '\0';
					strcat(hoursInput, buff);
				}
				initialCommandCount = commandCount;
			} else {
				initialCommandCount = commandCount;
			}
		}
	}
	strcat(toPrint, hoursInput);
	strcat(toPrint, ":");
	strcpy(defToPrint, toPrint);

	while(getCommand(commandCount - 1) != 22 || strlen(minuteInput) != 2 || atoi(minuteInput) > 60){
		printToDisplay(toPrint);
		if(commandCount != initialCommandCount){
			if(getCommand(commandCount - 1) == 23){
				//Removes the last char
				minuteInput[strlen(minuteInput) - 1] = '\0';
				strcpy(toPrint, defToPrint);
				strcat(toPrint, minuteInput);
				initialCommandCount = commandCount;
			} else if(getCommand(commandCount - 1) != 22) {
				if(strlen(minuteInput) < 2){
					newInput = getCommand(commandCount - 1);
					buff[0] = (newInput % 10) + '0';
					buff[1] = '\0';
					strcat(minuteInput, buff);
					strcpy(toPrint, defToPrint);
					strcat(toPrint, minuteInput);
				}
				initialCommandCount = commandCount;
			} else {
				initialCommandCount = commandCount;
			}
		}
	}

	//User confirmed both inputs!

	//Write it to the RTC
	hours = atoi(hoursInput);
	minutes = atoi(minuteInput);

	makeRTCFormat(&minutes, &hours);

	toWrite[0] = minutes;
	toWrite[1] = hours;

	setRAMtime(toWrite);

	//Write it to the local alarm variable(from main)
	buff[0] = hoursInput[0];
	buff[1] = hoursInput[1];
	buff[2] = ':';
	buff[3] = minuteInput[0];
	buff[4] = minuteInput[1];
	setAlarmTime(buff);
}


void toggleAlarmState(char alarmBit){ // RAM-addres for alarm; on/off is 0x10
	setAlarmBit(alarmBit);
}

void setTimeState(){

	int initialCommandCount;
		char hoursInput[20] = "";
		char minuteInput[20] = "";

		int hours;
		int minutes;

		char toPrint[20] = "";
		char defToPrint[20] = "";

		int newInput;
		char buff[5];
		int timeArray[3];

		initialCommandCount = commandCount;

		while(commandCount == initialCommandCount){
			printToDisplay("00:00");
		}

		while(getCommand(commandCount - 1) != 22 || strlen(hoursInput) != 2 || atoi(hoursInput) > 24){
			printToDisplay(hoursInput);
			if(commandCount != initialCommandCount){
				if(getCommand(commandCount - 1) == 23){
					//Removes the last char
					hoursInput[strlen(hoursInput) - 1] = '\0';
					initialCommandCount = commandCount;
				} else if(getCommand(commandCount - 1) != 22) {
					if(strlen(hoursInput) < 2){
						newInput = getCommand(commandCount - 1);
						buff[0] = (newInput % 10) + '0';
						buff[1] = '\0';
						strcat(hoursInput, buff);
					}
					initialCommandCount = commandCount;
				} else {
					initialCommandCount = commandCount;
				}
			}
		}

		strcat(toPrint, hoursInput);
		strcat(toPrint, ":");
		strcpy(defToPrint, toPrint);

		while(getCommand(commandCount - 1) != 22 || strlen(minuteInput) != 2 || atoi(minuteInput) > 60){
			printToDisplay(toPrint);
			if(commandCount != initialCommandCount){
				if(getCommand(commandCount - 1) == 23){
					//Removes the last char
					minuteInput[strlen(minuteInput) - 1] = '\0';
					strcpy(toPrint, defToPrint);
					strcat(toPrint, minuteInput);
					initialCommandCount = commandCount;
				} else if(getCommand(commandCount - 1) != 22) {
					if(strlen(minuteInput) < 2){
						newInput = getCommand(commandCount - 1);
						buff[0] = (newInput % 10) + '0';
						buff[1] = '\0';
						strcat(minuteInput, buff);
						strcpy(toPrint, defToPrint);
						strcat(toPrint, minuteInput);
					}
					initialCommandCount = commandCount;
				} else {
					initialCommandCount = commandCount;
				}
			}
		}

		hours = atoi(hoursInput);
		minutes = atoi(minuteInput);

		lastValues[0] = 0;
		lastValues[1] = minutes;
		lastValues[2] = hours;

		makeRTCFormat(&hours, &minutes);
		timeArray[0] = 0;
		timeArray[1] = minutes;
		timeArray[2] = hours;

		setTime(timeArray);

	// 	int arr[3] = {0x00, 0x00, 0x13};
	//	setTime(arr);
}

void makeRTCFormat(int *hours,int *mins){
        int tmp[2];

        tmp[0] = *hours / 10;
        tmp[1] = *hours % 10;

        *hours = tmp[0];
        *hours = *hours << 4;
        *hours |= tmp[1];

        tmp[0] = *mins / 10;
        tmp[1] = *mins % 10;

        *mins = tmp[0];
        *mins = *mins << 4;
        *mins |= tmp[1];
}
