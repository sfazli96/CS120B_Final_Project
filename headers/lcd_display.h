/*
 * LCD_Display.h
 *
 * Created: 3/10/2020 1:35:37 AM
 * Author : sfazl001 Sameh Fazli
 */ 
#ifndef _LCD_Display_H_
#define _LCD_Display_H_
enum states{LCDdisplay};
int LCD_Display(int state)
{
	switch(state)
	{
		case LCDdisplay:
		state = LCDdisplay;
		break;	
	}
	
	// state actions 
	switch(state)
	{
		case LCDdisplay:
		LCD_Cursor(1);
		LCD_DisplayString(1, "Score: ");
		break;
	}
	return state;
}
#endif

