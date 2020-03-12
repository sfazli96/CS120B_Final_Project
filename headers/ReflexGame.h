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
enum GameStates{Menu, Start_Game, Display_Matrix, Turn_OFF_Matrix, ButtonInput, Update_Score, Lose_Life, GameOver, EndGame}; // States what the game does 

int reflexGame(int State)
{
	// Transitions 
	switch(State)
	{
		case Menu:
		GameOn = 0;
		break;
		case Start_Game:
		GameOn = 1;
		State = Display_Matrix;
		break;
		case Display_Matrix:
		if(time_counter >= 10) // This means that the time has to be more than 1 second
		{ 
			counter++; // If i show the lights the first time its good.
			time_counter = 0; // This is for the time 
			State = Turn_OFF_Matrix;
		}
		else
		{
			time_counter++; //Keep incrementing the time.
			State = Display_Matrix;
		}
		break;
		case Turn_OFF_Matrix:
		if(counter == 2) // Done displaying.
		{			
			counter = 0;
			State = ButtonInput;
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
		case ButtonInput:
		if(time_counter > 60)
		{
			if(Pressed == Rand_Num && Pressed2 == Rand_Num2)
			{
				State = Update_Score;
			}
			else
			{
				State = Lose_Life;
			}
		}
		else
		{
			State = ButtonInput; // In action what buttons are we actually pushing
		}
		break;
		case Update_Score:
		if(score == 5)
		{
			State = EndGame;
		}
		else
		{
			time_counter = 0; // Keep playing the game
			State = Display_Matrix;
		}
		break;
		case Lose_Life:
		if(lives < 1)
		{
			State = GameOver;
		}
		else
		{
			time_counter = 0;
			State = Display_Matrix;
		}
		break;
		case GameOver:
		if(PressA == 128)  
		{
			State = Start_Game;
		}
		else
		{
			State = GameOver;
		}
		break;
		case EndGame:
		if(PressA == 128) 
		{
			State = Start_Game;
		}
		else 
		{
			State = Menu;
		}
		break;
	}
// Actions
switch(State)
{
	case Menu:
	if(SNES_Read() == 4096)
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
	UserInput = SNES_Read();
	if(UserInput != 0 && Pressed == 0)
	{
		Pressed = UserInput;
	}
	else if(UserInput != 0)
	{
		Pressed2 = UserInput;
	}
	break;
	case Update_Score:
	score++;
	break;
	case Lose_Life:
	lives--;
	break;
	case GameOver:
	break;
	case EndGame:
	break;
	
	default:
	score = 10;
}
	return State;
}


#endif
