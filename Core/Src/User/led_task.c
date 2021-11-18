#include "led_task.h"

#define MAX_BRIGHTNESS        10

void led_task_setup ()
{
	WS2812_Init();
}

void led_task_loop ()
{
    for (uint8_t i = 0; i < LED_NUM; i++)
    {
        LEDColor[i].r = (HAL_GetTick() / 5) % MAX_BRIGHTNESS;
        LEDColor[i].g = (HAL_GetTick() * 3) % MAX_BRIGHTNESS;
        LEDColor[i].b = (HAL_GetTick() * 2) % MAX_BRIGHTNESS;
        WS2812_Update();
        osDelay(500);
    }
}