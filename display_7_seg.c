/*
 * Display.c
 *
 * Created: 19.04.2020 00:25:53
 *  Author: David
 */ 

#include "display_7_seg.h"

void init_DISPLAY(){
	DDRD |= 0x0F;
	PORTD &= 0xF0;
}


void write_buffer(uint8_t buff_foo){
	PORTD &= ~(1<<PD1);
	for(int8_t i=7;i>=0;i--){
		if((buff_foo &(1<<i)) == (1<<i)){
			PORTD |= (1<<PD0);
			_delay_us(1);
			PORTD |= (1<<PD1);
			PORTD &= ~(1<<PD1);
		}
		else{
			PORTD &= ~(1<<PD0);
			_delay_us(1);
			PORTD |= (1<<PD1);
			PORTD &= ~(1<<PD1);
		}
	}
}

void set_light_delay(uint16_t light_delay){
	PORTD &= ~(1<<PD2);
	PORTD |= (1<<PD2);
	_delay_us(1);
	PORTD &= ~(1<<PD3);
	/*for(uint16_t i=0;i<light_delay;i++){
		_delay_us(1);
	}*/

	
}

void show_num(uint8_t stelle, uint8_t zahl){
	PORTD |= (1<<PD3);

	switch(stelle){
		case 1:
		write_buffer(~0x08);
		break;
		case 2:
		write_buffer(~0x04);
		break;
		case 3:
		write_buffer(~0x02);
		break;
		case 4:
		write_buffer(~0x01);
		break;
		default:
		write_buffer(~0x00);
		break;
	}
	
	uint8_t zahl_temp = 0x00;
	uint16_t delay_light = 0;

	switch(zahl){
		case 1:
		zahl_temp = ~((1<<1)|(1<<2));
		break;
		case 2:
		zahl_temp = ~((1<<0)|(1<<1)|(1<<4)|(1<<3)|(1<<6));
		break;
		case 3:
		zahl_temp = ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<6));
		break;
		case 4:
		zahl_temp = ~((1<<1)|(1<<2)|(1<<5)|(1<<6));
		break;
		case 5:
		zahl_temp = ~((1<<0)|(1<<2)|(1<<3)|(1<<5)|(1<<6));
		break;
		case 6:
		zahl_temp = ~((1<<0)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6));
		break;
		case 7:
		zahl_temp = ~((1<<0)|(1<<1)|(1<<2));
		break;
		case 8:
		zahl_temp = ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6));
		break;
		case 9:
		zahl_temp = ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<5)|(1<<6));
		break;
		case 0:
		zahl_temp = ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
		break;
		default:
		zahl_temp = 0xFF;
		break;
	}
	write_buffer(zahl_temp);
	set_light_delay(delay_light); //delay sinnlos, da SR an bis zum nächsten zeitwechsel
}

void show_time(uint8_t min, uint8_t sek){
	if(min/10!=0){
		min_zehn = min/10;
	}
	else{
		min_zehn = 10; //leer
	}
	min_ein = min % 10;
	if(sek/10!=0){
		sek_zehn = sek/10;
	}
	else{
		sek_zehn = 0;
	}
	sek_ein = sek % 10;
	
	show_num(1, sek_ein);
	//_delay_ms(5);
	show_num(2, sek_zehn);
	//_delay_ms(5);
	show_num(3, min_ein);
	//_delay_ms(5);
	show_num(4, min_zehn);
	//_delay_ms(5);
}


