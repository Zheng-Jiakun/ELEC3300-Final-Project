#include "lcd_task.h"

const uint8_t image[][3] = {
#include "image.h"
};

void lcd_task_setup()
{
    // LCD_INIT();
    // LCD_DrawString(120, 160, "WELCOME");
    // LCD_OpenWindow(0, 0, 128, 128);
    // LCD_Write_Cmd ( CMD_set_pixel );
    // for (uint16_t i = 0; i < 128; i++)
    // {
    //     for (uint16_t j = 0; j < 128; j++)
    //     {
    //         uint16_t color = (image[j+i*128][0]*0x1f/0xff & 0x1f) << 11 | (image[j+i*128][1]*0x3f/0xff & 0x3f) << 5 | (image[j+i*128][2]*0x1f/0xff & 0x1f);
    //         // LCD_DrawDot(i, j, color);
    // 	    LCD_Write_Data ( color );
    //     }
    // }
    macXPT2046_CS_DISABLE();

    LCD_INIT();
    LCD_set_brightness(999);

    // LCD_Clear(50, 80, 140, 70, RED);
    // LCD_DrawString(68, 100, "TOUCHPAD DEMO");
    // HAL_Delay(2000);

    // while( ! XPT2046_Touch_Calibrate () );

    LCD_GramScan(1);
    // LCD_Clear(0, 0, 240, 320, GREY);
    // LCD_Clear(90, 230, 60, 60, BLUE);
}

void lcd_task_loop()
{
    if (ucXPT2046_TouchFlag)
    {
        LCD_Clear(0, 0, 240, 320, 0xffff);
        LCD_DrawCross(touchscreen.x, touchscreen.y);
        ucXPT2046_TouchFlag = 0;
    }
    osDelay(100);
    // update_bin_height();
    // lcd_update_bins ();
}