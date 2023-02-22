/*
 * main.c
 *
 *Program to control the top level functionality of the game.
 *
 *  Created on: 13 May 2022
 *      Author: linri
 */


#include "SevenSeg/SevenSeg.h"
#include "framebuffer/framebuffer.h"
#include "gameProcess/GameProcess.h"
#include "DE1SoC_LT24/DE1SoC_LT24.h"
#include "HPS_Watchdog/HPS_Watchdog.h"
#include "HPS_usleep/HPS_usleep.h"

//define the state
#define Intro 		0
#define Init 		1
#define Game		2
#define Gameover	3



//Pointer to  switches address
volatile unsigned int *switch_ptr = (unsigned int *)0xFF200040;
//Pointer to  LEDs address
volatile unsigned int *LED_ptr = (unsigned int *)0xFF200000;
//Pointer to key button address
volatile unsigned int *key_ptr = (unsigned int *)0xFF200050;
//Pointer to key button edge address
volatile unsigned int *key_edge_ptr = (unsigned int *)0xFF20005C;
// ARM A9 Private Timer Load
volatile unsigned int *private_timer_load      = (unsigned int *) 0xFFFEC600;
// ARM A9 Private Timer Value
volatile unsigned int *private_timer_value     = (unsigned int *) 0xFFFEC604;
// ARM A9 Private Timer Control
volatile unsigned int *private_timer_control   = (unsigned int *) 0xFFFEC608;
// ARM A9 Private Timer Interrupt
volatile unsigned int *private_timer_interrupt = (unsigned int *) 0xFFFEC60C;

//Function to initialise the Timer
void Timer_initialise(void){
	//set the timer load value to the private timer load address
	//set for 1,000,000 times so it is 1s for each interrupt
	*private_timer_load = 0xFFFFFFFF;
	//set PRESCALAR time = 224, I = 0 , A = 1 ,E = 1 into private timer control address
	//set the prescaler = 224 for freq = 1MHz and enable the timer
	*private_timer_control = (224 << 8) | (0 << 2) | (1 << 1) | (1 << 0);
}

//Function to read the current private time value
unsigned int Timer_read(){
	return *private_timer_value;
}

// Function to clear inputs
// clears all set bits in the key edge register by writing 1 to them
void keyedge_clear(){
	int temp = *key_edge_ptr;
	*key_edge_ptr = temp;
}


//Function used to display the score on the 7-segment displays
void SevenSegDisplay(unsigned int score){
	SevenSeg_SingleAlpha(5,19);			//s
	SevenSeg_SingleAlpha(4,3);			//c
	SevenSeg_SingleAlpha(3,18);			//o
	SevenSeg_Single(2,score / 100);		//the hundreds digit
	SevenSeg_Double(0,score % 100);		//the tens and ones digit
}




