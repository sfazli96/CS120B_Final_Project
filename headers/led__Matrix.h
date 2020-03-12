/*
 * Led__Matrix.c
 *
 * Created: 3/10/2020 1:21:36 PM
 * Author : sfazl001 Sameh Fazli 
 */ 

#include "Global.h"
#ifndef _LED_Matrix_H_
#define _LED_Matrix_H_
#include <stdio.h>
#include <stdlib.h>
static uint8_t i = 0;
static uint8_t j = 0;
static uint16_t k = 0;
static uint8_t STATE = 0;
enum LEDMatrix{display};

int Get_Num() {
	int num;
	num = (rand() % 11);
	return num;
}// Get_Num  

int LED_Matrix(int state)
{
	switch(state)
	{
		case display:
		if(GameOn == 1)
		{
			if(STATE == 0)   {
				shift2Write(0xFF);
				shiftWrite(0x00);
				if(counter == 0)
				{
					Rand_Num = Get_Num();
					Rand_Num2 = Get_Num();
				}
				STATE = 1;
				++i;
			}
			else
			{
				shift2Write(0xFF & (~(l_list[j][i].row)) );
				shiftWrite(0x00 | (l_list[j][i].column));
				STATE = 0;
			}
			if(i >= 8)
			{
				i = 0;
			}
			if(k < 500)
			{
				++k;
			}
			else
			{
				k=0;
				if(j < 10)
				{
					//j++;
					j = Get_Num(); // Generate random character 1 random character a specific time.
					Rand_Num = j;
					if(counter == 0)
					{
						j = Rand_Num;
					}
					else
					{
						j = Rand_Num2;
					}
				}
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
