#include "sensor_task.h"

void sensor_task_setup ()
{
    MPU6050_init();
}

void sensor_task_loop ()
{
    MPU6050_update_data();
}