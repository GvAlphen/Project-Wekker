/*
 * display.c

 *
 *  Created on: 3 okt. 2014
 *      Author: Martijn
 */
#include "display.h"

void sleep(int sec){
	int i;
	for(i = sec*500; i>0;i--){
		 asm("nop");
	}
}

void setPin( int *reg, int pin, int status){
	if(status){
		*reg = *reg |= (1<<pin);
	}else{
		*reg = *reg &=~ (1<<pin);
	}
}

void initDisplay() {
	FIOPIN0 = 0;
	FIODIR0 = 0xFFFF;
	setPin(&FIOPIN0, H_RST, 0);
	setPin(&FIOPIN0, V_RST, 1);
	setPin(&FIOPIN0, V_RST, 0);
	setPin(&FIOPIN0, H_RST, 1);
}

void clear() {
	setPin(&FIOPIN0, V_RST, 1);
	setPin(&FIOPIN0, V_RST, 0);
	setPin(&FIOPIN0, H_RST, 0);
	setPin(&FIOPIN0, H_RST, 1);
}

void printRow(int data) {
	setPin(&FIOPIN0, H_RST, 0);
	setPin(&FIOPIN0, H_RST, 1);
	int i;
	for (i = 0; i < 25; i++) {
		setPin(&FIOPIN0, H_DTA, !((data >> i) & 1));
		setPin(&FIOPIN0, H_CLK, 1);
		setPin(&FIOPIN0, H_CLK, 0);
	}
	setPin(&FIOPIN0, V_CLK, 1);
	setPin(&FIOPIN0, V_CLK, 0);
	setPin(&FIOPIN0, H_STO, 1);
	setPin(&FIOPIN0, H_STO, 0);
}

int ZERO[35] =
{0,1,1,1,0,
 1,0,0,0,1,
 1,0,0,0,1,
 1,0,0,0,1,
 1,0,0,0,1,
 1,0,0,0,1,
 0,1,1,1,0};

int ONE[35] =
{0,0,1,0,0,
 0,1,1,0,0,
 1,0,1,0,0,
 0,0,1,0,0,
 0,0,1,0,0,
 0,0,1,0,0,
 1,1,1,1,1};

int TWO[35] =
{0,1,1,1,0,
 1,0,0,0,1,
 0,0,0,0,1,
 0,0,0,1,0,
 0,0,1,0,0,
 0,1,0,0,0,
 1,1,1,1,1};

int THREE[35] =
{0,1,1,1,0,
 1,0,0,0,1,
 0,0,0,0,1,
 0,0,1,1,0,
 0,0,0,0,1,
 1,0,0,0,1,
 0,1,1,1,0};

int FOUR[35] =
{1,0,0,0,0,
 1,0,0,0,1,
 1,0,0,0,1,
 1,1,1,1,1,
 0,0,0,0,1,
 0,0,0,0,1,
 0,0,0,0,1};

int FIVE[35] =
{1,1,1,1,0,
 1,0,0,0,0,
 1,0,0,0,0,
 1,1,1,1,0,
 0,0,0,0,1,
 1,0,0,0,1,
 0,1,1,1,0};

int SIX[35] =
{0,1,1,1,0,
 1,0,0,0,0,
 1,0,0,0,0,
 1,1,1,1,0,
 1,0,0,0,1,
 1,0,0,0,1,
 0,1,1,1,0};

int SEVEN[35] =
{1,1,1,1,1,
 0,0,0,0,1,
 0,0,0,1,0,
 0,0,1,0,0,
 0,0,1,0,0,
 0,0,1,0,0,
 0,0,1,0,0};

int EIGHT[35] =
{0,1,1,1,0,
 1,0,0,0,1,
 1,0,0,0,1,
 0,1,1,1,0,
 1,0,0,0,1,
 1,0,0,0,1,
 0,1,1,1,0};

int NINE[35] =
{0,1,1,1,0,
 1,0,0,0,1,
 1,0,0,0,1,
 0,1,1,1,1,
 0,0,0,0,1,
 0,0,0,0,1,
 0,1,1,1,0};

int COLON[35] =
{0,0,0,0,0,
 0,0,1,0,0,
 0,0,1,0,0,
 0,0,0,0,0,
 0,0,1,0,0,
 0,0,1,0,0,
 0,0,0,0,0};

int PLUS[35] =
{0,0,0,0,0,
 0,0,1,0,0,
 0,0,1,0,0,
 1,1,1,1,1,
 0,0,1,0,0,
 0,0,1,0,0,
 0,0,0,0,0};

int MINUS[35] =
{0,0,0,0,0,
 0,0,0,0,0,
 0,0,0,0,0,
 0,1,1,1,0,
 0,0,0,0,0,
 0,0,0,0,0,
 0,0,0,0,0};

int DIVIDE[35] =
{0,0,0,0,0,
 0,0,0,0,1,
 0,0,0,1,0,
 0,0,1,0,0,
 0,1,0,0,0,
 1,0,0,0,0,
 0,0,0,0,0};

int MULTIPLY[35] =
{0,0,0,0,0,
 1,0,0,0,1,
 0,1,0,1,0,
 0,0,1,0,0,
 0,1,0,1,0,
 1,0,0,0,1,
 0,0,0,0,0};


void fillRow(int char1[], int char2[], int char3[], int char4[], int char5[], int row){
  int rows = 0;
  int x;
  int max = 5*row;
    for(x = (max - 5); x < max; x++){
      rows |= (char1[x] & 1);
      rows = (rows << 1);
    }
    for(x = (max - 5); x < max; x++){
      rows |= (char2[x] & 1);
      rows = (rows << 1);
    }
    for(x = (max - 5); x < max; x++){
      rows |= (char3[x] & 1);
      rows = (rows << 1);
    }
    for(x = (max - 5); x < max; x++){
      rows |= (char4[x] & 1);
      rows = (rows << 1);
    }
    for(x = (max - 5); x < max; x++){
      rows |= (char5[x] & 1);
      rows = (rows << 1);
    }
    rows = (rows >> 1);

    printRow(rows);
}

void printToDisplay(char time[]){ // "19:12"

	int row;
	for(row = 1 ; row <= 7 ; row++){
		fillRow(getCase(time[0]), getCase(time[1]), getCase(time[2]), getCase(time[3]), getCase(time[4]), row);
	}
	sleep(1);
	setPin(&FIOPIN0, V_RST, 1);
	setPin(&FIOPIN0, V_RST, 0);

}

int * getCase(char input){
	switch(input){
	case '0': 	return ZERO; 	break;
	case '1':	return ONE;  	break;
	case '2': 	return TWO;  	break;
	case '3': 	return THREE;	break;
	case '4': 	return FOUR; 	break;
	case '5':	return FIVE; 	break;
	case '6':	return SIX;  	break;
	case '7':	return SEVEN;	break;
	case '8': 	return EIGHT;	break;
	case '9':	return NINE; 	break;
	case ':':	return COLON;	break;
	case '/':   return DIVIDE; 	break;
	case '*': 	return MULTIPLY;break;
	case '-':   return MINUS;   break;
	case '+':   return PLUS;    break;
	}
}


