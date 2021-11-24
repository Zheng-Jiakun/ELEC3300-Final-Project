#include "lcd.h"
#include "ascii.h"
#include "image.h"
#include "tim.h"

void LCD_REG_Config(void);
void LCD_FillColor(uint32_t ulAmout_Point, uint16_t usColor);
uint16_t LCD_Read_PixelData(void);

void Delay(__IO uint32_t nCount)
{
	for (; nCount != 0; nCount--)
		;
}

void LCD_set_brightness(uint16_t b)
{
	if (b > 999)
		b = 999;
	else if (b < 50)
		b = 50;
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, b);
}

void LCD_INIT(void)
{
	LCD_BackLed_Control(ENABLE);
	LCD_Rst();
	LCD_REG_Config();
	LCD_Clear(0, 0, 240, 320, BACKGROUND);

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
}

void LCD_Rst(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
	Delay(0xAFFf << 2);
	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
	Delay(0xAFFf << 2);
}

void LCD_BackLed_Control(FunctionalState enumState)
{
	if (enumState)
		HAL_GPIO_WritePin(LCD_BK_PORT, LCD_BK_PIN, GPIO_PIN_RESET);
	else
		HAL_GPIO_WritePin(LCD_BK_PORT, LCD_BK_PIN, GPIO_PIN_SET);
}

void LCD_Write_Cmd(uint16_t usCmd)
{
	*(__IO uint16_t *)(FSMC_Addr_LCD_CMD) = usCmd;
}

void LCD_Write_Data(uint16_t usData)
{
	*(__IO uint16_t *)(FSMC_Addr_LCD_DATA) = usData;
}

uint16_t LCD_Read_Data(void)
{
	return (*(__IO uint16_t *)(FSMC_Addr_LCD_DATA));
}

void LCD_REG_Config(void)
{
	/*  Power control B (CFh)  */
	DEBUG_DELAY();
	LCD_Write_Cmd(0xCF);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x81);
	LCD_Write_Data(0x30);

	/*  Power on sequence control (EDh) */
	DEBUG_DELAY();
	LCD_Write_Cmd(0xED);
	LCD_Write_Data(0x64);
	LCD_Write_Data(0x03);
	LCD_Write_Data(0x12);
	LCD_Write_Data(0x81);

	/*  Driver timing control A (E8h) */
	DEBUG_DELAY();
	LCD_Write_Cmd(0xE8);
	LCD_Write_Data(0x85);
	LCD_Write_Data(0x10);
	LCD_Write_Data(0x78);

	/*  Power control A (CBh) */
	DEBUG_DELAY();
	LCD_Write_Cmd(0xCB);
	LCD_Write_Data(0x39);
	LCD_Write_Data(0x2C);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x34);
	LCD_Write_Data(0x02);

	/* Pump ratio control (F7h) */
	DEBUG_DELAY();
	LCD_Write_Cmd(0xF7);
	LCD_Write_Data(0x20);

	/* Driver timing control B */
	DEBUG_DELAY();
	LCD_Write_Cmd(0xEA);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x00);

	/* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
	DEBUG_DELAY();
	LCD_Write_Cmd(0xB1);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x1B);

	/*  Display Function Control (B6h) */
	DEBUG_DELAY();
	LCD_Write_Cmd(0xB6);
	LCD_Write_Data(0x0A);
	LCD_Write_Data(0xA2);

	/* Power Control 1 (C0h) */
	DEBUG_DELAY();
	LCD_Write_Cmd(0xC0);
	LCD_Write_Data(0x35);

	/* Power Control 2 (C1h) */
	DEBUG_DELAY();
	LCD_Write_Cmd(0xC1);
	LCD_Write_Data(0x11);

	/* VCOM Control 1 (C5h) */
	LCD_Write_Cmd(0xC5);
	LCD_Write_Data(0x45);
	LCD_Write_Data(0x45);

	/*  VCOM Control 2 (C7h)  */
	LCD_Write_Cmd(0xC7);
	LCD_Write_Data(0xA2);

	/* Enable 3G (F2h) */
	LCD_Write_Cmd(0xF2);
	LCD_Write_Data(0x00);

	/* Gamma Set (26h) */
	LCD_Write_Cmd(0x26);
	LCD_Write_Data(0x01);
	DEBUG_DELAY();

	/* Positive Gamma Correction */
	LCD_Write_Cmd(0xE0); //Set Gamma
	LCD_Write_Data(0x0F);
	LCD_Write_Data(0x26);
	LCD_Write_Data(0x24);
	LCD_Write_Data(0x0B);
	LCD_Write_Data(0x0E);
	LCD_Write_Data(0x09);
	LCD_Write_Data(0x54);
	LCD_Write_Data(0xA8);
	LCD_Write_Data(0x46);
	LCD_Write_Data(0x0C);
	LCD_Write_Data(0x17);
	LCD_Write_Data(0x09);
	LCD_Write_Data(0x0F);
	LCD_Write_Data(0x07);
	LCD_Write_Data(0x00);

	/* Negative Gamma Correction (E1h) */
	LCD_Write_Cmd(0XE1); //Set Gamma
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x19);
	LCD_Write_Data(0x1B);
	LCD_Write_Data(0x04);
	LCD_Write_Data(0x10);
	LCD_Write_Data(0x07);
	LCD_Write_Data(0x2A);
	LCD_Write_Data(0x47);
	LCD_Write_Data(0x39);
	LCD_Write_Data(0x03);
	LCD_Write_Data(0x06);
	LCD_Write_Data(0x06);
	LCD_Write_Data(0x30);
	LCD_Write_Data(0x38);
	LCD_Write_Data(0x0F);

	/* memory access control set */
	DEBUG_DELAY();
	LCD_Write_Cmd(0x36);
	LCD_Write_Data(0xC8);
	DEBUG_DELAY();

	/* column address control set */
	LCD_Write_Cmd(CMD_Set_COLUMN);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0xEF);

	/* page address control set */
	DEBUG_DELAY();
	LCD_Write_Cmd(CMD_Set_PAGE);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x01);
	LCD_Write_Data(0x3F);

	/*  Pixel Format Set (3Ah)  */
	DEBUG_DELAY();
	LCD_Write_Cmd(0x3a);
	LCD_Write_Data(0x55);

	/* Sleep Out (11h)  */
	LCD_Write_Cmd(0x11);
	Delay(0xAFFf << 2);
	DEBUG_DELAY();

	/* Display ON (29h) */
	LCD_Write_Cmd(0x29);
}

