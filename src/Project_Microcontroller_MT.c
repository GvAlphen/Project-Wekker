/*
 ===============================================================================
 Name : Project_Microcontroller_MT.c
 Author : $(author)
 Version :
 Copyright : $(copyright)
 Description : main definition
 ===============================================================================
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <cr_section_macros.h>
#include <stdio.h>
// TODO: insert other include files here
#include "display.h"
#include "somGenerator.h"
// TODO: insert other definitions and declarations here
int main(void) {
	init();

	while (1) {
		printToDisplay("19:25");
	}
	return 0;
}
