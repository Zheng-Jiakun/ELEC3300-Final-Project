#ifndef HMC5883L_H
#define HMC5883L_H

#include "main.h"
//#include "cmsis_os.h"
#include "iic.h"
#include "math.h"

extern uint16_t compass_angle;

void HMC5883L_init();
void HMC5883L_update_data();

#endif