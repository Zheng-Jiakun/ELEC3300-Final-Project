#include "user_isr.h"

void adc1_dma_isr()
{
    process_fft();
}

void exti4_isr()
{
    if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_4) != RESET)
    {
        check_touchscreen();
    }
}