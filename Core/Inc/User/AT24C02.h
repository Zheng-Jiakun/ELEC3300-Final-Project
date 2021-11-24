#ifndef AT24C02_H
#define AT24C02_H

#include "main.h"
//#include "cmsis_os.h"
#include "iic.h"

void eeprom_init();
void eeprom_write_byte(uint16_t address, uint8_t val);
void eeprom_read_byte(uint16_t address, uint8_t *val);


#endif