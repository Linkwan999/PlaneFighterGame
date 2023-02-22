/*
 * GameProcess.h
 *
 * All the functions about operation of the game.
 *
 *
 *  Created on: 15 May 2022
 *      Author: linri
 */

#ifndef GAMEPROCESS_GAMEPROCESS_H_
#define GAMEPROCESS_GAMEPROCESS_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "../Bitmap/bitmap.h"


#define enemyNum 30
#define bombNum 20


//use the key address declared in other place (KEY0-3)
extern volatile unsigned int *key_ptr;
//use the switch address declared in other place(KEY0-9)
extern volatile unsigned int *switch_ptr;

//create struct object with coordinates, speed and Id
typedef struct object{
	signed int x, y, width, height;
	//for bitmap
	const unsigned short* Id;
	//for whether exit on the screen
	bool flag;
	//for explosion process
	bool explosion;
} Object;
//use the score declared in other place
extern unsigned int score;

//Function used to initialise the value of plane
void gameProcess_PlaneInit(Object* plane);
//Function used to manage the move of the plane
void gameProcess_movePlane(Object* plane,Object*enemy);
//Function to initialise the enemy
void gameProcess_EnemyInit(Object* enemy);
//Function to create enemies
void gameProcess_creatEnemy(Object* enemy);
//Function to control the move of enemies
void gameProcess_moveEnemy(Object* enemy);
//Function to create bombs
void gameProcess_BombInit(Object*);
//Function to create bombs
void gameProcess_createBomb(Object* bomb, Object* plane);
//Function to bomb movement
void gameProcess_moveBomb(Object* bomb);
//Function to check collison
void gameProcess_collison(Object* plane, Object* enemy);
//Function used to the explosion animation
void gameProcess_explosion(Object* object);
//Function to clear the bombs and enemy planes
void gameProcess_clear(Object* object);
//Function to check whether the bombs hit the enemy plane
unsigned int gameProcess_bombEnemy(Object* bomb, Object* enemy, unsigned score);
//Function to find whether game over
int gameProcess_gameover(Object* plane, Object* enemy);

#endif /* GAMEPROCESS_GAMEPROCESS_H_ */
