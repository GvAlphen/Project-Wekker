#include "Display.h"
#include "Delay.h"

void vReset() { // pin 0
	FIOSET0 = 0x01;
	FIOCLR0 = 0x01;
}

void vClock() { // pin 2
	FIOSET0 = 0x02;
	FIOCLR0 = 0x02;
}

void hStorage() { // pin 6
	FIOSET0 = 0x40;
	FIOCLR0 = 0x40;
}

void hData() { // pin 7
	FIOSET0 = 0x80;
	FIOCLR0 = 0x80;
}

void hClock() { // pin 8
	FIOSET1 = 0x01;
	FIOCLR1 = 0x01;
}

void hReset() { // pin 9
	FIOSET1 = 0x02;
	FIOCLR1 = 0x02;
}

void horizontalLeds() {
	unsigned int i;
	vReset();
	hReset();
	 //aansturen van de horizontale lijn
	  while ( i < 7) {
		  hData();
		  hClock();
		  hStorage();
		  delay();
		  hReset();
		  vClock();
	      i++;
	  }
	  vReset();
}

//void klok() {
//	FIOCLR = 1;
//	FIOSET = 1;
//	FIODIR |= 0x01;
//	FIODIR |= 0x40;
//	FIODIR |= 0x02;
//}

/*
void verticalLeds() {
	//aansturing van verticale lijn
	   while ( i < 25 ) {
	       laad bit in;
	       i++;
	   }
	   reset teller;
	   laad alle 25 bits naar de output;
}
*/
