#ifndef GAME_H
#define GAME_H

#include "main.h"
#include "cmsis_os.h"
#include "lcd.h"
#include "MPU6050.h"
#include "DHT11.h"
#include "stdio.h"
#include "stdlib.h"


typedef enum {
    GAME_INIT = 0,
    GAME_PLAY,
    GAME_END,
} game_state_t;

void game_snake ();
void game_bird ();

#endif