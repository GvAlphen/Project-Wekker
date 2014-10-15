/*
===============================================================================
 Name        : RTCI2C.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

#include "RTC.h"

int main(void) {

    volatile static int i = 0 ;

    initRTC();

    int arr[3] = {0x30,0x16,0x16};
    int arr2[3];
    int arr3[3] = {0x44, 0x22, 0x01};

  // setTime(arr);
  // readTime(arr2, 0x00);
 //  writeRAM(arr3, 0x08);
   readRAM(arr2, 0x08);
    while(1) {
        i++;
    }
    return 0 ;
}

