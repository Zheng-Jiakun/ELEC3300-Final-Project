#ifndef MK_DHT11_H_
#define MK_DHT11_H_

#include "main.h"
//#include "cmsis_os.h"
#include "gpio.h"
#include "tim.h"
#include "string.h"

extern uint8_t temperature;
extern uint8_t humidity;

typedef struct {
	GPIO_TypeDef* port;	///GPIO Port ex:GPIOA
	uint16_t pin; ///GPIO pin ex:GPIO_PIN_2
	TIM_HandleTypeDef *htim; /// timer for measure time
} dht11_t;

void dht11_init();
void set_data_pin_output();
void set_data_pin_input();
uint8_t dht11_read();

#endif