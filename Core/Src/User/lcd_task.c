#include "lcd_task.h"

void lcd_task_setup()
{
    // LCD_INIT();
    // LCD_DrawString(120, 160, "WELCOME");
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
    update_clock_ui_lcd();
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