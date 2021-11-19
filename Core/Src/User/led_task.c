#include "led_task.h"

void led_task_setup ()
{
	WS2812_init();
    set_led_brightness(10);
}

void led_task_loop ()
{
}