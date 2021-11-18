#ifndef LCD_TASK
#define LCD_TASK

#include "main.h"
#include "lcd.h"
#include "music_animation.h"
#include "cmsis_os.h"
#include "xpt2046.h"

void lcd_task_setup();
void lcd_task_loop();

#endif