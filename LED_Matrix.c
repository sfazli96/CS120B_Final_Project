/*
 * LED_matrix.c
 *
 * Created: 3/10/2020 11:25:13 AM
 * Author : sfazl001 Sameh Fazli
 */ 

#include <avr/io.h>
#include "shiftregister_columns.h"
#include "shiftRegister_Rows.h"
#include "timer.h"
#include "Light_array.h"
#include "scheduler.h"

#define TASK_SIZE 1
//period of timer: default 50ms
const unsigned long tasksPeriod = 50;
const unsigned char tasksSize = TASK_SIZE;
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
			if(j < 3)
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
int main(void)
{
    DDRB = 0x00; PORTB = 0xFF; // PORTB set to output, outputs init 0s
    DDRC = 0xFF; PORTC = 0x00; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	
	shiftInit();
	shift2Init();
	static task task1;
	task *tasks[] = { &task1 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1
	task1.state = display;//Task initial state.
	task1.period = 50;//Task Period.
	task1.elapsedTime = task1.period;//Task current elapsed time.
	task1.TickFct = &LED_Matrix;//Function pointer for the tick.
	
	// Set the timer and turn it on
	TimerSet(1);
	TimerOn();

	unsigned short i; // Scheduler for-loop iterator
	while(1) {
		for ( i = 0; i < numTasks; i++ )
		{ // Scheduler code
			if ( tasks[i]->elapsedTime >= tasks[i]->period )
			{ // Task is ready to tick
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state); // Set next state
				tasks[i]->elapsedTime = 0; // Reset the elapsed time for next tick.
			}
			tasks[i]->elapsedTime += tasksPeriod;
		}
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
    }

