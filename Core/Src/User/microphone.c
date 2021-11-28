#include "microphone.h"

uint16_t adc_raw_result[RAW_SAMPLE_NUM];

float fft_input[RAW_SAMPLE_NUM];
float fft_output[RAW_SAMPLE_NUM];
float fft_magnitude[FFT_NUM];

uint16_t fft_sample_result[FFT_SAMPLE_NUM];
uint16_t fft_energy;

arm_rfft_fast_instance_f32 s;

void microphone_init ()
{
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_raw_result, RAW_SAMPLE_NUM);

    HAL_TIM_Base_Start(&htim8);
    
    arm_rfft_fast_init_f32(&s, RAW_SAMPLE_NUM);
}

void microphone_deinit ()
{
    HAL_ADC_Stop_DMA(&hadc1);

    HAL_TIM_Base_Stop(&htim8);
}

void process_fft ()
{
    for (uint16_t i = 0; i < RAW_SAMPLE_NUM; i++)
        fft_input[i] = adc_raw_result[i];
    arm_rfft_fast_f32(&s, fft_input, fft_output, 0);

  /* Process the data through the Complex Magnitude Module for
  calculating the magnitude at each bin */
    arm_cmplx_mag_f32(fft_output, fft_magnitude, FFT_NUM);

  /* Calculates maxValue and returns corresponding BIN value */
//   arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);

    fft_magnitude_filter();
}

void fft_magnitude_filter ()
{    
    #if (FFT_NUM == FFT_SAMPLE_NUM)
        fft_magnitude[0] -= 49600;
    #else
    fft_sample_result[0] = 0;
    for (uint8_t j = 1; j < FFT_NUM/FFT_SAMPLE_NUM; j++)
    {
        fft_sample_result[0] += fft_magnitude[j];
    }
    fft_sample_result[0] /= (FFT_NUM/FFT_SAMPLE_NUM - 1);
    #endif

    for (uint8_t i = 1; i < FFT_SAMPLE_NUM; i++)
    {
        fft_sample_result[i] = 0;
        for (uint8_t j = 0; j < FFT_NUM/FFT_SAMPLE_NUM; j++)
        {
            fft_sample_result[i] += fft_magnitude[j+i*(FFT_NUM/FFT_SAMPLE_NUM)];
        }
        fft_sample_result[i] /= (FFT_NUM/FFT_SAMPLE_NUM);
    }
}

void calc_fft_energy ()
{
    uint32_t fft_average = 0;
    for (uint16_t i = 0; i < FFT_SAMPLE_NUM; i++)
        fft_average += fft_sample_result[i];
    fft_energy = fft_average / FFT_SAMPLE_NUM;
}