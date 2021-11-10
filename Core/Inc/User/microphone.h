#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "main.h"
#include "adc.h"

// #include "arm_math.h"
// #include "arm_const_structs.h"

#define FFT_SAMPLE_NUM    16

#define RAW_SAMPLE_NUM  2048
#define FFT_NUM     RAW_SAMPLE_NUM/2

extern float fft_magnitude[FFT_NUM];
extern uint16_t fft_sample_result[FFT_SAMPLE_NUM];

void microphone_init ();
// void ProcessFFT ();
// void FFTResultFilter ();


#endif