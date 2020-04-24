/*
 * IR_remote.c
 *
 * Created: 08.04.2020 02:01:44
 * Author : David
 */ 

#ifndef F_CPU
#define F_CPU 8000000
#endif


#include <avr/io.h>
#include <avr/delay.h>

#include "alarm.h"
#include "display_7_seg.h"
#include "ir.h"
#include "time.h"
#include "rtc.h"


void init_main(){
	init_IR();
	init_DISPLAY();
	//init_TIME_ISR();
	init_ALARM_ISR();
	
	rtc_set_init();
}

int main(void)
{	
	init_main();
	
	//hour=20;
	//min=53;
	
	rtc_set_init();
	
    while (1) 
    {	
		//send_command(DEVICE_ADR, CMD);
		
		/*min = read_register(0x01);
		hour = read_register(0x02);
		
		show_time(hour, min);*/
		
		sek = rtc_read_sek();
		min = rtc_read_min();
		hour = rtc_read_hour();
		
		show_time(hour, min);
		
		for(uint8_t i=0;i<10;i++){
			_delay_ms(1);
			show_time(hour, min);
		}
		
		
		
		/*if(min+1>=60){
			min=0;
			hour++;
		}
		if(hour+1>=25){
			hour=0;
		}
		
		show_time(hour, min);*/
		
    }
}
