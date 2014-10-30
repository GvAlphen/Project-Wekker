/*
 * Alarm.h
 *
 *  Created on: 15 okt. 2014
 *      Author: Martijn
 */

#ifndef ALARM_H_
#define ALARM_H_

#include "display.h"

#define FIOPIN0 (*(unsigned int *) 0x2009C014)
#define FIODIR0 (*(unsigned int *) 0x2009C000)

#define A1 		4
#define A2 		5

void setAlarm(int alarmCount);

#endif /* ALARM_H_ */
