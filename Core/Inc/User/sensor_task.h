#ifndef SNESOR_TASK
#define SENSOR_TASK

#include "main.h"
#include "MPU6050.h"
#include "AT24C02.h"
#include "microphone.h"
#include "DHT11.h"

void sensor_task_setup();
void sensor_task_loop();

#endif