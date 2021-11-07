#include "user_main.h"

void user_setup ()
{
	LCD_INIT();
	LCD_DrawString(0, 0, "Task 1:");
	LCD_DrawString(80, 16, " X     Y      Angle");
	LCD_DrawString(16, 32, "Value: ");
	LCD_DrawString(16, 48, "Value: ");
}

void user_loop ()
{
    if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_SET)
    {
        HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
        while (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_SET);
    } 
}