/*
 * GameLogic.c
 *
 * Created: 3/5/2020 12:12:45 AM
 * Author : sfazl001 Sameh Fazli
 * CS120b
 */ 
#ifndef _ReflexGame_H_
#define _ReflexGame_H_
#include "snes.c"
#include "snes_controller.h"
#include "Global.h" 
enum GameStates{Game_Menu, Start_Game, Display_Matrix, Turn_OFF_Matrix, First_Button, Wait1, Second_button, wait2, ButtonInput, Update_Score, Lose_Life, GameOver, EndGame}; // States what the game does 

int reflexGame(int State)
{
	// Transitions 
	switch(State)
	{
		case Game_Menu: // Game is Off, So only Menu will show up
		GameOn = 0;
		State = Game_Menu;
		break;
		case Start_Game: // Game is On, Displays the LED Matrix
		GameOn = 1;
		State = Display_Matrix;
		break;
		case Display_Matrix:
		if(counter == 0 && time_counter == 0)
		{
			Rand_Char = Get_Num();
			j = Rand_Char;
		} 
		else if (counter == 1 && time_counter == 0)
		{
			Rand_Char2 = Get_Num();
			j = Rand_Char2;
		}
		matrixControl = 1;
		if(time_counter >= 20) // This means that the time has to be more than 1 second
		{ 
			counter++; // If i show the lights the first time its good.
			time_counter = 0; // This is for the time 
			State = Turn_OFF_Matrix;  // Then it turns off the matrix
		}
		else
		{
			time_counter++; //Keep incrementing the time.
			State = Display_Matrix; // Then Display the matrix back
		}
		break;
		case Turn_OFF_Matrix:
		matrixControl = 0;
		j = 10;
		if(counter == 2) // Done displaying.
		{			
			State = First_Button;
		}
		else if (time_counter >= 10) // Repeat display and turn On and Off after button Input
		{
			time_counter = 0;
			State = Display_Matrix;
		}
		else
		{
			State = Turn_OFF_Matrix;
			time_counter++;
		}
		break;
		case First_Button:
		//LCD_Cursor(17);
		//LCD_WriteData(MatrixMap[Rand_Char]);
		//LCD_WriteData(MatrixMap[Rand_Char2]);
		ButtonPressed = SNES_button();
		if(ButtonPressed != ' ')
		{
			Pressed = ButtonPressed;
			State = Wait1;
		}
		else
		{
			State = First_Button;
		}
		break;
		case Wait1:
		ButtonPressed = SNES_button();
		if(ButtonPressed != ' ')
		{
			State = Wait1;
		}
		else
		{
			State = Second_button;
		}
		break;
		case Second_button:
		ButtonPressed = SNES_button();
		if(ButtonPressed != ' ')
		{
			Pressed2 = ButtonPressed;
			State = wait2;
		}
		else
		{
			State = Second_button;
		}
		break;
		case wait2:
		ButtonPressed = SNES_button();
		if(ButtonPressed != ' ')
		{
			State = wait2;
		}
		else
		{
			State = ButtonInput;
		}
		break;
		case ButtonInput:
		//LCD_Cursor(17);
		//LCD_WriteData(Pressed);
		//LCD_WriteData(Pressed2);
		//if(time_counter > 30)
		//{
			if(Pressed == MatrixMap[Rand_Char] && Pressed2 == MatrixMap[Rand_Char2])
			{
				State = Update_Score;   // Will get score
			}
			else
			{
				State = Lose_Life;     // Will get life
			}
		//}
		//else
		//{
		//	time_counter++;
		//	State = ButtonInput; // In action what buttons are we actually pushing
		//}
		break;
		case Update_Score:
		if(score == 5)    // Finished with game
		{
			State = EndGame;     
		}
		else
		{
			time_counter = 0; // Keep playing the game
			State = Display_Matrix;
			counter = 0;
		}
		break;
		case Lose_Life:
		if(lives < 1)     // If player losses all lives then game over
		{
			State = GameOver;
		}
		else
		{
			time_counter = 0;
			State = Display_Matrix;
			counter = 0;
		}
		break;
		case GameOver:    // Where u lose
		PressA = SNES_button();
		if(PressA == 'A')  
		{
			State = Start_Game;
			lives = 3;
			score = 0;
			LCD_ClearScreen();
		}
		else
		{
			State = GameOver;
		}
		break;
		case EndGame:
		PressA = SNES_button();
		LCD_Cursor(17);
		LCD_WriteData(PressA);
		if(PressA == 'A') 
		{
			State = Start_Game;
			lives = 3;
			score = 0;
			LCD_ClearScreen();
		}
		else 
		{
			State = EndGame;
		}
		break;
		default:
		break;
	}
	
// Actions
switch(State)
{
	case Game_Menu:
	if(ValueOfSNES == 'S')   
	{
		GameOn = 1;
		State = Start_Game;
	}
	break;
	case Start_Game:
	counter = 0;
	time_counter = 0;
	break;
	case Display_Matrix:
	break;
	case Turn_OFF_Matrix:
	break;
	case ButtonInput:
	/*UserInput = SNES_button();   
	//if(UserInput != 0 && ButtonCounterPresses == 0)
	if(UserInput != ' ' && ButtonCounterPresses == 0)
	{
		Pressed = SNES_button();
		//ButtonCounterPresses++;
		LCD_Cursor(19);
		LCD_WriteData('1');
	}
	else if(UserInput != ' ' && ButtonCounterPresses)
	{
		Pressed2 = SNES_button();
		//ButtonCounterPresses++;
		LCD_Cursor(20);
		LCD_WriteData('1');
	}
	else
	{
		LCD_Cursor(21);
		LCD_WriteData('1');
	}
	*/
	break;
	case Update_Score:
	score++;    // Increment score
	break;
	case Lose_Life:
	lives--;   // Decrement lives
	break;
	case GameOver:
	break;
	case EndGame:
	break;
	default: 
	break;
	
}
	return State;
}


#endif
