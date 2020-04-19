/*
 * alarm.c
 *
 * Created: 19.04.2020 01:46:12
 *  Author: David
 */ 

#include "alarm.h"

int16_t diff_alarm=500;
uint16_t tone_overfl_counter=0, alarm_pause_counter=0, ALARM_TIME = 10000;


void init_ALARM_ISR(){
	
	DDRD |= (1<<PD7);
	
	TCCR1A = 0x00;
	TCCR1B = 0x02;
	
	//TCCR1A = 0x03;
	//TCCR1B = 0x03;
	
	TIMSK |= (1<<TOIE1);
	
	
	TCNT1H = 0xFF;  // TIMER1 10us Interrupt
	TCNT1L = 255-10;
	
	sei();
}

ISR(TIMER1_OVF_vect){
	TCNT1H = 0xFF;
	TCNT1L = 255-10;
	//if(alarm_pause_counter<=ALARM_TIME){
		if(tone_overfl_counter<=ALARM_SOUND){
			tone_overfl_counter++;
		}
		else{
			PORTD ^= (1<<PD7);
			tone_overfl_counter = 0;
		}
		alarm_pause_counter++;
	//}
	/*else if(alarm_pause_counter>ALARM_TIME&&alarm_pause_counter<=(2*ALARM_TIME)){
		alarm_pause_counter++;
	}
	else{
		alarm_pause_counter=0;
		ALARM_TIME-=diff_alarm;
		if(ALARM_TIME==0)
			diff_alarm=-500;
		if(ALARM_TIME>10000)
			diff_alarm=500;
	} */
}