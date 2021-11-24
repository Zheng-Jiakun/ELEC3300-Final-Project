#ifndef LED_TASK
#define LED_TASK

#include "main.h"
#include "WS2812B.h"
#include "cmsis_os.h"
#include "music_animation.h"
#include "clock.h"
#include "game.h"

void led_task_setup();
void led_task_loop();

#endif