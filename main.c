/*
 * sfazl001_cs120_Final_project_demo1.c
 * Created: 2/25/2020 4:23:37 PM
 *	Author: Sameh Fazli
 *	Lab Section:
 *	Assignment: CS120b Final Project 
 *	Exercise Description: [optional - include for your own benefit]
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "shiftregister_columns.h"
#include "shiftRegister_Rows.h"
#include "timer.h"
#include "io.c"
#include "bit.h"
#include "scheduler.h"
#include "Light_array.h"
#include "Led_matrix.h"
//#include "snes.c"
#define TASK_SIZE 1
//period of timer: default 50ms
const unsigned long tasksPeriod = 50;
const unsigned char tasksSize = TASK_SIZE;
#ifdef _SIMULATE_
#endif


int main(void) {
	
	TimerSet(1);
	//initialize timer
	TimerOn();
	//initialize shift register
	shiftInit();
	shift2Init();
	//SNES_init();
	//LCD_init();
	static task task1;
	task *tasks[] = { &task1 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1 (Will show an output on the LED Matrix)
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