int main(void){
	int flag = 1;
	int state = Intro;
	unsigned int score;
	unsigned short frameBuffer[76800];
	int i;
	int j;
	int over = 0;
	unsigned int lastTimerValueEnemy = 0;
	unsigned int lastTimerValueBomb = 0;
	unsigned int lastTimerValueExplosion = 0;
	unsigned int lastTimerValuePlane = 0;
	//enemy planes are emerged about every 1s
	const unsigned int requirePeriodEnemy = 1000000;
	//bombs are emerged about every 500ms
	const unsigned int requirePeriodBomb = 500000;
	//explosion bit map changed each 800ms
	const unsigned int requirePeriodExplosion = 800000;
	unsigned int currentTimer = 0;
	Object plane;
	Object enemy[enemyNum];
	Object bomb[bombNum];
	//initialise LT24
	LT24_initialise(0xFF200060, 0xFF200080);
	//initialise the private timer
	Timer_initialise();



	while(1){

		switch(state){
			//state of introduction page
			case Intro:
				//update the screen buffer
				FrameBuffer_background(frameBuffer, intro);
				FrameBuffer_PressKEY0(frameBuffer, 3, 0xDEFB, 10, 170);
				FrameBuffer_start(frameBuffer, 3, 0xDEFB, 85, 200);
				//copy the screen buffer to show on the screen
				LT24_copyFrameBuffer(frameBuffer, 0, 0, 240, 320);
				score = 0;
				//display the score by 7-segment displays
				SevenSegDisplay(score);
				//if KEY0 is pressed, start the game
				if(*key_edge_ptr & 0x01){
					state = Init;
					keyedge_clear();
				}

			break;
			//state of initialisation
			case Init:
				//weed and create random number for the background selection
				srand((unsigned int)time(NULL));
				j = rand() % 3;
				//initialise the place, enemies and bombs
				gameProcess_PlaneInit(&plane);
				gameProcess_EnemyInit(enemy);
				gameProcess_BombInit(bomb);
				state = Game;
			break;

			//start the game
			case Game:

				SevenSegDisplay(score);
				//set all ovjects move
				gameProcess_movePlane(&plane, enemy);
				gameProcess_moveEnemy(enemy);
				gameProcess_moveBomb(bomb);

				//select the background
				if(j == 0 ){
					FrameBuffer_background(frameBuffer, bg1);
				}
				else if(j == 1){
					FrameBuffer_background(frameBuffer, bg2);
				}
				else if(j == 2 ){
					FrameBuffer_background(frameBuffer, bg3);
				}
				else if(j == 3){
					FrameBuffer_background(frameBuffer, bg4);
				}
				//display the score on the screen
				FrameBuffer_score(frameBuffer, score, 2, 0xDEFB, 120, 3);

				//update the plane of player on the screen
				FrameBuffer_map(frameBuffer, plane.Id, plane.x, plane.y, 36, 46);
				if(flag){
					lastTimerValueEnemy = Timer_read();
					flag = 0;
				}
				//read current time
				currentTimer = Timer_read();
				//create an enemy about per 1s add a random range of 1s
				if(lastTimerValueEnemy - currentTimer >= requirePeriodEnemy + rand()%1000000){
					lastTimerValueEnemy = Timer_read();
					gameProcess_creatEnemy(enemy);

				}
				//uodate the enemy planes on the screen
				for(i = 0; i < bombNum; i++){
					if((enemy[i].flag) || (enemy[i].explosion)){
						FrameBuffer_map(frameBuffer, enemy[i].Id, enemy[i].x, enemy[i].y, 36, 41);
					}
				}

				//if button SW0 is pressed, shoot a bomb per 500ms
				if((*switch_ptr & 0x01) && (lastTimerValueBomb - currentTimer >= requirePeriodBomb)){
					lastTimerValueBomb = Timer_read();
					*LED_ptr = 0x01;
					gameProcess_createBomb(bomb, &plane);
				}
				else if(!(*switch_ptr & 0x01)){
					lastTimerValueBomb = Timer_read();
				}
				else if(*switch_ptr & 0x00){
					*LED_ptr = 0x00;
				}
				//update bombs on the screen
				for(i = 0; i < bombNum; i++){
					if(bomb[i].flag == true){
						FrameBuffer_map(frameBuffer, bomb[i].Id, bomb[i].x, bomb[i].y, 10, 26);
					}
				}
				//check collision
				gameProcess_collison(&plane, enemy);
				//check whether hit the target
				score = gameProcess_bombEnemy(bomb, enemy, score);
				//the explosion animation
				//every bitmap of explosion changed every 800ms
				for(i = 0; i < enemyNum; i++){
					if((enemy[i].explosion == true) && (lastTimerValueExplosion - currentTimer >= requirePeriodExplosion)){
						lastTimerValueExplosion = Timer_read();
						lastTimerValueExplosion = lastTimerValueExplosion - requirePeriodExplosion;
						gameProcess_explosion(&enemy[i]);

					}
				}
				if((plane.explosion == true) && (lastTimerValuePlane - currentTimer >= requirePeriodExplosion) ){
					lastTimerValuePlane = Timer_read();
					lastTimerValuePlane = lastTimerValuePlane - requirePeriodExplosion;
					gameProcess_explosion(&plane);
				}

				//update the screen
				LT24_copyFrameBuffer(frameBuffer, 0, 0, 240, 320);
				//if game over, to next state
				over = gameProcess_gameover(&plane, enemy);
				if(over){
					state = Gameover;
					over = 0;
					keyedge_clear();
				}
			break;
			//state of game over page
			case Gameover:
				//update the screen
				FrameBuffer_background(frameBuffer, gameover);
				FrameBuffer_score(frameBuffer, score, 2, 0xE384, 60, 190);
				LT24_copyFrameBuffer(frameBuffer, 0, 0, 240, 320);
				SevenSegDisplay(score);
				//if KEY0 is pressed, restart the game
				if(*key_edge_ptr & 0x01){
					state = Intro;
					keyedge_clear();
				}
			break;

		}
		//reset watchdog
		HPS_ResetWatchdog();

	}
}



