/*
 * display_7_seg.h
 *
 * Created: 19.04.2020 01:52:52
 *  Author: David
 */ 


#ifndef DISPLAY_7_SEG_H_
#define DISPLAY_7_SEG_H_

#ifndef F_CPU
#define F_CPU 8000000
#endif

#ifndef LIGHT_TIME
#define LIGHT_TIME 5000
#endif

#ifndef LIGHT_TIME_LOW
#define LIGHT_TIME_LOW 2000
#endif

#ifndef SER
#define SER PD0
#endif

#ifndef SRCLK 
#define SRCLK PD1
#endif

#ifndef RCLK
#define RCLK PD2
#endif

#ifndef OE
#define OE PD3
#endif


#include <avr/io.h>
#include <avr/delay.h>

#include "time.h"

void init_DISPLAY();
void write_buffer(uint8_t buff_foo);
void set_light_delay(uint16_t light_delay);
void show_num(uint8_t stelle, uint8_t zahl);
void show_time(uint8_t min, uint8_t sek);


#endif /* DISPLAY_7_SEG_H_ */