/*
 * display.h
 *
 *  Created on: 3 okt. 2014
 *      Author: Martijn
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define FIOPIN0 (*(unsigned int *) 0x2009C014)
#define FIODIR0 (*(unsigned int *) 0x2009C000)

#define H_RST 9
#define H_CLK 8
#define H_DTA 7
#define H_STO 6
#define V_RST 3
#define V_CLK 2

void sleep(int sec);
void setPin(unsigned int *reg, unsigned int pin, int status);
void initDisplay();
void clear();
void printRow(int data);

void fillRow(int char1[], int char2[], int char3[], int char4[], int char5[], int row);
void printToDisplay(char time[]);
int * getCase(char input);


#endif /* DISPLAY_H_ */
