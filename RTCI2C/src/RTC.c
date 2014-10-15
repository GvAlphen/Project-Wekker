/*
 * RTC.c
 *
 *  Created on: 26 sep. 2014
 *      Author: Glennnn
 */
#include <stdio.h>
#include "RTC.h"

int bytesToSend = 0;
int bytesToReceive = 3;
unsigned char data[3];
unsigned char time[3];
int timePointer = 0;
int dataPointer = 0;
int reading = 0;
int dataRead = 0;
int rw = 0;
int regAdress = 0;

void initRTC()
{
	//PCONP |= 0x4000000; 	//i2c interface enables on reset -> bit 26 = 1
	ISER0 |= 0x1000;		//enable I2C2 interrupt
	PCLKSEL1 |=  0x300000; 	//peripheral clock selection for I2C2
	PINSEL0 |= 0xA00000;	//select SDA2 0.10, SCL2 0.11
	PINMODE0 |= 0xA00000;	//set as neither pull up/down
	PINMODE_OD0 |= 0xC00;	//set as open drain mode
//
	I2C2CONSET |= 0x40;		//bit 6 enable i2c interface

	I2SCLH = 0xA;
	I2SCLL = 0xA;
}

void initRTCzzz()
{
	PCONP |= 0x80000; 		//i2c interface enables on reset -> bit 19 = 1
	ISER0 |= 0x800;			//enable I2C2 interrupt
	PCLKSEL1 |=  0xC0; 		//peripheral clock selection for I2C2
	PINSEL0 |= 0xF;			//select SDA2 0.10, SCL2 0.11
	PINMODE0 |= 0xA;		//set as neither pull up/down
	PINMODE_OD0 |= 0x3;		//set as open drain mode

	I2C2CONSET |= 0x40;		//bit 6 enable i2c interface

	I2SCLH = 0xA;
	I2SCLL = 0xA;
}

void setMasterTransmitterMode()
{
	rw = 0;
	I2C2CONCLR = 0x2C;
	I2C2CONSET |= STA_FLAG; //set start flag
}

void readTime(int arr2[3], int adress)
{
	regAdress = adress;
	reading = 1;
	setMasterTransmitterMode();
	while (dataRead == 0)
	{

	}
	if (dataRead == 1)
	{
		showData();
		arr2[0] = BCDtoDec(0);
		arr2[1] = BCDtoDec(1);
		arr2[2] = BCDtoDec(2);
	}
}

void readRAM(int arr2[2], int adress)
{
	bytesToReceive = 3;
	reading = 1;
	regAdress = adress;
	setMasterTransmitterMode();
	while (dataRead == 0)
	{

	}
	if (dataRead == 1)
	{
		showData();
		arr2[0] = BCDtoDec(0);
		arr2[1] = BCDtoDec(1);
	}
}

void setTime(int secMinHour[3])
{
	bytesToSend = 3;
	time[0] = secMinHour[0];
	time[1] = secMinHour[1];
	time[2] = secMinHour[2];
	setMasterTransmitterMode();
}

void writeRAM(int minHourAlarm[3], int adress)
{
	regAdress = adress;
	bytesToSend = 3;
	time[0] = minHourAlarm[0];
	time[1] = minHourAlarm[1];
	time[2] = minHourAlarm[2];
	setMasterTransmitterMode();
}

void startCondition()
{
	I2C2CONSET |= STA_FLAG; 	//add start flag
}

void writeSlaveAdress()
{//RW 1 = read, 0 = write
	I2C2DAT = (0xD0 | rw);
}

void writeData(int dat)
{
	I2C2DAT = dat;
}

void showData()
{
	printf("%x\n", data[0]);
	printf("%x\n", data[1]);
	printf("%x\n", data[2]);
}

int BCDtoDec(int pointer)
{
	int returnTime = 0;
	returnTime += (data[pointer] & 0x0F);
	if (pointer < 2)
	{
		//data[pointer] >>= 4;
		returnTime += (((data[pointer] >> 4) & 0x7) * 10);
	}
	else
	{
		returnTime += (((data[pointer] >> 4) & 0x3) * 10);
	}
	return returnTime;
}

void I2C2_IRQHandler()
{
	//printf("%x\n", I2C2STAT);

	if (I2C2STAT == 0x00)
	{
		I2C2CONSET = 0x14;
		I2C2CONCLR = SI_FLAG;
	}

	if (I2C2STAT == 0x08)
	{//first start condition
		writeSlaveAdress();
		I2C2CONCLR = STA_FLAG | SI_FLAG; //clear start flag
	}

	else if (I2C2STAT == 0x10)
	{//repeated start condition
		writeSlaveAdress();
		I2C2CONCLR = STA_FLAG | SI_FLAG;
	}

	else if (I2C2STAT == 0x18)
	{//transmit first databyte

		I2C2DAT = regAdress; //reg adress
		//I2C2CONSET = STA_FLAG;
		I2C2CONCLR = SI_FLAG;
	}

	else if (I2C2STAT == 0x20)
	{//slave address+write transmitted, NOT ACK received.
		I2C2CONSET = 0x10;
		I2C2CONCLR = SI_FLAG; //clear start flag
	}

	else if (I2C2STAT == 0x28)
	{//transmit byte 2 and higher
		if (bytesToSend == 0)
		{
			if(reading == 1)
			{
				rw = 1;
				I2C2CONSET = STA_FLAG;
				I2C2CONCLR = ~STA_FLAG;
				I2C2CONCLR = SI_FLAG;
			}
			else
			{
				I2C2CONSET = 0x10; //stop
				I2C2CONCLR = SI_FLAG;
			}
		}
		else
		{
			writeData(time[timePointer]);
			timePointer++;
			bytesToSend--;
			I2C2CONCLR = SI_FLAG;
		}
	}
	else if (I2C2STAT == 0x30)
	{
		I2C2CONSET = 0x14;
		I2C2CONCLR = SI_FLAG;
	}

	else if (I2C2STAT == 0x38)
	{
		I2C2CONSET = 0x24;
		I2C2CONCLR = 0x08;
	}

/////////////////////////////////// receiver states
	else if (I2C2STAT == 0x40)
	{
		I2C2CONSET = 0x04;
		I2C2CONCLR = SI_FLAG;
		bytesToReceive--;
	}

	else if (I2C2STAT == 0x48)
	{
		I2C2CONSET = 0x14;
		I2C2CONCLR = SI_FLAG;
	}

	else if (I2C2STAT == 0x50)
	{
		data[dataPointer] = I2C2DAT;
		dataPointer++;
		bytesToReceive--;
		if (bytesToReceive == 0)
		{
			I2C2CONCLR = 0x0C;
		}
		else
		{
			I2C2CONSET = 0x04;
			I2C2CONCLR = SI_FLAG;
		}
	}

	else if (I2C2STAT == 0x58)
	{
		data[dataPointer] = I2C2DAT;
		I2C2CONSET = 0x14;
		I2C2CONCLR = SI_FLAG;
		dataRead = 1;
	}

	else{I2C2CONCLR = SI_FLAG;}
}

//1gnd 9sda1 10clk1
//14clk 15sda drhk dwn
