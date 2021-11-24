#ifndef USER_MAIN_H
#define USER_MAIN_H


#include "main.h"
#include "MPU6050.h"
#include "AT24C02.h"
#include "microphone.h"
#include "DHT11.h"
#include "HMC5883L.h"
#include "adc.h"
#include "misc_sensors.h"
#include "lcd.h"
#include "gallery.h"
#include "WS2812B.h"
#include "music_animation.h"
#include "xpt2046.h"
#include "stdio.h"
#include "stdlib.h"
#include "clock.h"

void user_setup();
void user_loop();

#endif