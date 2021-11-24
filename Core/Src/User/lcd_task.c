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
    static sys_mode_t last_mode;
    if (last_mode != system_mode)
    {
        LCD_Clear(0, 0, 240, 320, 0xffff);
    }
    last_mode = system_mode;

    system_mode = SNAKE;
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
        if (ucXPT2046_TouchFlag)
        {
            // LCD_DrawCross(touchscreen.x, touchscreen.y);
            if (touchscreen.y < 160)
            {
                system_mode = SNAKE;
            }
            else if (touchscreen.y > 160)
            {
                system_mode = BIRD;
            }
            ucXPT2046_TouchFlag = 0;
        }
        break;

    case GALLERY:
        break;

    case SNAKE:
        game_snake();
        break;

    case BIRD:
        game_bird();
        
        break;

    case MUSIC:
        update_lcd_bins();
        break;

    default:
        break;
    }

    HAL_ADC_Start(&hadc2);
    uint16_t cap_key = HAL_ADC_GetValue(&hadc2);
    if (cap_key < 2000 || HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_SET)
    {
        system_mode = MENU;
    }

    osDelay(100);
}