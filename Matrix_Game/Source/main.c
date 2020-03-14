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
#include <time.h>
#include "shiftregister_columns.h"
#include "shiftRegister_Rows.h"
#include "timer.h"
#include "io.c"
#include "bit.h"
#include "scheduler.h"
#include "Light_array.h"
#include "Led_matrix.h"
#include "lcd_display.h"
#include "ReflexGame.h"	

//period of timer: default 50ms

#ifdef _SIMULATE_
#endif


int main(void) {
	DDRA = 0x03; PORTA = 0x00; //input
	DDRC = 0xFF;
	PORTC = 0x00;
	DDRD = 0xFF;
	PORTD = 0x00;
	srand(time(0));
	TimerSet(1);
	TimerOn();
	// Initializes the ShiftInit register
	shiftInit();
	// Initializes the Shift2Init register
	shift2Init();
	// Initializes the SNES_init controller
	SNES_init();
	// Initializes the LCD screen
	LCD_init();
	
	static task task1, task2, task3, task4;  // 4 different tasks
	task *tasks[] = { &task1, &task2, &task3, &task4};    // This is my Task array, 4 tasks
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	// Task 1 (Will show an output on the LED Matrix)
	task1.state = display;//Task initial state.
	task1.period = 1;//Task Period.
	task1.elapsedTime = task1.period;//Task current elapsed time.
	task1.TickFct = &LED_Matrix;//Function pointer for the tick.
	
	// Task 2 (Will show the LCDDisplay of the score)
	task2.state = Display_Menu;
	task2.period = 10;
	task2.elapsedTime = task2.period;
	task2.TickFct = &LCD_Display;
	
	// Task 3 (Game Logic)
	task3.state = Game_Menu;
	task3.period = 100;
	task3.elapsedTime = task3.period;
	task3.TickFct = &reflexGame;
	
	// SNES Controller 
	task4.state = SNES_LISTEN;
	task4.period = 1;
	task4.elapsedTime = task4.period;
	task4.TickFct = &snes;
	
	
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
