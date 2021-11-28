#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "main.h"
#include "adc.h"
#include "tim.h"
#include "arm_math.h"
//#include "cmsis_os.h"

#define FFT_SAMPLE_NUM    16

#define RAW_SAMPLE_NUM    64
#define FFT_NUM           RAW_SAMPLE_NUM/2

extern uint16_t adc_raw_result[RAW_SAMPLE_NUM];
extern float fft_magnitude[FFT_NUM];
extern uint16_t fft_sample_result[FFT_SAMPLE_NUM];
extern uint16_t fft_energy;

void microphone_init ();
void microphone_deinit ();
void process_fft ();
void fft_magnitude_filter ();


#endif