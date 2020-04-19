/*
 * ir.c
 *
 * Created: 19.04.2020 00:26:32
 *  Author: David
 */ 


#include "ir.h"

volatile int8_t tggle_bit=0;

void init_IR(){
	DDRB = 0x01;
	PORTB = 0x00;
	
}

void send_1(){
	_delay_us(C_DELAY);
	
	for(uint8_t i=0;i<32;i++){
		PORTB = 0xFF;
		_delay_us(C_ON);
		//_delay_ms(1000);
		PORTB = 0x00;
		_delay_us(C_OFF);
		//_delay_ms(1000);
	}
}

void send_0(){
	for(uint8_t i=0;i<32;i++){
		PORTB = 0xFF;
		_delay_us(C_ON);
		//_delay_ms(1000);
		PORTB = 0x00;
		_delay_us(C_OFF);
		//_delay_ms(1000);
	}
	_delay_us(C_DELAY);
}

void send_command(uint8_t device_adr, uint8_t command){
	for(uint8_t i=0;i<2;i++){
		send_1();
	}
	//send_1();
	if(tggle_bit==0){
		send_0();
	}
	else{
		send_1();
	}
	tggle_bit ^= (1<<0);
	
	for(int8_t i=4;i>=0;i--){
		if((device_adr&(1<<i))==(1<<i)){
			send_1();
		}
		else{
			send_0();
		}
	}
	
	for(int8_t i=5;i>=0;i--){
		if((command&(1<<i))==(1<<i)){
			send_1();
		}
		else{
			send_0();
		}
	}
	
}