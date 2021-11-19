#ifndef CLOCK_H
#define CLOCK_H

#include "main.h"
#include "cmsis_os.h"
#include "rtc.h"
#include "lcd.h"
#include "WS2812B.h"
#include "usart.h"

extern uint8_t internet_flag;

extern RTC_DateTypeDef sdatestructure;
extern RTC_TimeTypeDef stimestructure;

void clock_init();
void calibrate_date_time();
void update_date_time();
void update_clock_ui_lcd();
void update_clock_ui_led();

#endif