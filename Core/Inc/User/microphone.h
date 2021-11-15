#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "main.h"
#include "adc.h"
#include "tim.h"
#include "arm_math.h"

#define FFT_SAMPLE_NUM    16

#define RAW_SAMPLE_NUM    512
#define FFT_NUM     RAW_SAMPLE_NUM/2

extern float fft_magnitude[FFT_NUM];
extern uint16_t fft_sample_result[FFT_SAMPLE_NUM];

void microphone_init ();
void process_fft ();
// void FFTResultFilter ();


#endif