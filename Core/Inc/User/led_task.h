#ifndef LED_TASK
#define LED_TASK

#include "main.h"
#include "WS2812B.h"
#include "cmsis_os.h"

void led_task_setup();
void led_task_loop();

#endif