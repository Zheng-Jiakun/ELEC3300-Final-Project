#include "music_animation.h"

#define ABS(x)      (((x)>0)?(x):-(x))

uint8_t lcd_bin_height[LCD_BIN_NUM];
uint8_t led_column_height;

void update_lcd_bin_height()
{
    for (uint8_t i = 0; i < LCD_BIN_NUM; i++)
    {
        lcd_bin_height[i] = fft_sample_result[i] / 100;
        if (lcd_bin_height[i] > 240)
        {
            lcd_bin_height[i] = 240;
        }
    }
}

void update_lcd_bins()
{
    // update_lcd_bin_height();
    lcd_bin_height[0]++;
    if (lcd_bin_height[0] > 254)
        lcd_bin_height[0] = 0;
    // LCD_Clear(0, 0, 240, 320, 0xffff);
    for (uint8_t i = 0; i < LCD_BIN_NUM; i++)
    {
        LCD_Clear(0, 320 / LCD_BIN_NUM * i, lcd_bin_height[i], 320 / LCD_BIN_NUM, 0x1234);
        LCD_Clear(lcd_bin_height[i], 320 / LCD_BIN_NUM * i, 240 - lcd_bin_height[i], 320 / LCD_BIN_NUM, 0xffff);
    }
    // static uint8_t last_column_height = 0;
    // if (led_column_height > LED_NUM/2)
    //     led_column_height = LED_NUM/2;
    // if (last_column_height > led_column_height)
    // {
    //     led_clear_pixel(last_column_height-1);
    //     last_column_height--;
    // }
    // else if (last_column_height < led_column_height)
    // {
    //     led_set_pixel(last_column_height);
    //     last_column_height++;
    // }
}

void led_clear_pixel(uint8_t index)
{
    led_color[index].r = 0;
    led_color[index].g = 0;
    led_color[index].b = 0;
}

void led_set_pixel(uint8_t index)
{
    uint8_t rainbow[LED_NUM / 2][3] = {
        {255, 255, 255},
        {139, 140, 255},
        {139, 0, 255},
        {0, 0, 255},
        {0, 127, 255},
        {0, 200, 150},
        {0, 255, 50},
        {100, 255, 0},
        {255, 255, 0},
        {255, 165, 0},
        {255, 50, 0},
        {255, 0, 0},
    };
    led_color[index].r = rainbow[index][0];
    led_color[index].g = rainbow[index][1];
    led_color[index].b = rainbow[index][2];
}

void led_fill_mirror ()
{
    for (uint8_t i = 0; i < LED_NUM/2; i++)
    {
        led_color[LED_NUM-1-i].r = led_color[i].r;
        led_color[LED_NUM-1-i].g = led_color[i].g;
        led_color[LED_NUM-1-i].b = led_color[i].b;
    }
}

void update_led_column_height()
{
    // uint32_t adc = 0;
    // for (uint16_t i = 0; i < RAW_SAMPLE_NUM; i++)
    //     adc += ABS(adc_raw_result[i] - 1550);
    // led_column_height = adc / RAW_SAMPLE_NUM * 0.00001f;
    led_column_height = ABS(adc_raw_result[0] - 1550) * 0.05f;
}

void music_update_led ()
{
    update_led_column_height();
    static uint8_t last_column_height = 0;
    if (led_column_height > LED_NUM/2)
        led_column_height = LED_NUM/2;
    if (last_column_height > led_column_height)
    {
        led_clear_pixel(last_column_height-1);
        last_column_height--;
    }
    else if (last_column_height < led_column_height)
    {
        led_set_pixel(last_column_height);
        last_column_height++;
    }
    led_fill_mirror();
    WS2812_update();
    // HAL_Delay(1);
}