#include <avr/io.h>
#include "shiftregister_columns.h"
#include "shiftRegister_Rows.h"
#include "timer.h"
#include "io.c"
#include "bit.h"
//#include "snes.c"
#include "scheduler.h"

#ifdef _SIMULATE_
#endif

typedef struct _lights
{
	uint8_t row;
	uint8_t column;
} lights;

const lights l_list[][8] =
{
	/*
	{
		{0x81, 0x01},
		{0x42, 0x02},
		{0x24, 0x04},
		{0x18, 0x08},
		{0x18, 0x10}, // Change only left side for the matrix, so i can make the letter of X.
		{0x24, 0x20}, // Same thing
		{0x42, 0x40},
		{0x81, 0x80}
	},
	*/
	
	// This will make the Letter Y.
	/*{
		{0x01, 0x01},
		{0x02, 0x02},
		{0x04, 0x04},
		{0x08, 0x08},
		{0x18, 0x10}, // Change only left side for the matrix, so i can make the letter of Y.
		{0x24, 0x20}, // Same thing
		{0x42, 0x40},
		{0x81, 0x80}
	},
	*/
	
	// This is for the Letter that prints out A.
	/*{
		{0x42, 0x01},
		{0x42, 0x02},
		{0x42, 0x04},
		{0x42, 0x08},
		{0x7E, 0x10}, // Change only left side for the matrix
		{0x42, 0x20}, // Same thing
		{0x42, 0x40},
		{0x3C, 0x80}
	},
	*/
	// This is for the Letter that prints out B.
	{
		{0x3E, 0x01},
		{0x42, 0x02},
		{0x42, 0x04},
		{0x3E, 0x08},
		{0x3E, 0x10}, // Change only left side for the matrix
		{0x42, 0x20}, // Same thing
		{0x42, 0x40},
		{0x3E, 0x80}
	},
	
		{
			{0x00, 0x00},
			{0x00, 0x00},
			{0x00, 0x00},
			{0x00, 0x00},
			{0x00, 0x00}, // Change only left side for the matrix
			{0x00, 0x00}, // Same thing
			{0x00, 0x00},
			{0x00, 0x00}
		},
};

int main(void) {
	//    //output of columns
	//DDRC = 0xFF;
	//PORTC = 0x00;
	
	//set port A as output columns
	//DDRD = 0xFF;
	// PORTD = 0x00;
	//set period timer
	TimerSet(1);
	//initialize timer
	TimerOn();
	uint8_t i = 0;
	uint8_t j = 0;
	uint16_t k = 0;
	uint8_t state = 0;
	//initialize shift register
	shiftInit();
	shift2Init();
	//SNES_init();
	//LCD_init();
	while (1)
	{
		
		if(state == 0)
		{
			shift2Write(0xFF);
			shiftWrite(0x00);
			state = 1;
			++i;
		}
		else
		{
			shift2Write(0xFF & (~(l_list[j][i].row)) );
			shiftWrite(0x00 | (l_list[j][i].column));
			state = 0;
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
			if(j < 1)
			{
				j++;
			}
			else
			{
				j = 0;
			}
		}
		//shift2Write(0xFF); //& (~(l_list[j][i].row)) );
		//shiftWrite(0x00); //| (l_list[j][i].column));
		//Tick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
	
}
