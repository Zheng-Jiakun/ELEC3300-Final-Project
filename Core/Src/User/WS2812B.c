#include "WS2812B.h"

#define FRAME_SIZE (30 + 24 * LED_NUM + 80)

color_t led_color[LED_NUM] = {0};
uint8_t led_brightness = LED_MAX_BRIGHTNESS;

uint16_t DMADataBuf[FRAME_SIZE];

static void TIM_DMAPeriodElapsedCplt(DMA_HandleTypeDef *hdma)
{
  TIM_HandleTypeDef *htim = (TIM_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (htim->hdma[TIM_DMA_ID_UPDATE]->Init.Mode == DMA_NORMAL)
  {
    htim->State = HAL_TIM_STATE_READY;
  }

#if (USE_HAL_TIM_REGISTER_CALLBACKS == 1)
  htim->PeriodElapsedCallback(htim);
#else
  HAL_TIM_PeriodElapsedCallback(htim);
#endif /* USE_HAL_TIM_REGISTER_CALLBACKS */
  htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
}

void WS2812_init()
{
  // HAL_TIM_PWM_Start_DMA(&htim5, TIM_CHANNEL_4, (uint32_t *)DMADataBuf, FRAME_SIZE);
  htim5.hdma[TIM_DMA_ID_UPDATE]->XferCpltCallback = TIM_DMAPeriodElapsedCplt;

  /* Set the DMA error callback */
  htim5.hdma[TIM_DMA_ID_UPDATE]->XferErrorCallback = TIM_DMAError;

  /* Enable the DMA channel */
  HAL_DMA_Start_IT(htim5.hdma[TIM_DMA_ID_UPDATE], (uint32_t)DMADataBuf, (uint32_t)&htim5.Instance->CCR4, FRAME_SIZE);

  /* Enable the TIM Capture/Compare 1 DMA request */
  __HAL_TIM_ENABLE_DMA(&htim5, TIM_DMA_UPDATE);

  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
}

#define ONE_PULSE 8
#define ZERO_PULSE 4

void WS2812_update()
{
  // memset(DMADataBuf, 0, sizeof(DMADataBuf));
  for (uint8_t j = 0; j < LED_NUM; j++)
  {
    for (uint8_t i = 0; i < 8; i++)
    {
      if ((led_color[j].g*led_brightness/LED_MAX_BRIGHTNESS) & (0x80 >> i))
        DMADataBuf[30 + j * 24 + i] = ONE_PULSE;
      else
        DMADataBuf[30 + j * 24 + i] = ZERO_PULSE;
    }
    for (uint8_t i = 0; i < 8; i++)
    {
      if ((led_color[j].r*led_brightness/LED_MAX_BRIGHTNESS) & (0x80 >> i))
        DMADataBuf[30 + j * 24 + i + 8] = ONE_PULSE;
      else
        DMADataBuf[30 + j * 24 + i + 8] = ZERO_PULSE;
    }
    for (uint8_t i = 0; i < 8; i++)
    {
      if ((led_color[j].b*led_brightness/LED_MAX_BRIGHTNESS) & (0x80 >> i))
        DMADataBuf[30 + j * 24 + i + 16] = ONE_PULSE;
      else
        DMADataBuf[30 + j * 24 + i + 16] = ZERO_PULSE;
    }
  }
}

void set_led_brightness(uint8_t b)
{
  if (b > 255)
    b = 255;
  led_brightness = b;
}

void clear_all_led ()
{
  memset(led_color, 0, sizeof(led_color));
}