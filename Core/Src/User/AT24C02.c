#include "AT24C02.h"

void eeprom_init ()
{
    iic_init();
}

void eeprom_write_byte(uint16_t address, uint8_t val)
{
	iic_send_start();

	iic_send_byte(0xA0 + ((address / 256) << 1));
	iic_wait_ack();

	iic_send_byte(address % 256);
	iic_wait_ack();

	iic_send_byte(val);
	iic_wait_ack();

	iic_send_stop();

	HAL_Delay(20);
}

void eeprom_read_byte(uint16_t address, uint8_t *val)
{
	iic_send_start();

	iic_send_byte(0xA0 + ((address / 256) << 1));
	iic_wait_ack();

	iic_send_byte(address % 256);
	iic_wait_ack();

	iic_send_start();

	iic_send_byte(0xA1);
	iic_wait_ack();

	iic_read_byte(val);
	iic_send_nack();

	iic_send_stop();
}