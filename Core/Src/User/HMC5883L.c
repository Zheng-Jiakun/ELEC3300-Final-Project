#include "HMC5883L.h"

uint16_t compass_angle;

const uint8_t HMC5883L_Addr = 0x3C;

void HMC5883L_write_byte(uint8_t add, uint8_t val)
{
    iic_send_start();

    iic_send_byte(HMC5883L_Addr);
    iic_wait_ack();

    iic_send_byte(add);
    iic_wait_ack();

    iic_send_byte(val);
    iic_wait_ack();

    iic_send_stop();

    // HAL_Delay(1);
}

void HMC5883L_read_byte(uint8_t add, uint8_t *val)
{
    iic_send_start();

    iic_send_byte(HMC5883L_Addr);
    iic_wait_ack();

    iic_send_byte(add);
    iic_wait_ack();

    iic_send_start();

    iic_send_byte(HMC5883L_Addr + 1);
    iic_wait_ack();

    iic_read_byte(val);
    iic_send_nack();

    iic_send_stop();
}

void HMC5883L_init()
{
    iic_init();
    uint8_t CRA = 0x70, CRB = 0xA0;
	// HAL_I2C_Mem_Write(&hi2c2, HMC5883L_Addr<<1, 0x00, 1, &CRA, 1, 100);
	// HAL_I2C_Mem_Write(&hi2c2, HMC5883L_Addr<<1, 0x01, 1, &CRB, 1, 100);
    HMC5883L_write_byte(0x00, CRA);
    HMC5883L_write_byte(0x01, CRB);
}

void HMC5883L_update_data()
{
    int16_t value_x, value_y;
    uint8_t raw_dat;
    uint8_t mode = 0x01;
    // HAL_I2C_Mem_Write(&hi2c2, HMC5883L_Addr<<1, 0x02, 1, &mode, 1, 100);
    // HAL_Delay(6);
    // HAL_I2C_Mem_Read(&hi2c2, HMC5883L_Addr<<1, 0x03, 1, &raw_dat, 1, 100);
    // value_x = raw_dat << 8;
    // HAL_I2C_Mem_Read(&hi2c2, HMC5883L_Addr<<1, 0x04, 1, &raw_dat, 1, 100);
    // value_x |= raw_dat;
    
    // HAL_I2C_Mem_Read(&hi2c2, HMC5883L_Addr<<1, 0x05, 1, &raw_dat, 1, 100);
    // HAL_I2C_Mem_Read(&hi2c2, HMC5883L_Addr<<1, 0x06, 1, &raw_dat, 1, 100);
    
    // HAL_I2C_Mem_Read(&hi2c2, HMC5883L_Addr<<1, 0x07, 1, &raw_dat, 1, 100);
    // value_y = raw_dat << 8;
    // HAL_I2C_Mem_Read(&hi2c2, HMC5883L_Addr<<1, 0x08, 1, &raw_dat, 1, 100);
    // value_y |= raw_dat;
    HMC5883L_write_byte(0x02, mode);
    HAL_Delay(6);
    HMC5883L_read_byte(0x03, &raw_dat);
    value_x = raw_dat << 8;
    HMC5883L_read_byte(0x04, &raw_dat);
    value_x |= raw_dat;

    HMC5883L_read_byte(0x05, &raw_dat);
    HMC5883L_read_byte(0x06, &raw_dat);

    HMC5883L_read_byte(0x07, &raw_dat);
    value_y = raw_dat << 8;
    HMC5883L_read_byte(0x08, &raw_dat);
    value_y |= raw_dat;
    
    compass_angle = (uint16_t)(atan2(value_y, value_x)/3.14*179.5+179.0);
}
