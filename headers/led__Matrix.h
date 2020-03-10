/*
 * Led__Matrix.c
 *
 * Created: 3/10/2020 1:21:36 PM
 * Author : sfazl001 Sameh Fazli 
 */ 

#ifndef _LED_Matrix_H_
#define _LED_Matrix_H_
static uint8_t i = 0;
static uint8_t j = 0;
static uint16_t k = 0;
static uint8_t STATE = 0;
enum LEDMatrix{display};

int LED_Matrix(int state)
{
	switch(state)
	{
		case display:
		if(STATE == 0)
		{
			shift2Write(0xFF);
			shiftWrite(0x00);
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
			if(j < 9)
			{
				j++;
			}
			else
			{
				j = 0;
			}
		}
		break;
	}
	return state;
}

#endif