void LCD_OpenWindow(uint16_t usCOLUMN, uint16_t usPAGE, uint16_t usWidth, uint16_t usHeight)
{
	LCD_Write_Cmd(CMD_Set_COLUMN);
	LCD_Write_Data(usCOLUMN >> 8);
	LCD_Write_Data(usCOLUMN & 0xff);
	LCD_Write_Data((usCOLUMN + usWidth - 1) >> 8);
	LCD_Write_Data((usCOLUMN + usWidth - 1) & 0xff);

	LCD_Write_Cmd(CMD_Set_PAGE);
	LCD_Write_Data(usPAGE >> 8);
	LCD_Write_Data(usPAGE & 0xff);
	LCD_Write_Data((usPAGE + usHeight - 1) >> 8);
	LCD_Write_Data((usPAGE + usHeight - 1) & 0xff);
}

void LCD_FillColor(uint32_t usPoint, uint16_t usColor)
{
	uint32_t i = 0;

	/* memory write */
	LCD_Write_Cmd(CMD_set_pixel);

	for (i = 0; i < usPoint; i++)
		LCD_Write_Data(usColor);
}

void LCD_Clear(uint16_t usCOLUMN, uint16_t usPAGE, uint16_t usWidth, uint16_t usHeight, uint16_t usColor)
{
	LCD_OpenWindow(usCOLUMN, usPAGE, usWidth, usHeight);
	LCD_FillColor(usWidth * usHeight, usColor);
}

uint16_t LCD_Read_PixelData(void)
{
	uint16_t usR = 0, usG = 0, usB = 0;

	LCD_Write_Cmd(0x2E);

	usR = LCD_Read_Data(); /*FIRST READ OUT DUMMY DATA*/

	usR = LCD_Read_Data(); /*READ OUT RED DATA  */
	usB = LCD_Read_Data(); /*READ OUT BLUE DATA*/
	usG = LCD_Read_Data(); /*READ OUT GREEN DATA*/

	return (((usR >> 11) << 11) | ((usG >> 10) << 5) | (usB >> 11));
}

uint16_t LCD_GetPointPixel(uint16_t usCOLUMN, uint16_t usPAGE)
{
	uint16_t usPixelData;

	LCD_OpenWindow(usCOLUMN, usPAGE, 1, 1);

	usPixelData = LCD_Read_PixelData();

	return usPixelData;
}

