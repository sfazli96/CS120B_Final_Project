/*
 * LCD_Display.c
 *
 * Created: 3/10/2020 1:35:37 AM
 * Author : sfazl001 Sameh Fazli
 */ 
#include "Global.h"
#ifndef _LCD_Display_H_
#define _LCD_Display_H_
enum states{MENU, Game};
int LCD_Display(int state)
{
	switch(state)
	{
		case MENU:
		if(GameOn == 1)
		{
			state = Game;
			LCD_ClearScreen();
		}
		else
		{
			GameOn = 0;
			state = MENU;
		}
		break;	
		case Game:
		if(GameOn == 0)
		{
			state = MENU;
			LCD_ClearScreen();
		}
		else
		{
			GameOn = 1;
			state = Game;
		}
	}
	
	// state actions 
	switch(state)
	{
		case MENU:
		LCD_Cursor(1);
		LCD_DisplayString(1, "Press start to play" );
		break;
		case Game:
		LCD_Cursor(1);
		LCD_DisplayString(1, "Score: ");
		if(score == 5)
		{
			LCD_DisplayString(1, "You win! Press A to play again!");
		}
		else if(lives == 0 || score != 5)
		{
			LCD_DisplayString(1, "You Lose! Press A to play again");
		}
		break;
	}
	return state;
}
#endif

