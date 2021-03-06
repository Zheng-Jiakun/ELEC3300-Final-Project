#ifndef _WS2812B_H_
#define _WS2812B_H_

#include "main.h"
#include "dma.h"
#include "tim.h"
#include "string.h"

#define LED_NUM 24

#define LED_MAX_BRIGHTNESS        255

typedef struct 
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;

extern color_t led_color[LED_NUM];
void WS2812_init();
void WS2812_update();
void set_led_brightness(uint8_t b);
void clear_all_led ();

#endif