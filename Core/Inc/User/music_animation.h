#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "main.h"
#include "cmsis_os.h"
#include "microphone.h"
#include "lcd.h"

// #define SLIDE_SPEED     1
// #define BRIGHTNESS      ((row+2)*2)

// void update_columns (uint8_t columns_height[PIXEL_COL]);

#define LCD_BIN_NUM         16

void update_bin_height ();
void lcd_update_bins ();

#endif