/*
 * Led__Matrix.c
 *
 * Created: 3/10/2020 1:21:36 PM
 * Author : sfazl001 Sameh Fazli 
 * Cs120b
 */ 

#include "Global.h"
#ifndef _LED_Matrix_H_
#define _LED_Matrix_H_
#include <stdio.h>
#include <stdlib.h>
static uint8_t i = 0;
static uint16_t k = 0;
static uint8_t STATE = 0;
enum LEDMatrix{display};

int Get_Num() {
	int num;
	num = (rand() % 11);
	return num;
}// Get_Num, random generator

int LED_Matrix(int state)
{
	switch(state)
	{
		case display:   // This big If and else statement, whole thing is able to display the LED Matrix.
		if(GameOn == 1)
		{
			if(STATE == 0)   {
				shift2Write(0xFF);
				shiftWrite(0x00);
				/*if(counter == 0)
				{
					Rand_Char = Get_Num();   // get Random Character
					Rand_Char2 = Get_Num();  // get Random Character
				}
				*/
				STATE = 1;
				++i;
			}
			else
			{
				if(matrixControl)   {
					shift2Write(0xFF & (~(l_list[j][i].row)) );
					shiftWrite(0x00 | (l_list[j][i].column));
				}
				STATE = 0;
			}
			if(i >= 8) // Iterates through all the lines
			{
				i = 0;
			}
			if(k < 500)  // Timer 
			{
				++k;
			}
			else
			{
				k=0;
				//if(j < 10)   // This is how many byte array of the LED Matrix that I have and which byte arrays that I want to print out
				//{
					/*if(counter == 0)
					{
						j = Rand_Char;
					}
					else if(counter == 1)
					{
						j = Rand_Char2;
					}
					*/
				//}
				//else
				//{
					//j = 0;	
				//}
			}
		}
		else
		{
			shift2Write(0xFF);
			shiftWrite(0x00);
		}
		break;
	}
	return state;
}

#endif
