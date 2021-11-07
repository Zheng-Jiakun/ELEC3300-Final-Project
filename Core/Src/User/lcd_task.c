#include "lcd_task.h"

const uint8_t image[][3] = {
    #include "image.h"
};

void lcd_task_setup ()
{
	LCD_INIT();
	LCD_DrawString(120, 160, "WELCOME");
    for (uint16_t i = 0; i < 128; i++)
    {
        for (uint16_t j = 0; j < 128; j++)
        {
            uint16_t color = (image[j+i*128][0]*0x1f/0xff & 0x1f) << 11 | (image[j+i*128][1]*0x3f/0xff & 0x3f) << 5 | (image[j+i*128][2]*0x1f/0xff & 0x1f);
            LCD_DrawDot(i, j, color);
        }
    }
}

void lcd_task_loop ()
{
    if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_SET)
    {
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
        while (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_SET);
    } 
}