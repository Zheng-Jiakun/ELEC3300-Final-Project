#include "DHT11.h"

dht11_t dht;

uint8_t temperature, humidity;

void dht11_init(){
	dht.htim = &htim6;
	dht.port = DHT11_DATA_GPIO_Port;
	dht.pin = DHT11_DATA_Pin;
}

void set_data_pin_output()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = dht.pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(dht.port, &GPIO_InitStruct);
}

void set_data_pin_input()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = dht.pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(dht.port, &GPIO_InitStruct);
}

uint8_t dht11_read()
{
	uint16_t mTime1 = 0, mTime2 = 0, mBit = 0;
	uint8_t RH_int = 0, RH_dec = 0, T_int = 0, T_dec = 0, parity = 0;
	uint8_t mData[40];

	//start comm
	set_data_pin_output();			//set pin direction as input
	HAL_GPIO_WritePin(dht.port, dht.pin, GPIO_PIN_RESET);
	HAL_Delay(18);					//wait 18 ms in Low state
	__disable_irq();	//disable all interupts to do only read dht otherwise miss timer
	HAL_TIM_Base_Start(dht.htim); //start timer
	set_data_pin_input();
	//check dht answer
	__HAL_TIM_SET_COUNTER(dht.htim, 0);				//set timer counter to zero
	while(HAL_GPIO_ReadPin(dht.port, dht.pin) == GPIO_PIN_SET){
		if((uint16_t)__HAL_TIM_GET_COUNTER(dht.htim) > 500){
			__enable_irq();
			return 0;
		}
	}
	__HAL_TIM_SET_COUNTER(dht.htim, 0);
	while(HAL_GPIO_ReadPin(dht.port, dht.pin) == GPIO_PIN_RESET){
		if((uint16_t)__HAL_TIM_GET_COUNTER(dht.htim) > 500){
			__enable_irq();
			return 0;
		}
	}
	mTime1 = (uint16_t)__HAL_TIM_GET_COUNTER(dht.htim);
	__HAL_TIM_SET_COUNTER(dht.htim, 0);
	while(HAL_GPIO_ReadPin(dht.port, dht.pin) == GPIO_PIN_SET){
		if((uint16_t)__HAL_TIM_GET_COUNTER(dht.htim) > 500){
			__enable_irq();
			return 0;
		}
	}
	mTime2 = (uint16_t)__HAL_TIM_GET_COUNTER(dht.htim);

	//if answer is wrong return
	if(mTime1 < 75 && mTime1 > 85 && mTime2 < 75 && mTime2 > 85)
	{
		__enable_irq();
		return 0;
	}

//	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
	for(int j = 0; j < 40; j++)
	{
		__HAL_TIM_SET_COUNTER(dht.htim, 0);
		while(HAL_GPIO_ReadPin(dht.port, dht.pin) == GPIO_PIN_RESET){
			if((uint16_t)__HAL_TIM_GET_COUNTER(dht.htim) > 500){
				__enable_irq();
				return 0;
			}

		}
		__HAL_TIM_SET_COUNTER(dht.htim, 0);
		while(HAL_GPIO_ReadPin(dht.port, dht.pin) == GPIO_PIN_SET){
			if((uint16_t)__HAL_TIM_GET_COUNTER(dht.htim) > 500){
				__enable_irq();
				return 0;
			}

		}
		mTime1 = (uint16_t)__HAL_TIM_GET_COUNTER(dht.htim);

		//check pass time in high state
		//if pass time 25uS set as LOW
		if(mTime1 > 20 && mTime1 < 30)
		{
			mBit = 0;
		}
		else if(mTime1 > 60 && mTime1 < 80) //if pass time 70 uS set as HIGH
		{
			 mBit = 1;
		}

		//set i th data in data buffer
		mData[j] = mBit;

	}

	HAL_TIM_Base_Stop(dht.htim); //stop timer
	__enable_irq(); //enable all interrupts

	//get hum value from data buffer
	for(int i = 0; i < 8; i++)
	{
		RH_int += mData[i];
		RH_int <<= 1;
	}
	for(int i = 8; i < 16; i++)
	{
		RH_dec += mData[i];
		RH_dec <<= 1;
	}
	// memcpy(&humidity, &value_buffer, sizeof(value_buffer));

	//get temp value from data buffer
	for(int i = 16; i < 24; i++)
	{
		T_int += mData[i];
		T_int <<= 1;
	}
	for(int i = 24; i < 32; i++)
	{
		T_dec += mData[i];
		T_dec <<= 1;
	}
	// memcpy(&temperature, &value_buffer, sizeof(value_buffer));

	//get parity value from data buffer
	for(int i = 32; i < 40; i++)
	{
		parity += mData[i];
		parity <<= 1;
	}

	if (RH_int + RH_dec + T_int + T_dec == parity)
	{
		humidity = RH_int >> 1;
		temperature = T_int >> 1;
	}


	return 1;
}