#include "sensor_task.h"

uint8_t eep_data = 0;

void sensor_task_setup ()
{
    dht11_init();
    MPU6050_init();
    eeprom_init();
    eeprom_write_byte(0, 123);
    eeprom_read_byte(0, &eep_data);
    microphone_init();
}

void sensor_task_loop ()
{
    MPU6050_update_data();
    dht11_read();
}