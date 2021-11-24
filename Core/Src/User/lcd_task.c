#include "lcd_task.h"

void lcd_task_setup()
{
    macXPT2046_CS_DISABLE();

    LCD_set_brightness(999);
    LCD_INIT();

    // while( ! XPT2046_Touch_Calibrate () );

    LCD_GramScan(1);

    gallery_init();
}

void lcd_task_loop()
{
    char char_buf[50];
    static sys_mode_t last_mode;
    if (last_mode != system_mode)
    {
        LCD_Clear(0, 0, 240, 320, 0xffff);
    }
    last_mode = system_mode;

    system_mode = GALLERY;
    switch (system_mode)
    {
    case WELCOME:
        LCD_DrawString_2448_Rotate(108, 76, "WELCOME");
        LCD_DrawChinese(50, 112, BLUE);
        osDelay(2500);
        system_mode = CLOCK;
        break;

    case CLOCK:
        update_clock_ui_lcd();
        if (ucXPT2046_TouchFlag)
        {
            system_mode = MENU;
            ucXPT2046_TouchFlag = 0;
        }
        break;

    case MENU:
        lcd_draw_icon_clock(120, 25);
        lcd_draw_icon_game(0, 25);
        lcd_draw_icon_gallery(120, 170);
        lcd_draw_icon_music(0, 170);
        if (ucXPT2046_TouchFlag)
        {
            // LCD_DrawCross(touchscreen.x, touchscreen.y);
            if (touchscreen.x > 120 && touchscreen.y < 160)
            {
                system_mode = CLOCK;
            }
            else if (touchscreen.x > 120 && touchscreen.y > 160)
            {
                system_mode = GALLERY;
            }
            else if (touchscreen.x < 120 && touchscreen.y < 160)
            {
                system_mode = GAME;
            }
            else if (touchscreen.x < 120 && touchscreen.y > 160)
            {
                system_mode = MUSIC;
            }
            ucXPT2046_TouchFlag = 0;
        }
        break;

    case GAME:
        lcd_draw_icon_snake(60, 25);
        lcd_draw_icon_bird(60, 170);
        break;

    case GALLERY:
        gallery_slideshow();
        break;

    case SNAKE:
        break;

    case BIRD:
        break;

    case MUSIC:
        update_lcd_bins();
        break;

    case COMPASS:
        sprintf(char_buf, "x: %d ", accAngle.angleX);
        LCD_DrawString(0, 0, char_buf);
        sprintf(char_buf, "y: %d ", accAngle.angleY);
        LCD_DrawString(0, 80, char_buf);
        sprintf(char_buf, "z: %d ", compass_angle);
        LCD_DrawString(0, 160, char_buf);
        break;

    default:
        break;
    }

    osDelay(100);
}