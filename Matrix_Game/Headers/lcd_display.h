/*
 * LCD_Display.c
 *
 * Created: 3/10/2020 1:35:37 AM
 * Author : sfazl001 Sameh Fazli
 */ 
#include "Global.h"
#include "snes.c"
#ifndef _LCD_Display_H_
#define _LCD_Display_H_
enum states{Display_Menu, Game};
int LCD_Display(int state)
{
	// Transitions 
	switch(state)
	{
		case Display_Menu:
		if(GameOn == 1)       // Display the Menu, Game will start when player presses start.
		{
			state = Game;
			LCD_ClearScreen();
		}
		else                      // Display the Menu, but Game will not start because player did not press start
		{
			GameOn = 0;            
			state = Display_Menu;
		}
		break;	
		case Game:                // If the Game is Off, then the LCD should only display a Menu
		if(GameOn == 0)
		{
			state = Display_Menu;
			LCD_ClearScreen();
		}
		else
		{
			GameOn = 1;          // If the game is On, then the LCD should change and the game starts.
			state = Game;
		}
		break;
	}
	
	// state actions 
	switch(state)
	{
		case Display_Menu:
		LCD_Cursor(1);
		LCD_WriteData(SNES_button());
		LCD_DisplayString(1, "Press start to play" );
		break;
		case Game:
		LCD_Cursor(1);
		if(score == 5)    // If the player gets 5 points then they win
		{
			LCD_DisplayString(1, "You win! Press A to play again");
		}
		else if (lives < 1) // Else if they lose all 3 lives then they lose and its game over.
		{
			LCD_DisplayString(1, "You Lose! Try again, press A");
		}
		else
		{
			TextMessage[6] = score + 48;  // updates the Score 
			TextMessage[15] = lives + 48; // Updates the Lives
			for(unsigned char i = 0; i < 16; i++) 
			{
				LCD_WriteData(TextMessage[i]); // Prints out both TextMessage of Score and Lives.
			}
		}
		break;
	}
	return state;
}
#endif

