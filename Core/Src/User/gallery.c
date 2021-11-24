#include "gallery.h"

void show_bmp(char *filename)
{
    FATFS myFATFS;
    FIL fp;
    FRESULT ret;
    uint8_t SD_Readbuf[240 * 2] = {0};
    UINT wsbyte = 0;

    char *fname;
    fname = strtok(filename, '\0');

    ret = f_mount(&myFATFS, SDPath, 1);
    if (ret != FR_OK)
    {
        LCD_DrawString_2040_Rotate(100, 0, "No SD Card");
    }
    else
    {
        ret = f_open(&fp, fname, FA_READ);
        if (FR_OK != ret)
        {
            LCD_DrawString_2040_Rotate(100, 0, "File Not Found");
        }
        f_lseek(&fp, 70);

        LCD_OpenWindow(0, 0, 240, 320);
        LCD_Write_Cmd(CMD_set_pixel);
        for (uint16_t i = 0; i < 320; i++)
        {
            ret = f_read(&fp, SD_Readbuf, 240 * 2, &wsbyte);
            if (FR_OK != ret)
            {
                LCD_DrawString_2040_Rotate(100, 0, "Can't Read File");
            }

            for (uint16_t x = 0; x < 240 * 2; x += 2)
            {
                uint16_t color = SD_Readbuf[x] | (SD_Readbuf[x + 1] << 8);
                LCD_Write_Data(color);
            }
        }
    }
}

void gallery_slideshow()
{
    static uint32_t start_tick = 0;

    static uint8_t index = 0;

    if (HAL_GetTick() - start_tick > 1000)
    {
        char filename[] = "x.bmp";
        filename[0] = index + '0';
        show_bmp(filename);
        index++;
        if (index > 5)
            index = 0;
        start_tick = HAL_GetTick();
    }
}