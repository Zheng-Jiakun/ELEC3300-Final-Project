#include "clock.h"

uint8_t internet_flag = 0;

uint8_t uart_data[6];

RTC_DateTypeDef sdatestructure;
RTC_TimeTypeDef stimestructure;

void clock_init()
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

    internet_flag = 1;
}

void update_date_time()
{
    HAL_RTC_GetTime(&hrtc, &stimestructure, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sdatestructure, RTC_FORMAT_BIN);
}

void draw_time(uint8_t x, uint8_t y, uint8_t digit_offset, uint16_t color)
{
    LCD_DrawChar_2448_Rotate(x, y + digit_offset * 0, color, stimestructure.Hours / 10 + '0');
    LCD_DrawChar_2448_Rotate(x, y + digit_offset * 1, color, stimestructure.Hours % 10 + '0');
    LCD_DrawChar_2448_Rotate(x, y + digit_offset * 2, color, ':');

    LCD_DrawChar_2448_Rotate(x, y + digit_offset * 3, color, stimestructure.Minutes / 10 + '0');
    LCD_DrawChar_2448_Rotate(x, y + digit_offset * 4, color, stimestructure.Minutes % 10 + '0');
    LCD_DrawChar_2448_Rotate(x, y + digit_offset * 5, color, ':');

    LCD_DrawChar_2448_Rotate(x, y + digit_offset * 6, color, stimestructure.Seconds / 10 + '0');
    LCD_DrawChar_2448_Rotate(x, y + digit_offset * 7, color, stimestructure.Seconds % 10 + '0');
}

void draw_date(uint8_t x, uint8_t y, uint8_t digit_offset, uint16_t color)
{
    LCD_DrawChar_2040_Rotate(x, y + digit_offset * 0, color, 2 + '0');
    LCD_DrawChar_2040_Rotate(x, y + digit_offset * 1, color, 0 + '0');
    LCD_DrawChar_2040_Rotate(x, y + digit_offset * 2, color, sdatestructure.Year / 10 + '0');
    LCD_DrawChar_2040_Rotate(x, y + digit_offset * 3, color, sdatestructure.Year % 10 + '0');
    LCD_DrawChar_2040_Rotate(x, y + digit_offset * 4, color, '-');

    LCD_DrawChar_2040_Rotate(x, y + digit_offset * 5, color, sdatestructure.Month / 10 + '0');
    LCD_DrawChar_2040_Rotate(x, y + digit_offset * 6, color, sdatestructure.Month % 10 + '0');
    LCD_DrawChar_2040_Rotate(x, y + digit_offset * 7, color, '-');

    LCD_DrawChar_2040_Rotate(x, y + digit_offset * 8, color, sdatestructure.Date / 10 + '0');
    LCD_DrawChar_2040_Rotate(x, y + digit_offset * 9, color, sdatestructure.Date % 10 + '0');
}

void update_clock_ui_lcd()
{
    // LCD_DrawChinese(120, 160, BLUE);

    draw_time(120, 40, 24 + 6, BLACK);
    draw_date(72, 35, 20 + 6, BLACK);

    if (internet_flag)
        lcd_draw_icon_wifi(200, 144);
}

void update_clock_ui_led()
{
    update_date_time();
    uint8_t pointer_h, pointer_m, pointer_s;
    if (stimestructure.Hours >= 12)
        pointer_h = (stimestructure.Hours - 12) * 2;
    else
        pointer_h = stimestructure.Hours * 2;
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