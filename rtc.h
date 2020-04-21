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

#ifndef RTC_SDA
#define RTC_SDA PC0
#endif

#ifndef RTC_SCL
#define RTC_SCL PC1
#endif

#ifndef RTC_SER_FREQ
#define RTC_SER_FREQ 100000
#endif

#include <avr/io.h>
#include <avr/delay.h>

void init_RTC();
int get_ack();
void write_byte(uint8_t buff_foo);
void write_register(uint8_t reg, uint8_t val);
uint8_t read_byte();
uint8_t read_register(uint8_t reg);
void rtc_set_init();


#endif /* RTC_H_ */