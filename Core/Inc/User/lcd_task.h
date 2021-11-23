#ifndef LCD_TASK
#define LCD_TASK

#include "main.h"
#include "lcd.h"
#include "music_animation.h"
#include "cmsis_os.h"
#include "xpt2046.h"
#include "clock.h"
#include "adc.h"
#include "stdio.h"
#include "stdlib.h"
#include "MPU6050.h"
#include "HMC5883L.h"
#include "misc_sensors.h"

void lcd_task_setup();
void lcd_task_loop();

#endif