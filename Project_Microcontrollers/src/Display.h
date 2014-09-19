/*
 * Display.h
 *
 *  Created on: 18 sep. 2014
 *      Author: Gebruiker
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define FIODIR0 (*(unsigned int*) 0x2009C000)
#define FIODIR1 (*(unsigned int*) 0x2009C001)
#define FIODIR2 (*(unsigned int*) 0x2009C002)
#define FIODIR3 (*(unsigned int*) 0x2009C003)
#define FIOSET0 (*(unsigned int*) 0x2009C018) // produces a HIGH lvl output: 1
#define FIOSET1 (*(unsigned int*) 0x2009C019)
#define FIOSET2 (*(unsigned int*) 0x2009C01A)
#define FIOSET3 (*(unsigned int*) 0x2009C01B)
#define FIOCLR0 (*(unsigned int*) 0x2009C01C) // produces a LOW lvl output: 0
#define FIOCLR1 (*(unsigned int*) 0x2009C01D)
#define FIOCLR2 (*(unsigned int*) 0x2009C01E)
#define FIOCLR3 (*(unsigned int*) 0x2009C01F)

//void vReset();
//void vClear();
//void hStorage();
//void hData();
//void hClock();
//void hReset();
void horizontalLeds();
//void verticalLeds();

#endif /* DISPLAY_H_ */