void LCD_DrawLine(uint16_t usC1, uint16_t usP1, uint16_t usC2, uint16_t usP2, uint16_t usColor)
{
	uint16_t us;
	uint16_t usC_Current, usP_Current;

	int32_t lError_C = 0, lError_P = 0, lDelta_C, lDelta_P, lDistance;
	int32_t lIncrease_C, lIncrease_P;

	lDelta_C = usC2 - usC1;
	lDelta_P = usP2 - usP1;

	usC_Current = usC1;
	usP_Current = usP1;

	if (lDelta_C > 0)
		lIncrease_C = 1;

	else if (lDelta_C == 0)
		lIncrease_C = 0;

	else
	{
		lIncrease_C = -1;
		lDelta_C = -lDelta_C;
	}

	if (lDelta_P > 0)
		lIncrease_P = 1;

	else if (lDelta_P == 0)
		lIncrease_P = 0;
	else
	{
		lIncrease_P = -1;
		lDelta_P = -lDelta_P;
	}

	if (lDelta_C > lDelta_P)
		lDistance = lDelta_C;

	else
		lDistance = lDelta_P;

	for (us = 0; us <= lDistance + 1; us++)
	{
		LCD_DrawDot(usC_Current, usP_Current, usColor);

		lError_C += lDelta_C;
		lError_P += lDelta_P;

		if (lError_C > lDistance)
		{
			lError_C -= lDistance;
			usC_Current += lIncrease_C;
		}

		if (lError_P > lDistance)
		{
			lError_P -= lDistance;
			usP_Current += lIncrease_P;
		}
	}
}

void LCD_DrawChar(uint16_t usC, uint16_t usP, const char cChar)
{
	uint8_t ucTemp, ucRelativePositon, ucPage, ucColumn;

	ucRelativePositon = cChar - ' ';

	LCD_OpenWindow(usC, usP, WIDTH_EN_CHAR, HEIGHT_EN_CHAR);

	LCD_Write_Cmd(CMD_set_pixel);

	for (ucPage = 0; ucPage < HEIGHT_EN_CHAR; ucPage++)
	{
		ucTemp = ucAscii_1608[ucRelativePositon][ucPage];

		for (ucColumn = 0; ucColumn < WIDTH_EN_CHAR; ucColumn++)
		{
			if (ucTemp & 0x01)
				LCD_Write_Data(0x001F);

			else
				LCD_Write_Data(0xFFFF);

			ucTemp >>= 1;
		}
	}
}

void LCD_DrawString(uint16_t usC, uint16_t usP, const char *pStr)
{
	while (*pStr != '\0')
	{
		if ((usC - LCD_DispWindow_Start_COLUMN + WIDTH_EN_CHAR) > LCD_DispWindow_COLUMN)
		{
			usC = LCD_DispWindow_Start_COLUMN;
			usP += HEIGHT_EN_CHAR;
		}

		if ((usP - LCD_DispWindow_Start_PAGE + HEIGHT_EN_CHAR) > LCD_DispWindow_PAGE)
		{
			usC = LCD_DispWindow_Start_COLUMN;
			usP = LCD_DispWindow_Start_PAGE;
		}

		LCD_DrawChar(usC, usP, *pStr);

		pStr++;

		usC += WIDTH_EN_CHAR;
	}
}

void LCD_DrawChar_Color(uint16_t usC, uint16_t usP, const char cChar, uint16_t usColor_Background, uint16_t usColor_Foreground)
{
	uint8_t ucTemp, ucRelativePositon, ucPage, ucColumn;

	ucRelativePositon = cChar - ' ';

	LCD_OpenWindow(usC, usP, WIDTH_EN_CHAR, HEIGHT_EN_CHAR);

	LCD_Write_Cmd(CMD_set_pixel);

	for (ucPage = 0; ucPage < HEIGHT_EN_CHAR; ucPage++)
	{
		ucTemp = ucAscii_1608[ucRelativePositon][ucPage];

		for (ucColumn = 0; ucColumn < WIDTH_EN_CHAR; ucColumn++)
		{
			if (ucTemp & 0x01)
				LCD_Write_Data(usColor_Foreground);

			else
				LCD_Write_Data(usColor_Background);

			ucTemp >>= 1;
		}
	}
}

void LCD_DrawCross(uint16_t usX, uint16_t usY)
{
	LCD_Clear(usX - 10, usY, 20, 1, RED);
	LCD_Clear(usX, usY - 10, 1, 20, RED);
}

