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


void init_main(){
	init_IR();
	init_DISPLAY();
	init_TIME_ISR();
	init_ALARM_ISR();
}

int main(void)
{	
	init_main();
    while (1) 
    {	
		//send_command(DEVICE_ADR, CMD);
		
		//show_time(6,23);
		
		show_time(min, sek);

		/*for(uint16_t j=0;j<80;j++){
			show_time(0,j);
		}*/
			
		//_delay_ms(200);
		
    }
}
