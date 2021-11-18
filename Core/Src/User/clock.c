#include "clock.h"

uint8_t uart_data[6];

RTC_DateTypeDef sdatestructure;
RTC_TimeTypeDef stimestructure;

void clock_init ()
{
    HAL_UART_Receive_DMA(&huart3, uart_data, sizeof(uart_data));
}

void calibrate_date_time()
{
    sdatestructure.Year = uart_data[0];
    sdatestructure.Month = uart_data[1];
    sdatestructure.Date = uart_data[2];
    stimestructure.Hours = uart_data[3];
    stimestructure.Minutes = uart_data[4];
    stimestructure.Seconds = uart_data[5];
    HAL_RTC_SetTime(&hrtc, &stimestructure, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &sdatestructure, RTC_FORMAT_BIN);
}

void update_date_time()
{
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BIN);
}


void update_clock_ui_lcd()
{
    update_date_time();
    uint8_t pointer_h, pointer_m, pointer_s;
    pointer_h = stimestructure.Hours / 2 * 2;
    pointer_m = stimestructure.Minutes * 24 / 60;
    pointer_s = stimestructure.Seconds * 24 / 60;

    clear_all_led();
    if (pointer_h < LED_NUM / 2)
        pointer_h += LED_NUM / 2;
    else
        pointer_h -= LED_NUM / 2;

    if (pointer_m < LED_NUM / 2)
        pointer_m += LED_NUM / 2;
    else
        pointer_m -= LED_NUM / 2;

    if (pointer_s < LED_NUM / 2)
        pointer_s += LED_NUM / 2;
    else
        pointer_s -= LED_NUM / 2;

    led_color[pointer_h].r = 255;
    led_color[pointer_m].g = 255;
    led_color[pointer_s].b = 255;
    WS2812_update();
}

void update_clock_ui_led()
{
}