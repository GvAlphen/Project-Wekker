/*
 * RTC.h
 *
 *  Created on: 26 sep. 2014
 *      Author: Glennnn
 */

#ifndef RTC_H_
#define RTC_H_

#define I2C2CONSET	(*(unsigned int *)0x400A0000)
#define I2C2CONCLR	(*(unsigned int *)0x400A0018)
#define PCONP		(*(unsigned int *)0x400FC0C4)
#define PCLKSEL1	(*(unsigned int *)0x400FC1AC)
#define I2C2DAT		(*(unsigned int *)0x400A0008)
#define I2C2STAT	(*(unsigned int *)0x400A0004)
//#define I2C2DATA_BUFFER	(*(unsigned int *)0x400A002C)

#define PINSEL0		(*(unsigned int *)0x4002C000)
#define PINMODE0	(*(unsigned int *)0x4002C040)
#define PINMODE_OD0	(*(unsigned int *)0x4002C068)
#define I2SCLH		(*(unsigned int *)0x4005C010)
#define I2SCLL		(*(unsigned int *)0x4005C014)

#define ISER0		(*(unsigned int *)0xE000E100)

#define STA_FLAG	(1 << 5)
#define SI_FLAG 	(1 << 3)
#define ACK_FLAG	(1 << 2)

#define I2C1CONSET	(*(unsigned int *)0x4005C000)
#define I2C1CONCLR	(*(unsigned int *)0x4005C018)
#define I2C1DAT		(*(unsigned int *)0x4005C008)
#define I2C1STAT	(*(unsigned int *)0x4005C004)

void initRTC();
void startCondition();
void setMasterTransmitterMode();
void writeSlaveAdress();
void writeData();
void setTime(int SecMinHour[3]);
void showData();
void readTime(int arr2[3], int adress);
int BCDtoDec(int pointer);
void writeRAM(int minHourAlarm[3], int adress);
void readRAM(int arr2[3], int adress);

#endif /* RTC_H_ */
