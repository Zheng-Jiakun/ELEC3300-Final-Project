#include "game.h"
#include "string.h"

game_state_t bird_state = GAME_INIT, snake_state = GAME_INIT;

void game_snake()
{
    static uint16_t Snakei = 0;
    static uint16_t Snakey = 0;
    static uint8_t movestate = 0;
    static uint16_t SnakeSpots[2][30];
    static uint16_t SnakeLength = 3;
    //time_t t;
    srand(HAL_GetTick() + temperature + humidity);
    static uint16_t Fruitx;
    static uint16_t Fruity;
    char buffer[3];
    //int value = 0;

    switch (snake_state)
    {
    case GAME_INIT:
        LCD_Clear(0, 0, 240, 320, 0xffff);
        Snakei = 40;
        Snakey = 40;
        movestate = 0;
        SnakeLength = 3;
        //time_t t;
        //srand(HAL_GetTick());
        Fruitx = 8 + (rand() % 232);
        Fruity = 8 + (rand() % 312);
        if (Fruitx % 8 > 4)
            Fruitx += (8 - Fruitx % 8);
        else
            Fruitx -= Fruitx % 8;
        if (Fruity % 8 > 4)
            Fruity += (8 - Fruity % 8);
        else
            Fruity -= Fruity % 8;
        LCD_DrawSquare(Fruitx, Fruity, 5, 0x00FF);
        snake_state = GAME_PLAY;
        break;

    case GAME_PLAY:

        /*if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)){
				LCD_Clear(0, 0, 240, 320, 0xFFFF);
				Fruitx = rand() % 240;
				Fruity = rand() % 320;
				sprintf(buffer, "%d", Fruitx);
				LCD_DrawString(110, 50, buffer);
			}*/
        /*if(SnakeLength == 1){
                if(Fruitx%8>4)Fruitx+=(8-Fruitx%8);
                else Fruitx-=Fruitx%8;
                if(Fruity%8>4)Fruity+=(8-Fruity%8);
                else Fruity-=Fruity%8;
                LCD_DrawSquare(Fruitx, Fruity, 5, 0x00FF);
                LCD_DrawString(50, 50, "Snake was toot srhto");
                SnakeLength++; 
            }*/

        //LCD_DrawSquare(Fruitx, Fruity, 5, 0x00FF);
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
        {
            HAL_Delay(100);
            movestate++;
            if (movestate > 3)
                movestate = 0;
        }

        // sprintf(buffer, "%d", accAngle.angleX);
        //LCD_DrawString(150, 150, buffer);
        if (accAngle.angleY < -ANGLE_THRESHOLD && movestate != 2)
        {
            movestate = 0;
        }
        else if (accAngle.angleX < -ANGLE_THRESHOLD && movestate != 3)
        {
            movestate = 1;
        }
        else if (accAngle.angleY > ANGLE_THRESHOLD && movestate != 0)
        {
            movestate = 2;
        }
        else if (accAngle.angleX > ANGLE_THRESHOLD && movestate != 1)
        {
            movestate = 3;
        }
        switch (movestate)
        {
        case 0:
            Snakei += 8;
            break;
        case 1:
            Snakey += 8;
            break;
        case 2:
            Snakei -= 8;
            break;
        case 3:
            Snakey -= 8;
            break;
        }
        //if(Snakey > 318) {Snakey = 8;} else if(Snakey < 2) {Snakey = 312;}
        //if(Snakei > 238) {Snakei = 8;} else if(Snakei < 2) {Snakei = 232;}
        if (Snakey > 320)
        {
            Snakey = 0;
        }
        else if (Snakey < 2)
        {
            Snakey = 320;
        }
        if (Snakei > 240)
        {
            Snakei = 0;
        }
        else if (Snakei < 2)
        {
            Snakei = 240;
        }
        LCD_DrawSquare(Snakei, Snakey, 5, 0x00FF);
        if (Fruitx == Snakei && Fruity == Snakey)
        {
            SnakeLength++;
            Fruitx = 8 + rand() % 232;
            Fruity = 8 + rand() % 312;
            if (Fruitx % 8 > 4)
                Fruitx += (8 - Fruitx % 8);
            else
                Fruitx -= Fruitx % 8;
            if (Fruity % 8 > 4)
                Fruity += (8 - Fruity % 8);
            else
                Fruity -= Fruity % 8;
            LCD_DrawSquare(Fruitx, Fruity, 5, 0x00FF);
        }
        //LCD_DrawString(240, 50, "Snake of deez nuts");
        //LCD_DrawString(0, 300, "Snake test");
        //HAL_Delay(50);
        //LCD_DrawSquare(155, 50, 5, 0x0f0f);
        // if (Fruitx > 109 && Fruitx < 153 && Fruity > 50 && Fruity < 69)
        // {
        //     sprintf(buffer, "%d", SnakeLength - 3);
        //     LCD_DrawString_2448_Rotate(109, 267, buffer);
        // }
        // else
        // {
        //     sprintf(buffer, "%d", SnakeLength - 3);
        //     LCD_DrawString_2448_Rotate(109, 50, buffer);
        // }
        for (int t = SnakeLength; t >= 0; t--)
        {
            if (SnakeSpots[0][t] == Snakei && SnakeSpots[1][t] == Snakey)
            {
                snake_state = GAME_END;
                LCD_Clear(0, 0, 240, 320, WHITE);
                break;
            } //Lose Condition, do something with this.
            if (t == SnakeLength)
            {
                LCD_Clear(SnakeSpots[0][t], SnakeSpots[1][t], 5, 5, 0xFFFF);
            }
            if (t == 0)
            {
                SnakeSpots[0][0] = Snakei;
                SnakeSpots[1][0] = Snakey;
            }
            else
            {
                SnakeSpots[0][t] = SnakeSpots[0][t - 1];
                SnakeSpots[1][t] = SnakeSpots[1][t - 1];
            }
        }
        if (SnakeLength > 3)
        {
            led_set_pixel(SnakeLength - 4);
            WS2812_update();
        }
        HAL_Delay(80 - SnakeLength);
        if (ucXPT2046_TouchFlag)
        {
            snake_state = GAME_INIT;
            system_mode = GAME;
        }
        break;

        static uint8_t print_info_flag = 0;
    case GAME_END:
        if (print_info_flag == 0)
        {
            LCD_DrawString_2448_Rotate(180, 56, "GAME OVER");
            LCD_DrawString_2448_Rotate(100, 90, "SCORE");
            sprintf(buffer, "%d", SnakeLength - 3);
            LCD_DrawString_2448_Rotate(50, 140, buffer);
            uint8_t highest;
            eeprom_read_byte(0, &highest);
            if (SnakeLength - 3 > highest)
            {
                eeprom_write_byte(0, SnakeLength - 3);
                LCD_DrawString_2040_Rotate(0, 40, "New history!");
            }
            print_info_flag = 1;
        }
        if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_SET || ucXPT2046_TouchFlag)
        {
            print_info_flag = 0;
            snake_state = GAME_INIT;
        }
        break;
    }
}

