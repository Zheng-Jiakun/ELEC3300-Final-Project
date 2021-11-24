#include "music_animation.h"

#define ABS(x) (((x) > 0) ? (x) : -(x))

uint8_t lcd_bin_height[LCD_BIN_NUM];
uint8_t led_column_height;

void lcd_set_block(uint8_t height, uint8_t column)
{
    uint8_t color_rgb[LCD_BIN_NUM][3] = {
        {200, 150, 255},
        {139, 140, 220},
        {100, 0, 230},
        {0, 50, 240},
        {0, 127, 255},
        {0, 200, 150},
        {0, 225, 100},
        {0, 255, 50},
        {50, 255, 30},
        {80, 255, 10},
        {100, 255, 0},
        {150, 255, 0},
        {200, 200, 0},
        {255, 165, 0},
        {255, 50, 0},
        {255, 0, 0},
    };
    uint16_t color[LCD_BIN_NUM];
    for (uint8_t i = 0; i < LCD_BIN_NUM; i++)
    {
        color[i] = (color_rgb[i][0] * 0x1f / 0xff & 0x1f) << 11 
        | (color_rgb[i][1] * 0x3f / 0xff & 0x3f) << 5 
        | (color_rgb[i][2] * 0x1f / 0xff & 0x1f);
    }
    LCD_Clear(height * 20 + 1, column * 20 + 1, 18, 18, color[column]);
}

void lcd_clear_block(uint8_t height, uint8_t column)
{
    LCD_Clear(height * 20 + 1, column * 20 + 1, 18, 18, 0xffff);
}

void update_lcd_bin_height()
{
    for (uint8_t i = 0; i < LCD_BIN_NUM; i++)
    {
        lcd_bin_height[i] = fft_sample_result[i] / 500;
        if (lcd_bin_height[i] > 12)
        {
            lcd_bin_height[i] = 12;
        }
    }
}

void update_lcd_bins()
{
    update_lcd_bin_height();

    static uint8_t last_column_height[LCD_BIN_NUM];
    for (uint8_t i = 0; i < LCD_BIN_NUM; i++)
    {
        if (lcd_bin_height[i] > LED_NUM / 2)
            lcd_bin_height[i] = LED_NUM / 2;
        if (last_column_height[i] > lcd_bin_height[i])
        {
            lcd_clear_block(last_column_height[i] - 1, i);
            last_column_height[i]--;
        }
        else if (last_column_height[i] < lcd_bin_height[i])
        {
            lcd_set_block(last_column_height[i], i);
            last_column_height[i]++;
        }
    }
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

void led_fill_mirror()
{
    for (uint8_t i = 0; i < LED_NUM / 2; i++)
    {
        led_color[LED_NUM - 1 - i].r = led_color[i].r;
        led_color[LED_NUM - 1 - i].g = led_color[i].g;
        led_color[LED_NUM - 1 - i].b = led_color[i].b;
    }
}

void update_led_column_height()
{
    uint32_t fft_average = 0;
    for (uint16_t i = 0; i < FFT_SAMPLE_NUM; i++)
        fft_average += fft_sample_result[i];
    led_column_height = fft_average / FFT_SAMPLE_NUM * 0.005f;
}

void music_update_led()
{
    update_led_column_height();
    static uint8_t last_column_height = 0;
    if (led_column_height > LED_NUM / 2)
        led_column_height = LED_NUM / 2;
    if (last_column_height > led_column_height)
    {
        led_clear_pixel(last_column_height - 1);
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