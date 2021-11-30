#include "misc_sensors.h"

uint16_t adc3_data[4];
uint8_t vibration_flag = 0, buzzer_flag = 0;

void misc_sensors_init()
{
    HAL_ADC_Start_DMA(&hadc3, (uint32_t *)adc3_data, sizeof(adc3_data));
}

void misc_sensors_deinit()
{
    HAL_ADC_Stop_DMA(&hadc3);
}

uint16_t get_ldr_value()
{
    return adc3_data[ADC_CH_LDR];
}

uint16_t get_capkey_value()
{
    return adc3_data[ADC_CH_CAPKEY];
}

uint16_t get_joyx_value()
{
    return adc3_data[ADC_CH_JOYX];
}

uint16_t get_joyy_value()
{
    return adc3_data[ADC_CH_JOYY];
}

void set_vibration_flag()
{
    vibration_flag = 1;
}

void set_buzzer_flag()
{
    buzzer_flag = 1;
}

void buzzer_service()
{
    static uint32_t start_tick;
    static uint8_t start_flag = 0;
    if (start_flag == 0 && buzzer_flag == 1)
    {
        HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
        start_tick = HAL_GetTick();
        start_flag = 1;
    }
    else if (start_flag == 1 && HAL_GetTick() - start_tick > 2)
    {
        HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
        start_flag = 0;
        buzzer_flag = 0;
    }
}

void vibration_service()
{
    static uint32_t start_tick;
    static uint8_t start_flag = 0;
    if (start_flag == 0 && vibration_flag == 1)
    {
        HAL_GPIO_WritePin(MOTOR_GPIO_Port, MOTOR_Pin, GPIO_PIN_SET);
        start_tick = HAL_GetTick();
        start_flag = 1;
    }
    else if (start_flag == 1 && HAL_GetTick() - start_tick > 200)
    {
        HAL_GPIO_WritePin(MOTOR_GPIO_Port, MOTOR_Pin, GPIO_PIN_RESET);
        start_flag = 0;
        vibration_flag = 0;
    }
}

void auto_brightness_service ()
{
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
    else if (get_ldr_value() > 3000 && get_ldr_value() < 3500)
    {
        set_led_brightness(15);
        LCD_set_brightness(800);
    }
    else if (get_ldr_value() > 3500)
    {
        set_led_brightness(20);
        LCD_set_brightness(999);
    }
}