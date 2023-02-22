/*
 * bitmap.h
 *
 *	Bitmaps declaration of every thing displayed on the LT24 LCD.
 *
 *  Created on: 15 May 2022
 *      Author: linri
 */

#ifndef BITMAP_BITMAP_H_
#define BITMAP_BITMAP_H_


//declare background bitmap
extern const unsigned short bg1 [76800]; //240*320
extern const unsigned short bg2 [76800];
extern const unsigned short bg3 [76800];
extern const unsigned short bg4 [76800];

//declare introduce bitmap
extern const unsigned short intro[76800];//240*320

//declare gameover bitmap
extern const unsigned short gameover[76800];//240*320

//declare plane bitmap
extern const unsigned short planestatic[1656];//36*46
extern const unsigned short planefront[1656];//36*46

//declare enermy bitmap
extern const unsigned short enemyfly[1476];//36*41

//declare bomp bitmap
extern const unsigned short bombshoot[260];//10*26

//declare blast bitmap
extern const unsigned short blast1[1920];//40*48
extern const unsigned short blast2[1575];//45*35
extern const unsigned short blast3[1750];//50*35
extern const unsigned short blast4[1485];//45*33
extern const unsigned short blast5[770];//35*22
#endif /* BITMAP_BITMAP_H_ */
