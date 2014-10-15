#include "Display.h"

#include <stdlib.h>


// Hreset hoog
// Hdata hoog
// 25 * HCLock hoog
// Hsto togglen
// VClock toggle
// Vreset toggle
//


void test(){
	int x;
	FIO0VAL |= (1 << 9); // Hreset hoog
	FIO0VAL |= (1 << 7); // Hdata hoog

	for(x = 0 ; x < 25 ; x++ ){// 25 Hclock toggle
		FIO0VAL |= (1 << 8);
		FIO0VAL |= (0 << 8);
	}

	FIO0VAL |= (1 << 6); // Hstorage toggle-high
	FIO0VAL |= (0 << 6);
}

//void vReset() { // pin 0
//	FIOSET0 = 0x01;
//	FIOCLR0 = 0x01;
//}
//
//void vClock() { // pin 2
//	FIOSET0 = 0x02;
//	FIOCLR0 = 0x02;
//}
//
//void hStorage() { // pin 6
//	FIOSET0 = 0x40;
//}
//
//void hData() { // pin 7
//	FIOSET0 = 0x80;
//	FIOCLR0 = 0x80;
//}
//
//void hClock() { // pin 8
//	FIOSET1 = 0x01;
//	FIOCLR1 = 0x01;
//}
//
//void hReset() { // pin 9
//	FIOCLR1 = 0x02;
//	hStorage();
//	FIOSET1 = 0x02;
//}

//void printRow(int input) {
//	unsigned int i = 0;
//	while(i <= input){
//		input >> hData();
//		i++;
//	}
//}

//void horizontalLeds() { //aansturen van de horizontale lijn
//	FIOPIN0 = 0xFFFF;
//	FIOPIN1 = 0xFFFF;
//
//	FIOSET0 = 1 << 7;
//	int x;
//	for(x = 0; x < 25; x++) {
//		FIOSET1 = 0x01;
//		FIOSET1 = 0x00;
//
//		hClock();
//	}
//	hStorage();
//}

//void klok() {
//	FIOCLR = 1;
//	FIOSET = 1;
//	FIODIR |= 0x01;
//	FIODIR |= 0x40;
//	FIODIR |= 0x02;
//}
