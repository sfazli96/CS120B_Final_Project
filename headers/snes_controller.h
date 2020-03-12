/*
 * snes_controller.c
 *
 * Created: 3/11/2020 9:31:17 PM
 * Author : sfazl001 Sameh Fazli 
 */ 
#ifndef _snes_controller_H_
#define _snes_controller_H_
#include "Global.h"
#include "snes.c"
enum SNESStates { SNES_LISTEN };
int snes(int state) {
	switch(state) {
		case SNES_LISTEN:
		ValueOfSNES = SNES_button();
		break;
		
		default:
		state = SNES_LISTEN;
		break;
	}
	return state;
}

#endif
