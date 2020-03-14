/*
 * Global.c
 *
 * Created: 3/10/2020 9:58:44 PM
 * Author : sfazl001 Sameh Fazli 
 */ 

#ifndef _Global_H_
#define _Global_H_
#define TASK_SIZE 4
#define MESSAGE_SIZE 16 // Size of the message
const unsigned long tasksPeriod = 3;
const unsigned char tasksSize = TASK_SIZE;
unsigned char Pressed = 0; // When the user presses one of the button on the SNES controller
unsigned char Pressed2 = 0; // When the user presses another button on the SNES controller
unsigned char counter = 0; 
unsigned char Rand_Char; // Random characters of the letter on the matrix 
unsigned char Rand_Char2; // Random Characters of the letter on the matrix
unsigned short PressA;
unsigned char lives = 3; // shows how many lives the user has in the game. 3 lives only
unsigned char time_counter = 0; // Time 
unsigned char GameOn; // If the game is on it is 1, if it is off it will be 0
unsigned char score = 0;
unsigned char button;
unsigned char ValueOfSNES;
unsigned short UserInput; // We get the user input
unsigned char TextMessage[MESSAGE_SIZE + 1] = "Score:   Lives: "; // This is the Text Message that will display on the LCD Display
unsigned char matrixControl = 0;
//unsigned char ButtonCounterPresses = 0;
unsigned char ButtonPressed = 0;
uint8_t j = 0;

const unsigned char MatrixMap[10] = {'X', 'Y', 'A', 'B', 'L', 'R', 'U', 'D', 'l', 'r'};


#endif