void game_bird() //game_bird_init/game_bird_loop
{
    static uint16_t Bird_y;
    static uint8_t Gravity;
    srand(HAL_GetTick() + temperature + humidity);
    static uint16_t PolePositions[4][2];
    static uint16_t TopPositions[4];
    char buffer[3];
    static uint16_t score;

    calc_fft_energy();

    switch (bird_state)
    { //bugs: the poles won't go to a new position
    case GAME_INIT:
        LCD_Clear(0, 0, 240, 320, 0xffff);
        clear_all_led();
        Bird_y = 100;
        Gravity = 1;
        uint16_t tempPolePositions[4][2] = {{200, 80}, {280, 40 + (rand() % 100)}, {360, 140}, {440, 40 + (rand() % 100)}};
        memcpy(PolePositions, tempPolePositions, sizeof(PolePositions));
        uint16_t tempTopPositions[4] = {140 - PolePositions[0][1], 140 - PolePositions[1][1], 180 - PolePositions[2][1], 140 - PolePositions[3][1]};
        memcpy(TopPositions, tempTopPositions, sizeof(TopPositions));
        score = 0;
        bird_state = GAME_PLAY;
        lcd_draw_grass(0, 0);
        break;

    case GAME_PLAY:
        LCD_Clear(Bird_y, 160, 15, 15, 0xFFFF);
        Bird_y -= Gravity;
        Gravity += 4;
        if (Bird_y < 1)
        {
            Bird_y = 1;
            Gravity = 0;
        }
        else if (Bird_y > 240)
        {
            Bird_y = 240, Gravity = 0;
        }
        //LCD_DrawSquare(118, y, 10, 0x00FF);
        // LCD_DrawSquare(Bird_y, 160, 10, 0x00FF);
        //Pipes with regular interval in between, but rand +- height, then draw.
        // LCD_Clear(30, 0, 1, 320, GREEN);
        // sprintf(buffer, "%d", score);
        // LCD_DrawString_2448_Rotate(175, 57, buffer);
        led_set_pixel(score);
        WS2812_update();
        if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_SET)
        {
            //Jump Animation
            // LCD_Clear(Bird_y, 160, 15, 15, 0xFFFF);
            Bird_y += 30;
            Gravity = 0;
            //LCD_DrawLine(0, y, 240, y, 0x0000);
        }
        if (fft_energy > MIC_THRESHOLD)
        {
            // LCD_Clear(Bird_y, 160, 15, 15, 0xFFFF);
            Bird_y += 10;
            Gravity = 0;
        }
        lcd_draw_flappy_bird(Bird_y, 160);
        //LCD_DrawLine(240,
        for (int i = 0; i < 4; i++)
        {
            if (PolePositions[i][0] <= 8)
            {
                LCD_Clear(30, 0, 240, 30, 0xffff);
                PolePositions[i][0] = 320;
                PolePositions[i][1] = 40 + (rand() % 100);
                TopPositions[i] = 140 - PolePositions[i][1];
            } //Draw a new pole

            if (PolePositions[i][0] < 159 && PolePositions[i][0] > 155)
            {
                score++;
            }
            else if (PolePositions[i][0] > 0)
            {
                //LCD_DrawLine(PolePositions[i][0], (360-PolePositions[i][1]), 360, (360-PolePositions[i][1]), 0x0000);
                //LCD_Clear(PolePositions[i][0]+12, (320-PolePositions[i][1]), 5, (PolePositions[i][1]), 0xffff);
                //LCD_DrawLine(PolePositions[i][0], (320-PolePositions[i][1]), PolePositions[i][0], 320, 0x0000);
                LCD_Clear(30, PolePositions[i][0] + 11, PolePositions[i][1] + 1, 7, 0xffff);
                LCD_Clear(30, PolePositions[i][0], PolePositions[i][1]-30, 3, GREEN);
                //LCD_Clear(PolePositions[i][0]+12, 0, 5, TopPositions[i]+1, 0xffff);
                //LCD_DrawLine(PolePositions[i][0], 0, PolePositions[i][0], TopPositions[i], 0x0000);
                LCD_Clear(240 - TopPositions[i], PolePositions[i][0] + 12, 240 - TopPositions[i], 7, 0xffff);
                LCD_Clear(240 - TopPositions[i], PolePositions[i][0], TopPositions[i], 3, GREEN);
            }

            if (((Bird_y > (240 - TopPositions[i]) || Bird_y < PolePositions[i][1]) && (PolePositions[i][0] > 160 && PolePositions[i][0] + 10 < 172)) || ((Bird_y > (240 - TopPositions[i]) || Bird_y < PolePositions[i][1]) && (PolePositions[i][0] + 12 > 160 && PolePositions[i][0] < 172)) || Bird_y < 30)
            {
                // LCD_DrawSquare(Bird_y, 160, 15, 0x00FF);
                bird_state = GAME_END;
                LCD_Clear(0, 0, 240, 320, WHITE);
                i = 255;
                //Snake();
                //y -= 100;
            }
            PolePositions[i][0] -= 3;
        }
        // HAL_Delay(50);
        break;

        static uint8_t print_info_flag = 0;
    case GAME_END:
        //LCD_Clear(0, 0, 240, 320, 0xffff);
        //LCD_DrawString(110, 60, "Game Over");
        if (print_info_flag == 0)
        {
            LCD_DrawString_2448_Rotate(180, 56, "GAME OVER");
            LCD_DrawString_2448_Rotate(100, 90, "SCORE");
            sprintf(buffer, "%d", score);
            LCD_DrawString_2448_Rotate(50, 140, buffer);
            uint8_t highest;
            eeprom_read_byte(1, &highest);
            if (score > highest)
            {
                eeprom_write_byte(1, score);
                LCD_DrawString_2040_Rotate(0, 40, "New history!");
            }
            print_info_flag = 1;
        }
        if (HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin) == GPIO_PIN_SET || ucXPT2046_TouchFlag)
        {
            print_info_flag = 0;
            bird_state = GAME_INIT;
        }
        break;
    }
}