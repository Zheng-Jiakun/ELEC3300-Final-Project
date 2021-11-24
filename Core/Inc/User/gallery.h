#ifndef GALLERY_H
#define GALLERY_H

#include "main.h"
#include "cmsis_os.h"
#include "sdio.h"
#include "fatfs.h"
#include "lcd.h"
#include "string.h"

void gallery_init ();
void gallery_slideshow ();

#endif