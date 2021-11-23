#include "led_task.h"

void led_task_setup()
{
    WS2812_init();
    set_led_brightness(50);
}

void led_task_loop()
{
    static sys_mode_t last_mode;
    if (last_mode != system_mode)
    {
        clear_all_led();
    }
    last_mode = system_mode;

    switch (system_mode)
    {
    case CLOCK:
        update_clock_ui_led();
        break;

    case MENU:
        for (uint8_t i = 0; i < LED_NUM / 2; i++)
        {
            led_set_pixel(i);
            led_fill_mirror ();
        }
        WS2812_update();
        break;

    case GAME:
        for (uint8_t i = 0; i < LED_NUM / 2; i++)
        {
            led_set_pixel(i);
            led_fill_mirror ();
        }
        WS2812_update();
        break;

    case GALLERY:
        for (uint8_t i = 0; i < LED_NUM / 2; i++)
        {
            led_set_pixel(i);
            led_fill_mirror ();
        }
        WS2812_update();
        break;

    case SNAKE:
        break;

    case BIRD:
        break;

    case MUSIC:
        music_update_led();
        break;

    default:
        break;
    }
}