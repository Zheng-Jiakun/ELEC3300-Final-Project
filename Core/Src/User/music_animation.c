#include "music_animation.h"

uint8_t bin_height[LCD_BIN_NUM];

void update_bin_height ()
{
    for (uint8_t i = 0; i < LCD_BIN_NUM; i++)
    {
        bin_height[i] = fft_sample_result[i] / 100;
        if (bin_height[i] > 240)
        {
            bin_height[i] = 240;
        }
    }
}

void lcd_update_bins ()
{
    // LCD_Clear(0, 0, 240, 320, 0xffff);
    for (uint8_t i = 0; i < LCD_BIN_NUM; i++)
    {
        LCD_Clear(0, 320/LCD_BIN_NUM*i, bin_height[i], 320/LCD_BIN_NUM, 0x1234);
        LCD_Clear(bin_height[i], 320/LCD_BIN_NUM*i, 240-bin_height[i], 320/LCD_BIN_NUM, 0xffff);
    }
    osDelay(5);
}

// void clear_pixel (uint8_t row, uint8_t col)
// {
//     display_frame_buffer[row][col].r = 0;
//     display_frame_buffer[row][col].g = 0;
//     display_frame_buffer[row][col].b = 0;
// }

// void set_pixel (uint8_t row, uint8_t col)
// {
//     if (col >= 14 && col < 16)
//     {
//         display_frame_buffer[row][col].r = 255/BRIGHTNESS;
//         display_frame_buffer[row][col].g = 100/BRIGHTNESS;
//         display_frame_buffer[row][col].b = 255/BRIGHTNESS;
//     }
//     else if (col >= 12 && col < 14)
//     {
//         display_frame_buffer[row][col].r = 148/BRIGHTNESS;
//         display_frame_buffer[row][col].g = 0/BRIGHTNESS;
//         display_frame_buffer[row][col].b = 211/BRIGHTNESS;
//     }
//     else if (col >= 10 && col < 12)
//     {
//         display_frame_buffer[row][col].r = 75/BRIGHTNESS;
//         display_frame_buffer[row][col].g = 0/BRIGHTNESS;
//         display_frame_buffer[row][col].b = 130/BRIGHTNESS;
//     }
//     else if (col >= 8 && col < 10)
//     {
//         display_frame_buffer[row][col].r = 0/BRIGHTNESS;
//         display_frame_buffer[row][col].g = 0/BRIGHTNESS;
//         display_frame_buffer[row][col].b = 255/BRIGHTNESS;
//     }
//     else if (col >= 6 && col < 8)
//     {
//         display_frame_buffer[row][col].r = 0/BRIGHTNESS;
//         display_frame_buffer[row][col].g = 255/BRIGHTNESS;
//         display_frame_buffer[row][col].b = 0/BRIGHTNESS;
//     }
//     else if (col >= 4 && col < 6)
//     {
//         display_frame_buffer[row][col].r = 255/BRIGHTNESS;
//         display_frame_buffer[row][col].g = 255/BRIGHTNESS;
//         display_frame_buffer[row][col].b = 0/BRIGHTNESS;
//     }
//     else if (col >= 2 && col < 4)
//     {
//         display_frame_buffer[row][col].r = 255/BRIGHTNESS;
//         display_frame_buffer[row][col].g = 127/BRIGHTNESS;
//         display_frame_buffer[row][col].b = 0/BRIGHTNESS;
//     }
//     else if (col >= 0 && col < 2)
//     {
//         display_frame_buffer[row][col].r = 255/BRIGHTNESS;
//         display_frame_buffer[row][col].g = 0/BRIGHTNESS;
//         display_frame_buffer[row][col].b = 0/BRIGHTNESS;
//     }
// }

// void update_columns (uint8_t columns_height[PIXEL_COL])
// {
//     static uint8_t Lastcolumns_height[PIXEL_COL];
//     for (uint8_t col = 0; col < PIXEL_COL; col++)
//     {
//         if (columns_height[col] > PIXEL_ROW)
//             columns_height[col] = PIXEL_ROW;
//         if (Lastcolumns_height[col] > columns_height[col])
//         {
//             clear_pixel(Lastcolumns_height[col]-1, col);
//             Lastcolumns_height[col]--;
//         }
//         else if (Lastcolumns_height[col] < columns_height[col])
//         {
//             set_pixel(Lastcolumns_height[col], col);
//             Lastcolumns_height[col]++;
//         }
//         osDelay(SLIDE_SPEED);
//     }
// }