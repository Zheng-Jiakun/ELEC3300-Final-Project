#include "game.h"
#include "string.h"

game_state_t bird_state = GAME_INIT, snake_state = GAME_INIT;

void game_snake(){
	static uint16_t Snakei = 0; 
    static uint16_t Snakey = 0; 
    static uint8_t movestate = 0;
	static uint16_t SnakeSpots[2][30]; 
    static uint16_t SnakeLength = 3;
	//time_t t;
	srand(HAL_GetTick()+ temperature + humidity);
	static uint16_t Fruitx;
	static uint16_t Fruity;
	char buffer[3];
	//int value = 0;

     switch (snake_state)
    {
        case GAME_INIT:
            Snakei = 40; Snakey = 40;  movestate = 0;
            SnakeLength = 1;
            //time_t t;
            srand(HAL_GetTick());
            Fruitx = (rand() % 240);
            Fruity = (rand() % 320);
            char buffer[3];
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
            if(SnakeLength == 1){
                if(Fruitx%8>4)Fruitx+=(8-Fruitx%8);
                else Fruitx-=Fruitx%8;
                if(Fruity%8>4)Fruity+=(8-Fruity%8);
                else Fruity-=Fruity%8;
                LCD_DrawSquare(Fruitx, Fruity, 5, 0x00FF);
                LCD_DrawString(50, 50, "Snake was toot srhto");
                SnakeLength++; 
            }
            
            //LCD_DrawSquare(Fruitx, Fruity, 5, 0x00FF);
			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)){
				HAL_Delay(100);
				movestate++; 
				if(movestate > 3) movestate = 0;
			}
			switch(movestate){
				case 0:
					Snakei+=8;
					break;
				case 1:
					Snakey+=8;
					break;
				case 2:
					Snakei-=8;
					break;
				case 3:
					Snakey-=8;
					break;
			}
			if(Snakey > 318) {Snakey = 8;} else if(Snakey < 2) {Snakey = 312;}
			if(Snakei > 238) {Snakei = 8;} else if(Snakei < 2) {Snakei = 232;}
			LCD_DrawSquare(Snakei, Snakey, 5, 0x00FF);
			if(Fruitx == Snakei && Fruity == Snakey){
				SnakeLength++;
				Fruitx = rand() % 240;
				Fruity = rand() % 320;
				if(Fruitx%8>4)Fruitx+=(8-Fruitx%8);
				else Fruitx-=Fruitx%8;
				if(Fruity%8>4)Fruity+=(8-Fruity%8);
				else Fruity-=Fruity%8;
				LCD_DrawSquare(Fruitx, Fruity, 5, 0x00FF);
			}
			//LCD_DrawString(240, 50, "Snake of deez nuts");
			//LCD_DrawString(0, 300, "Snake test");
			//HAL_Delay(50);

            sprintf(buffer, "%d", Fruitx);
            LCD_DrawString(150, 50, buffer);
            sprintf(buffer, "%d", SnakeSpots[0][0]);
            LCD_DrawString(110, 50, buffer);
			for(int t = SnakeLength; t >= 0; t--){
				if(SnakeSpots[0][t]==Snakei&&SnakeSpots[1][t]==Snakey){SnakeLength = 0;snake_state = GAME_END;break;} //Lose Condition, do something with this.
				if(t == SnakeLength){LCD_Clear(SnakeSpots[0][t], SnakeSpots[1][t], 5, 5, 0xFFFF);}
				if(t == 0){SnakeSpots[0][0]=Snakei; SnakeSpots[1][0]=Snakey;}
				else{SnakeSpots[0][t]=SnakeSpots[0][t-1]; SnakeSpots[1][t]=SnakeSpots[1][t-1];}
			}
        break;

        case GAME_END:
            LCD_DrawString(240, 50, "Gamer");
            if (HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == GPIO_PIN_SET)
            {
                snake_state = GAME_INIT;
            }
        break;


    }
		
}

