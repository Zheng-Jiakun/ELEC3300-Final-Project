#include "led_task.h"

void led_task_setup ()
{
	WS2812_Init();
}

void led_task_loop ()
{
    WS2812_Update();
}