void LCD_DrawString_Color(uint16_t usC, uint16_t usP, const char *pStr, uint16_t usColor_Background, uint16_t usColor_Foreground)
{
	while (*pStr != '\0')
	{
		if ((usC - LCD_DispWindow_Start_COLUMN + WIDTH_EN_CHAR) > LCD_DispWindow_COLUMN)
		{
			usC = LCD_DispWindow_Start_COLUMN;
			usP += HEIGHT_EN_CHAR;
		}

		if ((usP - LCD_DispWindow_Start_PAGE + HEIGHT_EN_CHAR) > LCD_DispWindow_PAGE)
		{
			usC = LCD_DispWindow_Start_COLUMN;
			usP = LCD_DispWindow_Start_PAGE;
		}

		LCD_DrawChar_Color(usC, usP, *pStr, usColor_Background, usColor_Foreground);

		pStr++;

		usC += WIDTH_EN_CHAR;
	}
}

void LCD_GramScan(uint8_t ucOption)
{
	switch (ucOption)
	{
	case 1:

		//		____ x(240)
		//	 |
		//	 |	y(320)

		LCD_Write_Cmd(0x36);
		LCD_Write_Data(0xC8);
		LCD_Write_Cmd(0x2A);
		LCD_Write_Data(0x00); /* x start */
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x00); /* x end */
		LCD_Write_Data(0xEF);

		LCD_Write_Cmd(0x2B);
		LCD_Write_Data(0x00); /* y start */
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x01); /* y end */
		LCD_Write_Data(0x3F);

		break;

	case 2:

		//		|x(320)
		//		|
		//		|___ y(240)

		LCD_Write_Cmd(0x36);
		LCD_Write_Data(0x68);
		LCD_Write_Cmd(0x2A);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x01);
		LCD_Write_Data(0x3F);

		LCD_Write_Cmd(0x2B);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0xEF);

		break;

	case 3:

		//		           |x(320)
		//		           |
		//		y(240) ____|

		LCD_Write_Cmd(0x36);
		LCD_Write_Data(0x28);
		LCD_Write_Cmd(0x2A);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x01);
		LCD_Write_Data(0x3F);

		LCD_Write_Cmd(0x2B);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0xEF);

		break;

	case 4:

		//		|y(320)
		//		|
		//		|___ x(240)

		LCD_Write_Cmd(0x36);
		LCD_Write_Data(0x48);
		LCD_Write_Cmd(0x2A);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0xEF);

		LCD_Write_Cmd(0x2B);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x00);
		LCD_Write_Data(0x01);
		LCD_Write_Data(0x3F);

		break;
	}

	/* write gram start */
	LCD_Write_Cmd(0x2C);
}

//Task 2
void LCD_DrawDot(uint16_t usCOLUMN, uint16_t usPAGE, uint16_t usColor)
{
	/*
	 *  Task 2 : Implement the LCD_DrawDot to turn on a particular dot on the LCD.
	 */

	LCD_OpenWindow(usCOLUMN, usPAGE, 1, 1);
	LCD_Write_Cmd(CMD_set_pixel);
	LCD_Write_Data(usColor);
}

//Task 3
void LCD_DrawEllipse(uint16_t usC, uint16_t usP, uint16_t SR, uint16_t LR, uint16_t usColor)
{
	/*
	 *  Task 3 : Implement LCD_DrawEllipse by using LCD_DrawDot
	 */
	LCD_OpenWindow(usC - SR, usP - LR, 2 * SR - 1, 2 * LR - 1);
	LCD_Write_Cmd(CMD_set_pixel);
	for (uint16_t p = 1; p < 2 * LR; p++)
	{
		for (uint16_t c = 1; c < 2 * SR; c++)
		{
			double track = (double)((c - SR) * (c - SR)) / (SR * SR) + (double)((p - LR) * (p - LR)) / (LR * LR);
			if (track >= 0.92 && track <= 1.00)
				LCD_Write_Data(usColor);
			else
				LCD_Write_Data(WHITE);
		}
	}
}

