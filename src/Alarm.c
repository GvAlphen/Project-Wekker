/*
 * Alarm.c
 *
 *  Created on: 15 okt. 2014
 *      Author: Martijn
 */

#include "Alarm.h"



void setAlarm(int alarmCount){

	switch(alarmCount){

	case 0:
				setPin(&FIOPIN0, A1, 0);
				setPin(&FIOPIN0, A2, 0);	break;

	case 1:		setPin(&FIOPIN0, A1, 0);
				setPin(&FIOPIN0, A2, 1);	break;

	case 2:		setPin(&FIOPIN0, A1, 1);
				setPin(&FIOPIN0, A2, 0);	break;

	case 3:		setPin(&FIOPIN0, A1, 1);
				setPin(&FIOPIN0, A2, 1);	break;

	default:	setPin(&FIOPIN0, A1, 1);
				setPin(&FIOPIN0, A2, 1);

	}

}
