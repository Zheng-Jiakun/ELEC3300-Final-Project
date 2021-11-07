#include <WS2812B.h>
#include <dma.h>
#include <tim.h>

#define FRAME_SIZE (30 + 24 * LED_NUM + 80)

color_t LEDColor[LED_NUM] = {0};

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

void WS2812_Init()
{
    // HAL_TIM_PWM_Start_DMA(&htim3, TIM_CHANNEL_1, (uint32_t *)DMADataBuf, FRAME_SIZE);
    htim3.hdma[TIM_DMA_ID_UPDATE]->XferCpltCallback = TIM_DMAPeriodElapsedCplt;

    /* Set the DMA error callback */
    htim3.hdma[TIM_DMA_ID_UPDATE]->XferErrorCallback = TIM_DMAError ;

    /* Enable the DMA channel */
    HAL_DMA_Start_IT(htim3.hdma[TIM_DMA_ID_UPDATE], (uint32_t)DMADataBuf, (uint32_t)&htim3.Instance->CCR1, FRAME_SIZE);

    /* Enable the TIM Capture/Compare 1 DMA request */
    __HAL_TIM_ENABLE_DMA(&htim3, TIM_DMA_UPDATE);

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

#define ONE_PULSE  8
#define ZERO_PULSE 4

void WS2812_Update()
{
    // memset(DMADataBuf, 0, sizeof(DMADataBuf));
    for (uint8_t j = 0; j < LED_NUM; j++)
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            if (LEDColor[j].g & (0x80 >> i))
                DMADataBuf[30+j*24+i] = ONE_PULSE;
            else
                DMADataBuf[30+j*24+i] = ZERO_PULSE;
        }
        for (uint8_t i = 0; i < 8; i++)
        {
            if (LEDColor[j].r & (0x80 >> i))
                DMADataBuf[30+j*24+i+8] = ONE_PULSE;
            else
                DMADataBuf[30+j*24+i+8] = ZERO_PULSE;
        }
        for (uint8_t i = 0; i < 8; i++)
        {
            if (LEDColor[j].b & (0x80 >> i))
                DMADataBuf[30+j*24+i+16] = ONE_PULSE;
            else
                DMADataBuf[30+j*24+i+16] = ZERO_PULSE;
        }
    }
}