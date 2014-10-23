/*
 * ProjWek.h
 *
 *  Created on: 16 okt. 2014
 *      Author: Martijn
 */

#ifndef PROJWEK_H_
#define PROJWEK_H_


#define IPR3 	(* (unsigned int *) 0xE000E40C)
#define IPR5 	(* (unsigned int *) 0xE000E414)
#define IPR7 	(* (unsigned int *) 0xE000E41C)

extern char output[5];
extern char alarmTime[5];

void setOutput(char str[]);
void setAlarmTime(char str[]);
int isTimeForAlarm(char alarmBit);
void resetAlarmTime();

void setPriorities();

#endif /* PROJWEK_H_ */
