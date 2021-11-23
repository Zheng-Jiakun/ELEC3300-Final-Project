#ifndef SNESOR_TASK
#define SENSOR_TASK

#include "main.h"
#include "MPU6050.h"
#include "AT24C02.h"
#include "microphone.h"
#include "DHT11.h"
#include "clock.h"
#include "HMC5883L.h"
#include "adc.h"
#include "misc_sensors.h"
#include "lcd.h"
#include "WS2812B.h"
#include "xpt2046.h"

void sensor_task_setup();
void sensor_task_loop();

#endif