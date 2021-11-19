#include "sensor_task.h"

uint8_t eep_data = 0;

void sensor_task_setup()
{
    dht11_init();
    MPU6050_init();
    eeprom_init();
    // eeprom_write_byte(0, 123);
    // eeprom_read_byte(0, &eep_data);
    microphone_init();
    clock_init();
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

    default:
        break;
    }
}