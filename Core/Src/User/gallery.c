#include "gallery.h"

void show_bmp(char *filename)
{
    FIL fp;
    FRESULT ret;
    uint8_t SD_Readbuf[240 * 3] = {0};
    UINT wsbyte = 0;

    char *fname;
    fname = strtok(filename, '\0');

    ret = f_open(&fp, fname, FA_READ);
    if (FR_OK != ret)
    {
        HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
        LCD_DrawString_2040_Rotate(100, 0, "File Not Found!");
    }
    f_lseek(&fp, 54);

    LCD_OpenWindow(0, 0, 240, 320);
    LCD_Write_Cmd(CMD_set_pixel);
    for (uint16_t i = 0; i < 320; i++)
    {
        ret = f_read(&fp, SD_Readbuf, 240 * 3, &wsbyte);
        if (FR_OK != ret)
        {
            HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
            LCD_DrawString_2040_Rotate(100, 0, "Cannot Read File!");
        }

        for (uint16_t x = 0; x < 240 * 3; x += 3)
        {
            uint16_t color =
                (SD_Readbuf[x + 2] * 0x1f / 0xff & 0x1f) << 11 | (SD_Readbuf[x + 1] * 0x3f / 0xff & 0x3f) << 5 | (SD_Readbuf[x + 0] * 0x1f / 0xff & 0x1f);
            LCD_Write_Data(color);
        }
    }
}

void gallery_init()
{
    FATFS myFATFS;
    // FIL myFILE;
    // UINT numberofbytes;
    // char myPath[] = "TEST_LCD.TXT\0";
    // char myData[] = "Hello World\0";
    FRESULT res; //operation result

    res = f_mount(&myFATFS, SDPath, 1);
    if (res == FR_OK)
    {
        // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
        //    f_open(&myFILE, myPath, FA_WRITE | FA_CREATE_ALWAYS);
        //    f_write(&myFILE, myData, sizeof(myData), &numberofbytes);
        //    f_close(&myFILE);
        //    HAL_Delay(1000);
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
        LCD_DrawString_2040_Rotate(100, 0, "No SD Card Found!");
    }
}

void gallery_slideshow()
{
    static uint32_t start_tick = 0;

    static uint8_t index = 0;

    if (HAL_GetTick() - start_tick > 1500)
    {
        char filename[] = "x.bmp";
        filename[0] = index + '0';
        show_bmp(filename);
        index++;
        start_tick = HAL_GetTick();
    }
}