#include "led_task.h"

void led_task_setup ()
{
	WS2812_init();
    set_led_brightness(10);
}

void led_task_loop ()
{
    // music_update_led();
    update_clock_ui_lcd();
}