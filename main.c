/*
 * IR_remote.c
 *
 * Created: 08.04.2020 02:01:44
 * Author : David
 */ 

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


#ifndef LIGHT_TIME
#define LIGHT_TIME 5000
#endif

#ifndef LIGHT_TIME_LOW
#define LIGHT_TIME_LOW 2000
#endif

#ifndef ALARM_SOUND
#define ALARM_SOUND (100000/200)
#endif

/*#ifndef ALARM_TIME
#define ALARM_TIME 10000
#endif */


#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

volatile uint8_t sek=0, min=0, min_zehn=0, min_ein=0, sek_zehn=0, sek_ein=0, toggle_bit=0;

uint16_t sek_count=0, timer_overfl_counter=0, tone_overfl_counter=0, alarm_pause_counter=0, ALARM_TIME = 10000;
int16_t diff_alarm=500;

void show_num(uint8_t zahl){
	switch(zahl){
		case 1:
		PORTD = ~((1<<1)|(1<<2));
		_delay_us(LIGHT_TIME_LOW);
		break;
		case 2:
		PORTD = ~((1<<0)|(1<<1)|(1<<4)|(1<<3)|(1<<6));
		_delay_us(LIGHT_TIME);
		break;
		case 3:
		PORTD = ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<6));
		_delay_us(LIGHT_TIME);
		break;
		case 4:
		PORTD = ~((1<<1)|(1<<2)|(1<<5)|(1<<6));
		_delay_us(LIGHT_TIME_LOW);
		break;
		case 5:
		PORTD = ~((1<<0)|(1<<2)|(1<<3)|(1<<5)|(1<<6));
		_delay_us(LIGHT_TIME);
		break;
		case 6:
		PORTD = ~((1<<0)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6));
		_delay_us(LIGHT_TIME);
		break;
		case 7:
		PORTD = ~((1<<0)|(1<<1)|(1<<2));
		_delay_us(LIGHT_TIME_LOW);
		break;
		case 8:
		PORTD = ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6));
		_delay_us(LIGHT_TIME);
		break;
		case 9:
		PORTD = ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<5)|(1<<6));
		_delay_us(LIGHT_TIME);
		break;
		case 0:
		PORTD = ~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
		_delay_us(LIGHT_TIME);
		break;
		default:
		PORTD = 0xFF;
		
		break;
	}
}

void select_digit(uint8_t indx){
	switch(indx){
		case 1:
		PORTC = ~(1<<0);
		break;
		case 2:
		PORTC = ~(1<<1);
		break;
		case 3:
		PORTC = ~(1<<2);
		break;
		case 4:
		PORTC = ~(1<<3);
		break;
		default:
		PORTC = 0xFF;
		break;
		
	}
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
	
	select_digit(1);
	show_num(sek_ein);
	//_delay_us(LIGHT_TIME);
	select_digit(2);
	show_num(sek_zehn);
	//_delay_us(LIGHT_TIME);
	select_digit(3);
	show_num(min_ein);
	//_delay_us(LIGHT_TIME);
	select_digit(4);
	show_num(min_zehn);
	//_delay_us(LIGHT_TIME);
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
		if(toggle_bit==0){
			send_0();
		}
		else{
			send_1();
		}
		toggle_bit ^= (1<<0);
		
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
int main(void)
{
    /* Replace with your application code */
	DDRB = 0xFF;
	PORTB = 0x00;
	
	
	DDRD = 0xFF;
	DDRC = 0xFF;
	
	TCCR0 = 0x03;
	
	TCCR1A = 0x00;
	TCCR1B = 0x02;
	
	//TCCR1A = 0x03;
	//TCCR1B = 0x03;
	
	TIMSK = (1<<TOIE0)|(1<<TOIE1);
	
	TCNT0 = 0x83;
	
	TCNT1H = 0xFF;  // TIMER1 10us Interrupt
	TCNT1L = 255-10;
	
	sei();
	
	
	
	uint16_t cmd;
    while (1) 
    {	
		send_command(DEVICE_ADR, CMD);
		
		_delay_ms(100);
		/*for(uint16_t j=0;j<80;j++){
			show_time(0,j);
		}*/
			
		/*PORTB = 0xFF;
		_delay_ms(2000);
		PORTB = 0x00;*/
		
    }
}

ISR(TIMER0_OVF_vect){
	TCNT0 = 131;
	if(timer_overfl_counter<=999){
		timer_overfl_counter++;
	}
	else{
		sek++;
		timer_overfl_counter = 0;
	}
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
