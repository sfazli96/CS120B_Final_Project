/*
 * Global.c
 *
 * Created: 3/10/2020 9:58:44 PM
 * Author : sfazl001 Sameh Fazli 
 */ 

#ifndef _Global_H_
#define _Global_H_
#define TASK_SIZE 3
const unsigned long tasksPeriod = 3;
const unsigned char tasksSize = TASK_SIZE;
unsigned short Pressed = 0; // When the user presses one of the button on the SNES controller
unsigned short Pressed2 = 0; // When the user presses another button on the SNES controller
unsigned char counter = 0;
unsigned char Rand_Num;
unsigned char Rand_Num2;
unsigned short PressA;
unsigned char lives; // shows how many lives the user has in the game. 3 lives only
unsigned char time_counter = 0; // Time 
unsigned char GameOn;
unsigned char score = 0;
unsigned short UserInput; // We get the user input
unsigned short SNES_button; 


#endif
