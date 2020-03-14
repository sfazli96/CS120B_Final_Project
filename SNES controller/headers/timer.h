#ifndef TIMER_H
#define TIMER_H

#include <avr/interrupt.h>

// TimerISR() sets this to 1. C programmer should clear to 0.
volatile unsigned char TimerFlag = 0;

// Internal variables for mapping the AVR's ISR to our cleaner TimerISR
// model.
//
// Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_M = 1;
// Current internal count of 1 ms ticks
unsigned long _avr_timer_cntcurr = 0; 

void TimerOn()
{
    //AVR timer/counter controller register TCCR1
    //  bit3 = 0: CTC mode (clear timer on compare)
    //  bit2bit1bit0=011: pre-scalar /64
    //  00001011: 0x0B
    //  SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks
    //  Thus, TCNT1 register will count at 125,000 ticks
    TCCR1B 	= 0x0B;

    //AVR output compare register OCR1A.
    //  Timer interrupt will be genterated when TCNT1==OCR1A
    //  We want a 1 ms tick, 0.001 s * 125,000 tick/s = 125
    //  So when TCNT1 register equals 125,
    //  1 ms has passed. Thus, we compare to 125
    OCR1A 	= 125;

    //AVR timer interrupt mask register
    // bit1: OCIE1A -- enables compare match interrupt
    TIMSK1 	= 0x02;

    //Initialize avr counter
    TCNT1 = 0;

    //TimerISR will be called every _avr_timer_cntcurr milliseconds
    _avr_timer_cntcurr = _avr_timer_M;

    //Enable global interrupts
    SREG |= 0x80; // 0x80: 1000000
}

//sets the timer to be off
void TimerOff()
{
    //bit3bit1bit0-000: timer off
    TCCR1B 	= 0x00;
}

//change timer flag when one period is complete
void TimerISR()
{
    TimerFlag = 1;
}

//In our approach, the C programmer does not touch this ISR, but rather
//TimerISR()
ISR(TIMER1_COMPA_vect)
{
    //CPU automatically calls when TCNT == OCR1 (every 1 ms per TimerOn
    //settings)
    //
    //Count down to 0 rather than up to TOP
    _avr_timer_cntcurr--;
    //this results in more efficient comparison
    if (_avr_timer_cntcurr == 0)
    {
        //Call the ISR that the user uses
        TimerISR();
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

//Set TimerISR() to tick every M ms
void TimerSet(unsigned long M)
{
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}
#endif//TIMER_H
