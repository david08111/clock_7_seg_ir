/*
 * ir.h
 *
 * Created: 19.04.2020 01:09:10
 *  Author: David
 */ 


#ifndef IR_H_
#define IR_H_

#ifndef F_CPU
#define F_CPU 8000000
#endif

#ifndef DEVICE_ADR
#define DEVICE_ADR 0x11 //-->0x10   0x14 , 0x11
#endif

#ifndef CMD
#define CMD 0x3F //0x10, 0x3F
#endif

#ifndef C_ON
#define C_ON 7 //7
#endif

#ifndef C_OFF
#define C_OFF 20 //21
#endif

#ifndef C_DELAY
#define C_DELAY 840 //889
#endif

#include <avr/io.h>
#include <avr/delay.h>


extern volatile int8_t tggle_bit;


void init_IR();
void send_1();
void send_0();
void send_command(uint8_t device_adr, uint8_t command);


#endif /* IR_H_ */