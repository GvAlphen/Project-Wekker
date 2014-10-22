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
#include "somGenerator.h"
#include "display.h"
#include "Alarm.h"
#include "Project_Microcontrollers_NSH.h"

void alarmState();
void addAlarmState();
void toggleAlarmState(char alarmBit);
#endif /* STATES_H_ */
