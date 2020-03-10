#include <avr/interrupt.h>
// initialize to 0s
#define A0 (~PINA & 0x01)
#define A1 (~PINA & 0x02)
enum CR_States {Start, one , two , three, Stop, reset} State;
//volatile unsigned char TimerFlag = 0;

void Tick(){
	switch (State){
		case Start:
		State = Start;
		break;
		
		case one:
		if(A0){
			State = one;
		}else{
			State = two;
		}
		
		break;
		
		case two:
		if(A0){
			State = Stop;
		}else{
			State = three;
		}
		
		break;
		
		case three:
		if(A0){
			State = Stop;
		}else{
			State = one;
		}
		break;
		
		case Stop:
		if(!A0){
			State = reset;
		}else{
			State = Stop;
		}
		break;
		
		case reset:
		if(A0){
			State = one;
		}else{
			State = reset;
		}
	}
	
	switch (State){
		case Start:
		break;
		
		case one:
		PORTB = 0x01;
		break;
		
		case two:
		PORTB = 0x02;
		break;
		
		case three:
		PORTB = 0x04;
		break;
		
		case Stop:
		break;
		
		case reset:
		break;
	}
}

//int main(void)
//{
    /* Replace with your application code */
	//DDRB = 0xFF; PORTB = 0x00;
	//DDRA = 0x00; PORTA = 0xFF;
	//TimerSet(300);
	//TimerOn();
	
    //while (1) 
    //{
	//	Tick();
	//	while(!TimerFlag);
	//	TimerFlag = 0;
    //}
//}
