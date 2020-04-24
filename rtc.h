/*
 * rtc.h
 *
 * Created: 19.04.2020 21:01:46
 *  Author: David
 */ 


#ifndef RTC_H_
#define RTC_H_

#ifndef F_CPU
#define F_CPU 8000000
#endif

#ifndef SLA_ADDR
#define SLA_ADDR 0xDE
#endif

#ifndef RTC_SER_FREQ
#define RTC_SER_FREQ 100000
#endif

#include <avr/io.h>
#include <avr/delay.h>
#include <util/twi.h>

void init_RTC();
void TWI_START();
void TWI_MT_SLA_ACK();
void TWI_MT_DATA_ACK(uint8_t send_data);
void TWI_R_START();
void TWI_MR_SLA_ACK();
uint8_t TWI_READ_DATABYTE_NACK();
void TWI_STOP();
void rtc_set_init();
uint8_t rtc_read_reg(uint8_t reg_addr);
uint8_t rtc_read_sek();
uint8_t rtc_read_min();
uint8_t rtc_read_hour();

#endif /* RTC_H_ */