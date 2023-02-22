# ELEC5620M Mini-Project Repository

This repository contains the project of a two-dimention fighter plane shooting game called "THUNDER ACTION". 
The project is based on the DE1-SoC board. This project including some peripherals like the A9 private timer, the
six seven-segment displays, LT24 LCD.

Game Functionality
--------------------

 In the plane shooting game, player will drive a yellow plane to shoot the enemy planes to stop the enemy plane
break though the blockade and avoid the collisions with enemy planes which two situations will make us Game Over.
The player plane will go right, left, up and down when the player presses the push button KEY0, KEY3, KEY2 and KEY1
respectively. And the plane will shoot the bullets and the LED0 will be lighted up as indicator light when the SW0 button
pushed high. The score displays on the LT24 LCD and the six seven-segments displays of the DE1-SoC. Players can play
the game in different backgrounds such as outer space, forest or rocks selected by the system casually. And KEY0 also
used to start the game in the introduction frame and restart the game in the game over frame.

File List
--------

The game including files and their description as below:


Filename	                |Description
---------------------	|-------------------------------------------------------------------------------------------------------------|
main.c	                |Program to control the top level functionality of the game. Control the input by KEY0-3, SW0, output to the LT24 LCD and seven-segment displays and process of the game by a state machine.  
gameProcess.c/h   	|All the functions about operation of the game.
framebuffer.c/h	|All the functions about interaction of the LT24 LCD and the framebuffer array.
Bitmap.h                  |Bitmaps of every thing displayed on the LT24 LCD. 
SevenSeg.c/h           |Perform the functionality of the seven segment LED displays.
DE1SoC_LT24.c/h     |LT24 LCD drive based on DE1SoC 
HPS_Watchdog.c/h  |Functions for resetting the watchdog and returning the value of watch dog


By Riju Lin

SID:201580350

University of Leeds