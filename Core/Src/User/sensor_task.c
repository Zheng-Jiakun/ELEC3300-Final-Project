#include "sensor_task.h"

uint8_t eep_data = 0;

void sensor_task_setup()
{
    dht11_init();
    MPU6050_init();
    eeprom_init();
    // HMC5883L_init();
    // eeprom_write_byte(0, 123);
    // eeprom_read_byte(0, &eep_data);
    microphone_init();
    clock_init();
    misc_sensors_init();
}

void sensor_task_loop()
{
    switch (system_mode)
    {
    case CLOCK:
        dht11_read();
        break;

    case MENU:
        break;

    case GAME:
        break;

    case GALLERY:
        break;

    case SNAKE:
        dht11_read();
        MPU6050_update_data();
        break;

    case BIRD:
        dht11_read();
        break;

    case MUSIC:
        break;

    case COMPASS:
        MPU6050_update_data();
        // HMC5883L_update_data();
        break;

    default:
        break;
    }

    if (get_ldr_value() < 2000)
    {
        set_led_brightness(1);
        LCD_set_brightness(200);
    }
    else if (get_ldr_value() > 2200 && get_ldr_value() < 2400)
    {
        set_led_brightness(5);
        LCD_set_brightness(400);
    }
    else if (get_ldr_value() > 2600 && get_ldr_value() < 2800)
    {
        set_led_brightness(10);
        LCD_set_brightness(600);
    }
    else if (get_ldr_value() > 3000 && get_ldr_value() < 3200)
    {
        set_led_brightness(15);
        LCD_set_brightness(800);
    }
    else if (get_ldr_value() > 3700)
    {
        set_led_brightness(20);
        LCD_set_brightness(999);
    }
    
    vibration_service();
    buzzer_service();

    if (get_capkey_value() < 2000 || HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == GPIO_PIN_SET)
    {
        system_mode = MENU;
        set_vibration_flag();
        set_buzzer_flag();
    }
}