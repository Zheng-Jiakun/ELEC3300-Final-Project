#include "lcd_task.h"

void lcd_task_setup ()
{
	LCD_INIT();
	LCD_DrawString(120, 160, "WELCOME");
}

void lcd_task_loop ()
{
    if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_SET)
    {
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
        while (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_SET);
    } 
}