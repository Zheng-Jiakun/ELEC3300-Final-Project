#ifndef MISC_SENSORS
#define MISC_SENSORS

#include "main.h"
//#include "cmsis_os.h"
#include "adc.h"
#include "lcd.h"
#include "WS2812B.h"

#define ADC_CH_CAPKEY   0
#define ADC_CH_LDR      1
#define ADC_CH_JOYX     2
#define ADC_CH_JOYY     3

void misc_sensors_init();
void misc_sensors_deinit();
uint16_t get_ldr_value();
uint16_t get_capkey_value();
uint16_t get_joyx_value();
uint16_t get_joyy_value();
void set_vibration_flag();
void vibration_service();
void set_buzzer_flag();
void buzzer_service();
void auto_brightness_service ();

#endif