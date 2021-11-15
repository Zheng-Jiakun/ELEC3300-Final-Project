#include "user_isr.h"

void adc1_dma_isr ()
{
    process_fft();
}