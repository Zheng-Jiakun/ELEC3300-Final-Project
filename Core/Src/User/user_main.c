#include "user_main.h"

void user_setup()
{
    LCD_INIT();
    LCD_set_brightness(999);
    WS2812_init();
    set_led_brightness(50);
    dht11_init();
    MPU6050_init();
    eeprom_init();
    // HMC5883L_init();
    clock_init();
    misc_sensors_init();
}

void user_loop()
{
    system_mode = SNAKE;
    char char_buf[50];
    static sys_mode_t last_mode;
    if (last_mode != system_mode)
    {
        LCD_Clear(0, 0, 240, 320, 0xffff);
        clear_all_led();

        if (system_mode == MUSIC && last_mode != MUSIC)
        {
            microphone_init();
        }
        else if (system_mode != MUSIC && last_mode == MUSIC)
        {
            microphone_init();
        }

        if (system_mode != GALLERY && last_mode == GALLERY)
        {
            misc_sensors_init();
        }
        else if (system_mode == GALLERY && last_mode != GALLERY)
        {
            microphone_deinit();
            misc_sensors_deinit();
        }

        if (system_mode == BIRD && last_mode != BIRD)
        {
            microphone_init();
        }
        else if (system_mode != BIRD && last_mode == BIRD)
        {
            microphone_init();
        }
    }
    last_mode = system_mode;

    switch (system_mode)
    {
    case WELCOME:
        LCD_DrawString_2448_Rotate(108, 76, "WELCOME");
        LCD_DrawChinese(50, 112, BLUE);
        HAL_Delay(2500);
        system_mode = CLOCK;
        break;

    case CLOCK:
        dht11_read();
        update_clock_ui_led();
        update_clock_ui_lcd();
        if (ucXPT2046_TouchFlag)
        {
            system_mode = MENU;
            ucXPT2046_TouchFlag = 0;
        }
        break;

    case MENU:
        for (uint8_t i = 0; i < LED_NUM / 2; i++)
        {
            led_set_pixel(i);
            led_fill_mirror();
        }
        WS2812_update();

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
        for (uint8_t i = 0; i < LED_NUM / 2; i++)
        {
            led_set_pixel(i);
            led_fill_mirror();
        }
        WS2812_update();

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
        for (uint8_t i = 0; i < LED_NUM / 2; i++)
        {
            led_set_pixel(i);
            led_fill_mirror();
        }
        WS2812_update();

        gallery_slideshow();

        if (ucXPT2046_TouchFlag)
        {
            system_mode = MENU;
        }
        break;

    case SNAKE:
        MPU6050_update_data();
        dht11_read();
        game_snake();
        break;

    case BIRD:
        dht11_read();
        game_bird();
        break;

    case MUSIC:
        update_lcd_bins();
        music_update_led();
        
        if (ucXPT2046_TouchFlag)
        {
            system_mode = MENU;
        }
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

    vibration_service();
    buzzer_service();
    auto_brightness_service();

    if (get_capkey_value() < 2000 || HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_SET)
    {
        system_mode = MENU;
        set_vibration_flag();
        set_buzzer_flag();
    }
}