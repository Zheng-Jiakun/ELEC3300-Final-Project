#ifndef GAME_H
#define GAME_H

#include "main.h"
// #include "cmsis_os.h"
#include "lcd.h"
#include "MPU6050.h"
#include "DHT11.h"
#include "stdio.h"
#include "stdlib.h"
#include "xpt2046.h"
#include "AT24C02.h"
#include "WS2812B.h"
#include "music_animation.h"
#include "misc_sensors.h"

#define   ANGLE_THRESHOLD           10
#define   MIC_THRESHOLD             1500
#define   JOYSTICK_THRESHOLD        1000


typedef enum {
    GAME_INIT = 0,
    GAME_PLAY,
    GAME_END,
} game_state_t;

void game_snake ();
void game_bird ();

#endif