void game_bird()//game_bird_init/game_bird_loop
{
    static uint16_t Bird_y;
    static uint8_t Gravity;
	srand(HAL_GetTick() + temperature + humidity);
	static uint16_t PolePositions[4][2];
    static uint16_t TopPositions[4];
    char buffer[3];
    static uint16_t score;

    switch (bird_state)
    {//bugs: the poles won't go to a new position
        case GAME_INIT:
            LCD_Clear(0, 0, 240, 320, 0xffff);
            Bird_y = 100;
            Gravity = 1;
            uint16_t tempPolePositions[4][2] = {{200, 80}, {280, 40+(rand()%100)}, {360, 140}, {440, 40+(rand()%100)}};
            memcpy(PolePositions, tempPolePositions, sizeof(PolePositions));
            uint16_t tempTopPositions[4] = {140-PolePositions[0][1], 140-PolePositions[1][1], 180-PolePositions[2][1], 140-PolePositions[3][1]};
            memcpy(TopPositions, tempTopPositions, sizeof(TopPositions));
            score = 0;
            bird_state = GAME_PLAY;
        break;
        case GAME_PLAY:
            LCD_Clear(Bird_y, 160, 10, 10, 0xFFFF);
            Bird_y-=Gravity;
            Gravity +=4;
            if(Bird_y<1){Bird_y=1;Gravity = 0;} else if (Bird_y > 240){Bird_y = 240, Gravity = 0;}
            //LCD_DrawSquare(118, y, 10, 0x00FF);
            LCD_DrawSquare(Bird_y, 160, 10, 0x00FF);
            //Pipes with regular interval in between, but rand +- height, then draw.
            LCD_DrawLine(30, 0, 30, 320, GREEN);
            sprintf(buffer, "%d", score);
            LCD_DrawString_2448_Rotate(175, 57, buffer);
            if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)){
                //Jump Animation
                LCD_Clear(Bird_y, 160, 10, 10, 0xFFFF);
                Bird_y+=30;
                Gravity = 0;
                //LCD_DrawLine(0, y, 240, y, 0x0000);
            }
            //LCD_DrawLine(240, 
            for(int i = 0; i < 4 ; i++){
                if(PolePositions[i][0] <=8) {
                    LCD_Clear(0, 0, 240, 30, 0xffff);
                    PolePositions[i][0] = 320;
                    PolePositions[i][1] = 40+(rand()%100);
                    TopPositions[i] = 140-PolePositions[i][1];
                } //Draw a new pole
                
                //sprintf(buffer, "%d", PolePositions[0][0]);
               // LCD_DrawString_2448_Rotate(10, 10, buffer);
                
               if(((Bird_y>(240-TopPositions[i])||Bird_y<PolePositions[i][1])&&(PolePositions[i][0] > 160 && PolePositions [i][0]+10<172))
                    ||((Bird_y>(240-TopPositions[i])||Bird_y<PolePositions[i][1])&&(PolePositions[i][0]+12>160 && PolePositions[i][0]<172))
                    || Bird_y < 30)
                {
                    LCD_DrawSquare(Bird_y, 160, 10, 0x00FF);
                    bird_state = GAME_END;
                    //Snake();
                    //y -= 100;
                }
                if(PolePositions[i][0] < 159 && PolePositions[i][0]>155){
                    score++;
                }
                else if(PolePositions[i][0] > 0){	
                    //LCD_DrawLine(PolePositions[i][0], (360-PolePositions[i][1]), 360, (360-PolePositions[i][1]), 0x0000);
                    //LCD_Clear(PolePositions[i][0]+12, (320-PolePositions[i][1]), 5, (PolePositions[i][1]), 0xffff);
                    //LCD_DrawLine(PolePositions[i][0], (320-PolePositions[i][1]), PolePositions[i][0], 320, 0x0000);
                    LCD_Clear(0, PolePositions[i][0]+11, PolePositions[i][1]+1, 5, 0xffff);
                    LCD_DrawLine(0, PolePositions[i][0], PolePositions[i][1], PolePositions[i][0], 0x0000);
                    //LCD_Clear(PolePositions[i][0]+12, 0, 5, TopPositions[i]+1, 0xffff);
                    //LCD_DrawLine(PolePositions[i][0], 0, PolePositions[i][0], TopPositions[i], 0x0000);
                    LCD_Clear(240-TopPositions[i], PolePositions[i][0]+12, 240-TopPositions[i], 5, 0xffff);
                    LCD_DrawLine(240-TopPositions[i], PolePositions[i][0], 240, PolePositions[i][0], 0x0000);

                }
                PolePositions[i][0]-=3;
            }
        break;

        case GAME_END:
            //LCD_Clear(0, 0, 240, 320, 0xffff);
            LCD_DrawString_2448_Rotate(108, 56, "GAME OVER");
            //LCD_DrawString(110, 60, "Game Over");
            if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13))
            {
                bird_state = GAME_INIT;
            }
        break;
	}
}