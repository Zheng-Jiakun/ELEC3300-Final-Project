#ifndef _WS2812B_H_
#define _WS2812B_H_

#include "stm32f1xx_hal.h"

#define LED_NUM 64

typedef struct 
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;

extern color_t LEDColor[LED_NUM];
void WS2812_Init();
void WS2812_Update();

#endif