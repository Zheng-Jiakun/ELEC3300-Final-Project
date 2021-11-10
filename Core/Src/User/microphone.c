#include "microphone.h"

uint16_t adc_raw_result[RAW_SAMPLE_NUM];

float fft_input[RAW_SAMPLE_NUM];
float fft_output[RAW_SAMPLE_NUM];
float fft_magnitude[FFT_NUM];

uint16_t fft_sample_result[FFT_SAMPLE_NUM];

// arm_rfft_fast_instance_f32 s;

void microphone_init ()
{
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_raw_result, RAW_SAMPLE_NUM);

    // HAL_TIM_Base_Start(&htim6);
    
    // arm_rfft_fast_init_f32(&s, RAW_SAMPLE_NUM);
}

// void ProcessFFT ()
// {
//     for (uint16_t i = 0; i < RAW_SAMPLE_NUM; i++)
//         fft_input[i] = RawSampleResult[i];
//     arm_rfft_fast_f32(&s, fft_input, fft_output, 0);

//   /* Process the data through the Complex Magnitude Module for
//   calculating the magnitude at each bin */
//     arm_cmplx_mag_f32(fft_output, fft_magnitude, FFT_NUM);

//   /* Calculates maxValue and returns corresponding BIN value */
// //   arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);

//     fft_magnitudeFilter();
// }

// void fft_magnitudeFilter ()
// {
//     for (uint8_t i = 0; i < FFT_SAMPLE_NUM; i++)
//     {
//         fft_sample_result[i] = 0;
//         for (uint8_t j = 0; j < FFT_NUM/FFT_SAMPLE_NUM; j++)
//         {
//             fft_sample_result[i] += fft_magnitude[j+i*(FFT_NUM/FFT_SAMPLE_NUM)];
//         }
//         fft_sample_result[i] /= (FFT_NUM/FFT_SAMPLE_NUM);
//     }
// }