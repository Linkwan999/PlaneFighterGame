/*
 * SevenSeg.h
 *
 *	Seven-Segment Display Driver
 *
 *  Created on: 31 Mar 2022
 *   	Author: Riju Lin | Based on Unit 1 Assignment.
 */

#ifndef SEVENSEG_H_
#define SEVENSEG_H_

//Declaration of the function for 7-segment display
void SevenSeg_Write(unsigned int display, unsigned char value);

void SevenSeg_Single(unsigned int display, unsigned int value);

void SevenSeg_Double(unsigned int display, unsigned int value);

void SevenSeg_SingleAlpha(unsigned int display, unsigned int value);

#endif /* SEVENSEG_H_ */
