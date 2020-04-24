/*
 * alarm.h
 *
 * Created: 19.04.2020 01:46:23
 *  Author: David
 */ 


#ifndef ALARM_H_
#define ALARM_H_

#ifndef F_CPU
#define F_CPU 8000000
#endif

#ifndef ALARM_FREQ
#define ALARM_FREQ 440
#endif

#ifndef ALARM_SOUND
#define ALARM_SOUND 100000/(2 * ALARM_FREQ) //(100000/200)
#endif

/*#ifndef ALARM_TIME
#define ALARM_TIME 10000
#endif */

#include <avr/io.h>
#include <avr/interrupt.h>


extern int16_t diff_alarm;
extern uint16_t tone_overfl_counter, alarm_pause_counter, ALARM_TIME;


void init_ALARM_ISR();
ISR(TIMER1_OVF_vect);


#endif /* ALARM_H_ */