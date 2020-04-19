/*
 * interrupts.c
 *
 * Created: 19.04.2020 01:06:54
 *  Author: David
 */ 

#include "time.h"

uint16_t timer_overfl_counter=0;

volatile uint8_t sek=0, min=0, min_zehn=0, min_ein=0, sek_zehn=0, sek_ein=0;

void init_TIME_ISR(){
	TCCR0 = 0x03;
	
	
	TIMSK |= (1<<TOIE0);
	
	TCNT0 = 0x83;
	
	
	sei();
}

ISR(TIMER0_OVF_vect){
	TCNT0 = 131;
	if(timer_overfl_counter<=999){
		timer_overfl_counter++;
	}
	else{
		if(sek+1>=60){
			sek=0;
			min++;
		}
		else{
			sek++;
		}
		timer_overfl_counter = 0;
	}
}
