/*
 * RTC.c
 *
 *  Created on: 26 sep. 2014
 *      Author: Glennnn
 */
#include <stdio.h>
#include "RTC.h"

int bytesToSend = 0;
int bytesToReceive = 0;
unsigned char receiveBuffer[3];
unsigned char transmitBuffer[3];
int transmitPointer = 0;
int receivePointer = 0;
int reading = 0;
int dataRead = 0;
int rw = 0;
int regAdress = 0;
int busy = 0;

void initRTC()
{
	//PCONP |= 0x4000000; 	//i2c interface enables on reset -> bit 26 = 1
	ISER0 |= 0x1000;		//enable I2C2 interrupt
	PCLKSEL1 |=  0x300000; 	//peripheral clock selection for I2C2
	PINSEL0 |= 0xA00000;	//select SDA2 0.10, SCL2 0.11
	PINMODE0 |= 0xA00000;	//set as neither pull up/down
	PINMODE_OD0 |= 0xC00;	//set as open drain mode

	I2C2CONSET |= 0x40;		//bit 6 enable i2c interface

	I2SCLH = 0xA;			//set clock pulse high time
	I2SCLL = 0xA;			//set clock pulse low time
}

void initRTCI2C1()
{
	PCONP |= 0x80000; 		//I2C1 interface enables on reset -> bit 19 = 1
	ISER0 |= 0x800;			//enable I2C1 interrupt
	PCLKSEL1 |=  0xC0; 		//peripheral clock selection for I2C1
	PINSEL0 |= 0xF;			//select SDA1 0.0, SCL1 0.1
	PINMODE0 |= 0xA;		//set as neither pull up/down
	PINMODE_OD0 |= 0x3;		//set as open drain mode

	I2C2CONSET |= 0x40;		//bit 6 enable I2C1 interface

	I2SCLH = 0xA;			//set clock pulse high time
	I2SCLL = 0xA;			//set clock pulse low time
}

void setMasterTransmitterMode()
{
	rw = 0;
	I2C2CONCLR = 0x2C;
	I2C2CONSET |= STA_FLAG; //set start flag
}

void setMasterReceiverMode()
{
	reading = 1;
	setMasterTransmitterMode();
}

void readTime(int arr2[3])
{
	while (busy == 1)
	{

	}
	if (busy == 0)
	{
		busy = 1;
		transmitPointer = 0;
		receivePointer = 0;
		bytesToSend = 0;

		bytesToReceive = 3;
		regAdress = 0x00;
		dataRead = 0;
		setMasterReceiverMode();
		while (dataRead == 0)
		{

		}
		if (dataRead == 1)
		{
			arr2[0] = BCDtoDec(0);
			arr2[1] = BCDtoDec(1);
			arr2[2] = BCDtoDec(2);
		}
	}
}

void readRAMtime(int arr2[2])
{
	while (busy == 1)
	{

	}
	if (busy == 0)
	{
		busy = 1;
		dataRead = 0;
		transmitPointer = 0;
		receivePointer = 0;
		bytesToSend = 0;

		bytesToReceive = 2;
		regAdress = 0x08;
		setMasterReceiverMode();
		while (dataRead == 0)
		{

		}
		if (dataRead == 1)
		{
			arr2[0] = BCDtoDec(0);
			receiveBuffer[1] = receiveBuffer[2];
			arr2[1] = BCDtoDec(2);
		}
	}
}

void readAlarmBit(char *alarmBit)
{
	while (busy == 1)
	{

	}
	if (busy == 0)
	{
		busy = 1;
		dataRead = 0;
		transmitPointer = 0;
		receivePointer = 0;
		bytesToSend = 0;

		bytesToReceive = 1;
		regAdress = 0x10;
		setMasterReceiverMode();

		while (dataRead == 0)
		{

		}
		if (dataRead == 1)
		{
			*alarmBit = receiveBuffer[0];
		}
	}
}

void setTime(int secMinHour[3])
{
	while (busy == 1)
	{

	}
	if (busy == 0)
	{
		busy = 1;
		reading = 0;
		transmitPointer = 0;
		receivePointer = 0;
		bytesToReceive = 0;

		bytesToSend = 3;
		regAdress = 0x00;
		transmitBuffer[0] = secMinHour[0];
		transmitBuffer[1] = secMinHour[1];
		transmitBuffer[2] = secMinHour[2];
		setMasterTransmitterMode();
	}
}

void setRAMtime(int minHour[2])
{
	while (busy == 1)
	{

	}
	if (busy == 0)
	{
		busy = 1;
		reading = 0;
		transmitPointer = 0;
		receivePointer = 0;
		bytesToReceive = 0;

		bytesToSend = 2;
		regAdress = 0x08;
		transmitBuffer[0] = minHour[0];
		transmitBuffer[1] = minHour[1];
		setMasterTransmitterMode();
	}
}

void setAlarmBit(char alarmBit)
{ // writes to RAM
	while (busy == 1)
	{

	}
	if (busy == 0)
	{
		busy = 1;
		reading = 0;
		transmitPointer = 0;
		receivePointer = 0;
		bytesToReceive = 0;

		bytesToSend = 1;
		regAdress = 0x10;
		transmitBuffer[0] = alarmBit;
		setMasterTransmitterMode();
	}
}

void writeSlaveAdress()
{//RW 1 = read, 0 = write
	I2C2DAT = (0xD0 | rw);
}

void writeByte(int byte)
{
	I2C2DAT = byte;
}

int BCDtoDec(int pointer)
{
	//if (data[pointer] > 0x3F)
	int returnTime = 0;
	returnTime += (receiveBuffer[pointer] & 0x0F);
	if (pointer < 2)
	{
		//data[pointer] >>= 4;
		returnTime += (((receiveBuffer[pointer] >> 4) & 0x7) * 10);
	}
	else
	{
		returnTime += (((receiveBuffer[pointer] >> 4) & 0x3) * 10);
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
	{//transmit first data byte

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
				busy = 0;
			}
		}
		else
		{
			writeByte(transmitBuffer[transmitPointer]);
			transmitPointer++;
			bytesToSend--;
			I2C2CONCLR = SI_FLAG;
		}
	}
	else if (I2C2STAT == 0x30)
	{//data transmitted, NOT ACK received
		I2C2CONSET = 0x14;
		I2C2CONCLR = SI_FLAG;
		busy = 0;
	}

	else if (I2C2STAT == 0x38)
	{//arbitration lost during transmission
		I2C2CONSET = 0x24;
		I2C2CONCLR = 0x08;
	}

/////////////////////////////////// receiver states
	else if (I2C2STAT == 0x40)
	{//slave address+read transmitted, ACK received
		I2C2CONSET = 0x04;
		I2C2CONCLR = SI_FLAG;
		bytesToReceive--;
	}

	else if (I2C2STAT == 0x48)
	{//slave address+read transmitted, NOT ACK received
		I2C2CONSET = 0x14;
		I2C2CONCLR = SI_FLAG;
		busy = 0;
	}

	else if (I2C2STAT == 0x50)
	{//data byte received, ACK returned
		receiveBuffer[receivePointer] = I2C2DAT;
		receivePointer++;
		bytesToReceive--;
		if (bytesToReceive < 1)
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
	{//last data byte received
		receiveBuffer[receivePointer] = I2C2DAT;
		I2C2CONSET = 0x14;
		I2C2CONCLR = SI_FLAG;
		dataRead = 1;
		busy = 0;
	}

	else{I2C2CONCLR = SI_FLAG;}
}

//1gnd 9sda1 10clk1
//14clk 15sda drhk dwn
