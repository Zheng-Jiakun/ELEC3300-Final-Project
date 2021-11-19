#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "main.h"
#include "cmsis_os.h"
#include "microphone.h"
#include "lcd.h"
#include "WS2812B.h"

// #define SLIDE_SPEED     1
// #define BRIGHTNESS      ((row+2)*2)

// void music_update_led (uint8_t columns_height[PIXEL_COL]);

#define LCD_BIN_NUM         16

void update_lcd_bin_height ();
void update_lcd_bins ();
void update_led_column_height();
void music_update_led ();
void led_set_pixel(uint8_t index);
void led_fill_mirror ();

#endif