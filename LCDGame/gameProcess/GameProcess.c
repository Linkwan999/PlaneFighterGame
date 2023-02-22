/*
 * GameProcess.c
 *
 * All the functions about operation of the game.
 *
 *
 *  Created on: 15 May 2022
 *      Author: linri
 */
#include "GameProcess.h"

#define verticalSpeed 15
#define horizonSpeed 15
#define maxHeight 80
#define bombSpeed 20

//Function used to initialise the value of plane
void gameProcess_PlaneInit(Object* plane){
	plane->x = 101;
	plane->y = 273;
	plane->width = 36;
	plane->height = 46;
	plane->Id = planestatic;
	plane->flag = true;
}

//Function used to manage the move of the plane
void gameProcess_movePlane(Object* plane, Object* enemy){
	//plane motion on in direction x and y direction
	if(*key_ptr & 0x08){
		plane->x = plane->x - horizonSpeed;
		plane->Id = planestatic;
	}
	else if(*key_ptr & 0x01){
		plane->x = plane->x + horizonSpeed;
		plane->Id = planestatic;
	}
	else if(*key_ptr & 0x04){
		plane->y = plane->y - verticalSpeed;
		plane->Id = planefront;
	}
	else if(*key_ptr & 0x02){
		plane->y = plane->y + verticalSpeed;
		plane->Id = planestatic;
	}
	//make sure the plane will not out of the screen and under the maximum height
	if(plane->x < 0) 			plane->x = 0;
	if(plane->x > 203)			plane->x = 203;
	if(plane->y < maxHeight) 	plane->y = maxHeight;
	if(plane->y > 273)			plane->y = 273;
	//check the plane whether collide with enemy planes
	gameProcess_collison(plane, enemy);
}


//Function to control the move of enemies
void gameProcess_moveEnemy(Object* enemy){
	int i;
	for(i = 0; i < enemyNum; i++){
		//if exit and not explode
		if((enemy[i].flag) && (enemy[i].explosion == false)){
			enemy[i].y = enemy[i].y + verticalSpeed;
			//if fly though the bottom, become not exit
			if(enemy[i].y > 319){
				enemy[i].flag = false;
			}
		}
	}
}



//Function to initialise the enemy
void gameProcess_EnemyInit(Object* enemy){
	int i;
	for(i = 0; i < enemyNum; i++){
		enemy[i].flag = false;
		enemy[i].explosion = false;
	}
}

//Function to create enemies
void gameProcess_creatEnemy(Object* enemy){
	int i;
	for(i = 0; i < enemyNum; i++){
			if(!(enemy[i].flag) && !(enemy[i].flag)){
				//enemies are emerged in the top of screen and random place of x direction
				srand((unsigned int)time(NULL));
				enemy[i].x = rand()%193;
				enemy[i].y = -41;
				enemy[i].width = 36;
				enemy[i].height = 41;
				enemy[i].Id = enemyfly;
				enemy[i].flag = true;
				enemy[i].explosion = false;
				break;
		}
	}
}

//Function to initialise bombs
void gameProcess_BombInit(Object* bomb){
	int i;
	for(i = 0; i< bombNum; i++){
		bomb[i].flag = false;
	}
}

//Function to create bombs
void gameProcess_createBomb(Object* bomb, Object* plane){
	int i;
	for(i = 0; i < bombNum; i++){
		if(bomb[i].flag == false)
		{
			bomb[i].flag = true;
			bomb[i].x = plane->x + 13;
			bomb[i].y = plane->y;
			bomb[i].width = 10;
			bomb[i].height = 26;
			bomb[i].Id = bombshoot;
			break;
		}

	}
}




//Function to bomb movement
void gameProcess_moveBomb(Object* bomb){
	int i;
	for(i = 0; i < bombNum; i++){
		if(bomb[i].flag ==true){
			bomb[i].y = bomb[i].y - bombSpeed;
			//when the bomb out of screen, take it back to use for unlimited bomb
			if(bomb[i].y < 0){
				bomb[i].flag = false;
			}
		}
	}
}

//Function to check collision
void gameProcess_collison(Object* plane, Object* enemy){
	int i;
	for(i = 0; i < enemyNum; i++)
	{
		//if the plane collides with any enemies
		if((enemy[i].flag == true) && (enemy[i].explosion == false) &&(plane->x + plane->width > enemy[i].x) && (plane->x < enemy[i].x + enemy[i].width)
		&&(plane->y < enemy[i].y + enemy[i].height) &&(plane->y + plane->height > enemy[i].y)){
			gameProcess_explosion(&enemy[i]);
			gameProcess_explosion(plane);
		}
	}
}

//Function used to the explosion animation
void gameProcess_explosion(Object* object){
	object->explosion = true;
	if((object->Id == enemyfly) || (object->Id == planestatic)|| (object->Id == planefront)){
		object->Id = blast1;
	}
	if(object->Id == blast1){
		object->Id = blast2;
		return;
	}
	if(object->Id == blast2){
		object->Id = blast3;
		return;
	}
	if(object->Id == blast3){
		object->Id = blast4;
		return;
	}
	if(object->Id == blast4){
		object->Id = blast5;
		return;
	}
	gameProcess_clear(object);
}

//Function to check whether the bombs hit the enemy plane
unsigned int gameProcess_bombEnemy(Object* bomb, Object* enemy, unsigned int score){
	int i ,j;
	for(i = 0; i < bombNum; i++)
	{
		for(j = 0; j < enemyNum; j ++){
			if((bomb[i].flag == true) && (enemy[j].flag == true) && (enemy[j].explosion ==false)&&(bomb[i].y < enemy[j].y + enemy[j].height)
			&& (bomb[i].x + bomb[i].width > enemy[j].x) && (bomb[i].x < enemy[j].x + enemy->width)){
				//hit the target, add the score
				score++;
				gameProcess_explosion(&enemy[j]);
				gameProcess_clear(&bomb[i]);
			}
		}
	}
	return score;
}

//Function to clear the bombs and enemy planes
void gameProcess_clear(Object* object){
	object->flag = false;
	object->explosion = false;
	object->x = -50;
	object->y = -50;
}

//Function to find whether game over
int gameProcess_gameover(Object* plane, Object* enemy){
	int i;
	//if the plane collide with enemy planes
	if(plane->flag == false){
		plane->flag = true;
		return 1;
	}
	//if the enemy planes go though the bottom of screen
	for(i = 0; i < enemyNum; i++){
		if(enemy[i].y == 319){
			gameProcess_clear(&enemy[i]);
			return 1;
		}
	}

	return 0;
}



