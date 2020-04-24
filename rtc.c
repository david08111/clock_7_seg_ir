/*
 * RTC.c
 *
 * Created: 19.04.2020 21:01:30
 *  Author: David
 */ 

#include "rtc.h"

void init_RTC(){
	TWBR = 0x02;
	TWAR = 0x6F;
	TWSR = 0x00;
}

void TWI_START(){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	
	while(!(TWCR &(1<<TWINT)));
	if((TWSR&0xF8) != 0x08){
		//WIP
	}
}

void TWI_MT_SLA_ACK(){
	TWDR = SLA_ADDR;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while(!(TWCR&(1<<TWINT)));
	
}

void TWI_MT_DATA_ACK(uint8_t send_data){
	TWDR = send_data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while(!(TWCR&(1<<TWINT)));
}

void TWI_R_START(){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	
}

void TWI_MR_SLA_ACK(){
	TWDR = SLA_ADDR+1;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while(!(TWCR&(1<<TWINT)));
	
}

uint8_t TWI_READ_DATABYTE_NACK(){
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	return TWDR;
}

void TWI_STOP(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}


void rtc_set_init(){
	TWI_START();
	TWI_MT_SLA_ACK();
	TWI_MT_DATA_ACK(0x00); //ADDR
	TWI_MT_DATA_ACK(0x80); //SEK
	TWI_MT_DATA_ACK(0x40); //MIN
	TWI_MT_DATA_ACK(0x02); //HOUR
	TWI_STOP();
	
}

uint8_t rtc_read_reg(uint8_t reg_addr){
	uint8_t reg_data;
	
	TWI_START();
	TWI_MT_SLA_ACK();
	TWI_MT_DATA_ACK(reg_addr);
	TWI_R_START();
	TWI_MR_SLA_ACK();
	reg_data = TWI_READ_DATABYTE_NACK();
	TWI_STOP();
	return reg_data;
}

uint8_t rtc_read_sek(){
	uint8_t reg_data;
	uint8_t sek, sek_zehn, sek_ein;
	
	TWI_START();
	TWI_MT_SLA_ACK();
	TWI_MT_DATA_ACK(0x00);
	TWI_R_START();
	TWI_MR_SLA_ACK();
	reg_data = TWI_READ_DATABYTE_NACK();
	TWI_STOP();
		
	sek_zehn = (reg_data&0x70);
	sek_zehn >>= 4;
	sek_ein = (reg_data&0x0F);
	
	sek = sek_zehn*10 + sek_ein;
	
	return sek;
}

uint8_t rtc_read_min(){
	uint8_t reg_data;
	uint8_t min, min_zehn, min_ein;
	
	TWI_START();
	TWI_MT_SLA_ACK();
	TWI_MT_DATA_ACK(0x01);
	TWI_R_START();
	TWI_MR_SLA_ACK();
	reg_data = TWI_READ_DATABYTE_NACK();
	TWI_STOP();
	
	min_zehn = (reg_data&0x70);
	min_zehn >>= 4;
	min_ein = (reg_data&0x0F);
	
	min = min_zehn*10 + min_ein;
	
	return min;
}

uint8_t rtc_read_hour(){
	uint8_t reg_data;
	uint8_t hour, hour_zehn, hour_ein;
	
	TWI_START();
	TWI_MT_SLA_ACK();
	TWI_MT_DATA_ACK(0x02);
	TWI_R_START();
	TWI_MR_SLA_ACK();
	reg_data = TWI_READ_DATABYTE_NACK();
	TWI_STOP();
	
	hour_zehn = (reg_data&0x30);
	hour_zehn >>= 4;
	hour_ein = (reg_data&0x0F);
	
	hour = hour_zehn*10 + hour_ein;
	
	
	return hour;
}
