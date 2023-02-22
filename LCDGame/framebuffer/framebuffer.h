/*
 * framebuffer.h
 *
 *
 *  All the functions about interaction of the LT24 LCD and the framebuffer array.
 *
 *
 *  Created on: 14 May 2022
 *      Author: linri
 */

#ifndef FRAMEBUFFER_FRAMEBUFFER_H_
#define FRAMEBUFFER_FRAMEBUFFER_H_

#include <string.h>
#include <math.h>

#include "BasicFont/BasicFont.h"

//Function used to show the background in the screen
void FrameBuffer_background(unsigned short* frameBuffer, const unsigned short* background);
//Function used to draw object in the right position of the screen
void FrameBuffer_map(unsigned short* frameBuffer, const unsigned short* object, unsigned int xStart, unsigned int yStart, unsigned int width, unsigned height);
//Function used to draw the score on the screen
void FrameBuffer_score(unsigned short* frameBuffer, int score, unsigned int size, unsigned int colour, unsigned int xStart, unsigned int yStart);
//Function used to draw introduction on the screen
void FrameBuffer_PressKEY0(unsigned short* frameBuffer, unsigned int size, unsigned int colour, unsigned int xStart, unsigned int yStart);
void FrameBuffer_start(unsigned short* frameBuffer, unsigned int size, unsigned int colour, unsigned int xStart, unsigned int yStart);
//Function used to generate font bitmap of the characters
void FrameBuffer_font(unsigned short* bitmap, char letter, unsigned int size , unsigned short colour);
#endif /* FRAMEBUFFER_FRAMEBUFFER_H_ */
