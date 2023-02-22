/*
 * framebuffer.c
 *
 *	All the functions about interaction of the LT24 LCD and the framebuffer array.
 *
 *
 *  Created on: 14 May 2022
 *      Author: linri
 */

#include "FrameBuffer.h"

//Function used to show the background in the screen
void FrameBuffer_background(unsigned short* frameBuffer, const unsigned short* background) {
	unsigned int index;
	//Copy the value of background bitmap to the framebuffer
	for (index = 0; index < 76800; index++){
		frameBuffer[index] = background [index];
	}
}


//Function used to draw object in the right position of the screen
void FrameBuffer_map(unsigned short* frameBuffer, const unsigned short* object, unsigned int xStart, unsigned int yStart, unsigned int width, unsigned height){
	//Vatiables for object coordinates and index and frameBuffer coordinates and index
	unsigned int  xEnd, yEnd, xCor, yCor, frameBufferIndex, objectIndex;

	//Find the exactly coordinates of the object
	xEnd = xStart + width - 1;
	yEnd = yStart + height - 1;
	//Make sure the object in the screen
	if(xEnd > 239) xEnd = 239;
	if(yEnd > 319) yEnd = 319;
	//Find out the index of each pixel in object and copy the value into
	//the corresponding position in frameBuffer
	for(yCor = yStart; yCor <= yEnd; yCor++){
		for(xCor = xStart; xCor <= xEnd; xCor++){
			frameBufferIndex = xCor + (yCor * 240);
			objectIndex = (xCor - xStart) + (yCor - yStart) * width;
			if(object[objectIndex] != 0xFFFF){
				frameBuffer[frameBufferIndex] = object[objectIndex];
			}
		}
	}
}

//Function used to draw the score on the screen
void FrameBuffer_score(unsigned short* frameBuffer, int score, unsigned int size, unsigned int colour, unsigned int xStart, unsigned int yStart){
	 //array of the score bitmap max size 5 (5 * 5 * 8 * 5 = 1000)
	 unsigned short scoreBitmap[1000];
	 char scoreArr[12], digitArr[1];
	 int digit,i;
	 //add "Score:   " to array
	 strncpy(scoreArr,"Score:",7);
	 //fingd all digits of the score
	 digit = score / 100;
	 digitArr[0] = digit + '0';   //convert digit to ASCII
	 strcat(scoreArr,digitArr);  //add the digit number after Score: to display
	 digit = score / 10;
	 digitArr[0] = digit + '0';
	 strcat(scoreArr,digitArr);
	 digit = score % 10;
	 digitArr[0] = digit + '0';
	 strcat(scoreArr,digitArr);
	 //convert all characters to bitmap and then draw them into the screen
	 for(i = 0; scoreArr[i] != '\0'; i++){
	 	FrameBuffer_font(scoreBitmap, scoreArr[i], size, colour);
	 	FrameBuffer_map(frameBuffer, scoreBitmap, xStart + (i * size * 6), yStart, 5 * size, 8 * size);
	 }
}

//Function used to draw introduction on the screen
void FrameBuffer_PressKEY0(unsigned short* frameBuffer, unsigned int size, unsigned int colour, unsigned int xStart, unsigned int yStart){
	 unsigned short bitmap[1000];
	 char string[14];
	 int i;
	 //add to array
	 strncpy(string,"Press KEY0 to",14);
	 //convert all characters to bitmap and then draw them into the screen
	  for(i = 0; string[i] != '\0'; i++){
	   FrameBuffer_font(bitmap,string[i],size,colour);
	   FrameBuffer_map(frameBuffer, bitmap, xStart + (i * size * 6), yStart, 5 * size, 8 * size);
	  }

}

//Function used to draw introduction on the screen
void FrameBuffer_start(unsigned short* frameBuffer, unsigned int size, unsigned int colour, unsigned int xStart, unsigned int yStart){
	unsigned short startBitmap[1000];
	char start[5];
	int i;
	//add to array
	 strncpy(start,"start",6);
	 //convert all characters to bitmap and then draw them into the screen
	 for(i = 0; start[i] != '\0'; i++){
	 	   FrameBuffer_font(startBitmap,start[i],size,colour);
	 	   FrameBuffer_map(frameBuffer, startBitmap, xStart + (i * size * 6), yStart, 5 * size, 8 * size);
	 	  }

}


//Function used to generate font bitmap of the characters
void FrameBuffer_font(unsigned short* bitmap, char letter, unsigned int size , unsigned short colour){
	 signed char a;
	 int x, y;
	 //make sure the size is not out of randge
	 if(size > 5){
	  size = 5;
	 }
	 else if(size < 1){
	  size = 1;
	 }
	 //find the correspending value of the letter in font map
	 for(x = 0; x < (5 * size); x++){
	  a = BF_fontMap[letter - ' '][x/size];
	  //covert the font map to bitmap
	  for(y = 0; y < (8 * size); y++){
	   if((a & 0x01) != 0x00){
		bitmap[(5 * size * y) + x] = colour;
	   }
	   else{
		bitmap[(5 * size * y) + x] = 0xFFFF;
	   }

	   if((y + 1) % size == 0){
		a = a >> 1;
	   }
	  }
	 }
}