void LCD_DrawChinese(uint16_t usC, uint16_t usP, uint16_t usColor)
{
	const uint8_t code[][72] =
		{
			/*纵向取模上高位,数据排列:从上到下从左到右 */
			//"欢",
			{0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x01, 0x80,
			 0x10, 0x01, 0xA0, 0x30, 0x01, 0x10, 0xE0, 0x01,
			 0x0F, 0x80, 0x03, 0x3F, 0x00, 0x03, 0xFB, 0x80,
			 0x03, 0xC1, 0xC0, 0x00, 0x00, 0x08, 0x00, 0x60,
			 0x18, 0x01, 0xC0, 0x70, 0x07, 0xBB, 0xC0, 0xFD,
			 0xBF, 0x00, 0x71, 0x03, 0x00, 0x41, 0x01, 0xC0,
			 0x03, 0x20, 0x70, 0x03, 0xC0, 0x38, 0x03, 0x80,
			 0x38, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00,
			 0x00, 0x08, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00},

			//"迎",
			{0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0x00, 0x20,
			 0x60, 0x10, 0x60, 0x60, 0x18, 0x7E, 0x60, 0x1C,
			 0x7F, 0xC0, 0x0C, 0x20, 0x60, 0x00, 0x00, 0x60,
			 0x02, 0x00, 0x20, 0x03, 0xFE, 0x20, 0x07, 0xFC,
			 0x30, 0x0C, 0x18, 0x30, 0x78, 0x30, 0x18, 0x70,
			 0x00, 0x18, 0x33, 0xFF, 0xF8, 0x03, 0xFF, 0xFC,
			 0x06, 0x10, 0x0C, 0x04, 0x18, 0x0C, 0x0F, 0xF8,
			 0x0C, 0x07, 0xF0, 0x0C, 0x07, 0x00, 0x0C, 0x00,
			 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18},

			//"使",
			{0x00, 0x04, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x18,
			 0x00, 0x00, 0x30, 0x00, 0x00, 0xE0, 0x00, 0x03,
			 0xFF, 0xFC, 0x3F, 0x7F, 0xF8, 0x7C, 0x00, 0x00,
			 0x30, 0x00, 0x08, 0x00, 0x42, 0x08, 0x00, 0x7A,
			 0x18, 0x02, 0x4B, 0x30, 0x02, 0x49, 0xE0, 0x06,
			 0x4F, 0xC0, 0xFF, 0xFF, 0x40, 0x7F, 0xC8, 0x60,
			 0x0C, 0x88, 0x30, 0x0C, 0xB8, 0x18, 0x0D, 0xF8,
			 0x1C, 0x09, 0xC0, 0x1C, 0x00, 0xC0, 0x0C, 0x00,
			 0x00, 0x0C, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x0C},

			//"用",
			{0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00,
			 0x0C, 0x00, 0x00, 0x18, 0x00, 0x00, 0x70, 0x1C,
			 0x7F, 0xC0, 0x1F, 0xFF, 0x00, 0x18, 0x00, 0x00,
			 0x18, 0x84, 0x00, 0x10, 0x8C, 0x00, 0x18, 0x8C,
			 0x00, 0x1F, 0xFF, 0xF0, 0x1F, 0x88, 0x00, 0x31,
			 0x88, 0x00, 0x31, 0x98, 0x00, 0x20, 0x08, 0x10,
			 0x30, 0x00, 0x1C, 0x3F, 0xFF, 0xFC, 0x3F, 0xFF,
			 0xFC, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		};

	uint8_t ucTemp, ucPage, ucColumn;

	for (uint8_t c = 0; c < 4; c++)
	{
		LCD_OpenWindow(usC, usP + c * 24, 24, 24);

		LCD_Write_Cmd(CMD_set_pixel);

		for (ucPage = 0; ucPage < 24; ucPage++)
		{
			for (uint8_t i = 0; i < 3; i++)
			{
				ucTemp = code[c][ucPage * 3 + (2 - i)];
				for (ucColumn = 0; ucColumn < 8; ucColumn++)
				{
					if (ucTemp & 0x01)
						LCD_Write_Data(usColor);

					else
						LCD_Write_Data(0xFFFF);

					ucTemp >>= 1;
				}
			}
		}
	}
}

void LCD_DrawChar_2040_Rotate(uint16_t usC, uint16_t usP, uint16_t usColor, const char c)
{
	uint8_t ucTemp, ucPage, ucColumn;

	LCD_OpenWindow(usC, usP, 40, 20);

	LCD_Write_Cmd(CMD_set_pixel);

	for (ucPage = 0; ucPage < 20; ucPage++)
	{
		for (int8_t i = 5 - 1; i >= 0; i--)
		{
			ucTemp = ucAscii_2040[(uint8_t)c - 32][ucPage * 5 + i];
			for (ucColumn = 0; ucColumn < 8; ucColumn++)
			{
				if (ucTemp & 0x01)
					LCD_Write_Data(usColor);

				else
					LCD_Write_Data(0xFFFF);

				ucTemp >>= 1;
			}
		}
	}
}

void LCD_DrawChar_2448_Rotate(uint16_t usC, uint16_t usP, uint16_t usColor, const char c)
{
	uint8_t ucTemp, ucPage, ucColumn;

	LCD_OpenWindow(usC, usP, 48, 24);

	LCD_Write_Cmd(CMD_set_pixel);

	for (ucPage = 0; ucPage < 24; ucPage++)
	{
		for (int8_t i = 6 - 1; i >= 0; i--)
		{
			ucTemp = ucAscii_2448[(uint8_t)c - 32][ucPage * 6 + i];
			for (ucColumn = 0; ucColumn < 8; ucColumn++)
			{
				if (ucTemp & 0x01)
					LCD_Write_Data(usColor);

				else
					LCD_Write_Data(0xFFFF);

				ucTemp >>= 1;
			}
		}
	}
}

void LCD_DrawString_2448_Rotate(uint16_t usC, uint16_t usP, const char *pStr)
{
	while (*pStr != '\0')
	{
		if ((usC - LCD_DispWindow_Start_COLUMN + WIDTH_EN_CHAR) > LCD_DispWindow_COLUMN)
		{
			usC = LCD_DispWindow_Start_COLUMN;
			usP += HEIGHT_EN_CHAR;
		}

		if ((usP - LCD_DispWindow_Start_PAGE + HEIGHT_EN_CHAR) > LCD_DispWindow_PAGE)
		{
			usC = LCD_DispWindow_Start_COLUMN;
			usP = LCD_DispWindow_Start_PAGE;
		}

		LCD_DrawChar_2448_Rotate(usC, usP, BLUE, *pStr);

		pStr++;

		usP += 24;
	}
}

void lcd_draw_icon(uint8_t x, uint8_t y, uint8_t size_x, uint8_t size_y, const uint8_t *code)
{
	LCD_OpenWindow(x, y, size_x, size_y);
	LCD_Write_Cmd(CMD_set_pixel);
	for (uint16_t i = 0; i < size_y; i++)
	{
		for (uint16_t j = 0; j < size_x; j++)
		{
			uint16_t color =
				(*(code + (j + i * size_y) * 3 + 0) * 0x1f / 0xff & 0x1f) << 11 | (*(code + (j + i * size_y) * 3 + 1) * 0x3f / 0xff & 0x3f) << 5 | (*(code + (j + i * size_y) * 3 + 2) * 0x1f / 0xff & 0x1f);
			// LCD_DrawDot(i, j, color);
			LCD_Write_Data(color);
		}
	}
}

void lcd_draw_icon_wifi(uint8_t x, uint8_t y)
{
	lcd_draw_icon(x, y, 64, 64, *wifi_code);
}

void lcd_draw_icon_clock(uint8_t x, uint8_t y)
{
	lcd_draw_icon(x, y, 120, 120, *clock_code);
}

void lcd_draw_icon_bird(uint8_t x, uint8_t y)
{
	lcd_draw_icon(x, y, 120, 120, *bird_code);
}

void lcd_draw_icon_snake(uint8_t x, uint8_t y)
{
	lcd_draw_icon(x, y, 120, 120, *snake_code);
}

void lcd_draw_icon_gallery(uint8_t x, uint8_t y)
{
	lcd_draw_icon(x, y, 120, 120, *gallery_code);
}

void lcd_draw_icon_music(uint8_t x, uint8_t y)
{
	lcd_draw_icon(x, y, 120, 120, *music_code);
}

void lcd_draw_icon_game(uint8_t x, uint8_t y)
{
	lcd_draw_icon(x, y, 120, 120, *game_code);
}

void lcd_draw_icon_temperature(uint8_t x, uint8_t y)
{
	lcd_draw_icon(x, y, 64, 64, *temperature_code);
}

void lcd_draw_icon_humidity(uint8_t x, uint8_t y)
{
	lcd_draw_icon(x, y, 64, 64, *humidity_code);
}

void LCD_DrawSquare(uint16_t usCOLUMN, uint16_t usPAGE, uint16_t HEIGHT, uint16_t usColor){
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < HEIGHT; j++){
			LCD_DrawDot(usCOLUMN+i, usPAGE+j, usColor);
		}
	}
}