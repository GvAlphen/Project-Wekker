/*
 * states.h
 *
 *  Created on: 14 okt. 2014
 *      Author: Thomas
 */

#ifndef STATES_H_
#define STATES_H_

#include <stdlib.h>
#include <string.h>

#include "RC5.h"
#include "RTC.h"
#include "RIT.h"
#include "somGenerator.h"
#include "display.h"
#include "Alarm.h"
#include "Project_Microcontrollers_NSH.h"

void alarmState();
void addAlarmState();
void toggleAlarmState(char alarmBit);
void setTimeState();

void makeRTCFormat(int *hours,int *mins);

#endif /* STATES_H_ */
