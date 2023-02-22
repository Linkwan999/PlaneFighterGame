/*
 * SevenSeg.c
 *
 *	7-Segment Display Driver
 *
 *  Created on: 31 Mar 2022
 *   	Author: Riju Lin | Based on Unit 1 Assignment.
 */

#include "SevenSeg.h"


//Pointers to seven-segment peripherals
volatile unsigned char *SevenSeg_lo_ptr = (unsigned char *) 0xFF200020;
volatile unsigned char *SevenSeg_hi_ptr = (unsigned char *) 0xFF200030;

//There are four displays in low address
#define SEVENSEG_LO 4
//There are two displays in high address
#define SEVENSEG_HI 2

//To take the correspond value to display lightened up in 0,1,2,3,4,5,6,7,8,9 respectively
char table[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

//Function used to write the value to the address
void SevenSeg_Write(unsigned int display, unsigned char value){
	if(display < SEVENSEG_LO)
	{
		SevenSeg_lo_ptr[display] = value;
	}
	else
	{
		display = display - SEVENSEG_LO;
		SevenSeg_hi_ptr[display] = value;
	}
}

//Function to display the single value
void SevenSeg_Single(unsigned int display, unsigned int value){
		SevenSeg_Write(display,table[value]);

}

//Function to display the double values
void SevenSeg_Double(unsigned int display, unsigned int value){
	unsigned int a = 0, b = 0;
	a = value % 10;		//get the value in the one's place
	b = value / 10;		//get the value in the ten's place
	SevenSeg_Single(display,a);
	SevenSeg_Single(display+1,b);

}


//Function to display the single alphabetical (A-Z) value
void SevenSeg_SingleAlpha(unsigned int display, unsigned int value) {
	//Array to store "-" in value 0 and "A-Z" from value 1 to 26
	int aphArray[27] = {0x40 ,0x5F, 0x79, 0x58, 0x5E, 0x7B, 0x71, 0x6F, 0x74, 0x06, 0x0E, 0x40, 0x38, 0x40, 0x54, 0x5C, 0x73, 0x67, 0x50, 0x6D, 0x78, 0x1C, 0x1C, 0x40, 0x76, 0x6E, 0x5B};
	//If value in input range, out put the corresponding alphabetical value, else output "-"
	if(value < 26){
		value = aphArray[value];
	}
	else{
		value = aphArray[0];
	}
	SevenSeg_Write(display,value);
}

