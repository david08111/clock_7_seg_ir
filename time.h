/*
 * interrupts.h
 *
 * Created: 19.04.2020 01:08:49
 *  Author: David
 */ 



#ifndef TIME_H_
#define TIME_H_

#ifndef F_CPU
#define F_CPU 8000000
#endif

#include <avr/io.h>
#include <avr/interrupt.h>


extern volatile uint8_t sek, min, min_zehn, min_ein, sek_zehn, sek_ein;
extern uint16_t timer_overfl_counter;


void init_TIME_ISR();
ISR(TIMER0_OVF_vect);


#endif /* TIME_H_ */