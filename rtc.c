/*
 * RTC.c
 *
 * Created: 19.04.2020 21:01:30
 *  Author: David
 */ 

#include "rtc.h"

void init_RTC(){
	DDRC |= (1<<0)|(1<<1);
	
	PORTC |= (1<<0)|(1<<1);
}

int get_ack(){
	uint8_t ack;
	_delay_us(1);
	PORTC &= ~(1<<RTC_SDA);
	_delay_us(1);
	DDRC &= ~(1<<RTC_SDA);
	_delay_us(2);
	PORTC |= (1<<RTC_SCL);
	_delay_us(1);
	
	if((PINC & (1<<RTC_SDA))==(1<<RTC_SDA)){
		ack = 1;
	}
	else{
		ack = 0;
	}
	
	_delay_us(3);
	PORTC &= ~(1<<RTC_SCL);
	
	DDRC |= (1<<RTC_SDA);
	
	return ack;
}

void write_byte(uint8_t buff_foo){
	uint8_t ack;
	for(uint8_t i=7;i>=0;i--){
		if((buff_foo & (1<<i))==(1<<i)){
			//voraussetzung RTC_SCL auf LOW angenommen
			_delay_us(1);
			PORTC |= (1<<RTC_SDA);
			_delay_us(4);
			PORTC |= (1<<RTC_SCL);
			_delay_us(5);
			PORTC &= ~(1<<RTC_SCL);
		}
		else{
			_delay_us(1);
			PORTC &= ~(1<<RTC_SDA);
			_delay_us(4);
			PORTC |= (1<<RTC_SCL);
			_delay_us(5);
			PORTC &= ~(1<<RTC_SCL);
		}
	}
	
	ack = get_ack();
	
	
}


void write_register(uint8_t reg, uint8_t val){
	_delay_us(20);
	
	PORTC |= (1<<RTC_SDA);
	_delay_us(1);
	PORTC |= (1<<RTC_SCL);
	_delay_us(1);
	PORTC &= ~(1<<RTC_SDA); //startbed
	_delay_us(5);
	PORTC &= ~(1<<RTC_SCL);
	
	write_byte(0xDE); //adresse + write bit
	
	write_byte(reg);
	write_byte(val);
	
	//stopp bed
	
	PORTC &= ~(1<<RTC_SCL);
	_delay_us(1);
	PORTC &= ~(1<<RTC_SDA);
	_delay_us(3);
	PORTC |= (1<<RTC_SCL);
	_delay_us(1);
	PORTC |= (1<<RTC_SDA);
	_delay_us(4);
}

uint8_t read_byte(){
	uint8_t reg_val;
	_delay_us(1);
	DDRC &= ~(1<<RTC_SDA);
	
	for(uint8_t i=7;i>=0;i--){
		PORTC &= ~(1<<RTC_SCL);
		_delay_us(4);
		PORTC |= (1<<RTC_SCL);
		_delay_us(1);
		
		if((PINC & (1<<RTC_SDA))==(1<<RTC_SDA)){
			uint8_t bit_add = 1;
			for(uint8_t j=1;j<i;j++){
				bit_add*=2;
			}
			reg_val += bit_add;
		}
		_delay_us(2);
		
	}
	
	PORTC &= ~(1<<RTC_SCL);
	_delay_us(1);
	PORTC |= (1<<RTC_SDA);
	_delay_us(3);
	PORTC |= (1<<RTC_SCL);
	_delay_us(4);
	PORTC &= ~(1<<RTC_SCL);
	
}

uint8_t read_register(uint8_t reg){
	_delay_us(20);
	uint8_t reg_val;
	
	PORTC |= (1<<RTC_SDA);
	_delay_us(1);
	PORTC |= (1<<RTC_SCL);
	_delay_us(1);
	PORTC &= ~(1<<RTC_SDA); //startbed
	_delay_us(5);
	PORTC &= ~(1<<RTC_SCL);
	
	write_byte(0xDE);
	write_byte(reg);
	
	//start bed
	PORTC &= ~(1<<RTC_SCL);
	_delay_us(1);
	PORTC |= (1<<RTC_SDA);
	_delay_us(1);
	PORTC |= (1<<RTC_SCL);
	_delay_us(1);
	PORTC &= ~(1<<RTC_SDA);
	
	
	
	write_byte(0xDF);
	
	reg_val = read_byte();
	
	//stopp bed
	
	_delay_us(1);
	PORTC &= ~(1<<RTC_SDA);
	_delay_us(3);
	PORTC |= (1<<RTC_SCL);
	_delay_us(1);
	PORTC |= (1<<RTC_SDA);
	_delay_us(3);
	
}


void rtc_set_init(){
	write_register(0x07, 0x00);
	write_register(0x00, 0x00);
	write_register(0x01, 0x01);
	write_register(0x00, 0x00);
	write_register(0x00, 0x00);
}
