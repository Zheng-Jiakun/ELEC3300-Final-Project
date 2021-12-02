# ELEC3300-Final-Project

### Sensors
- IMU (MPU6050 via IIC)
- Magnetometer (HMC5883L via IIC)
- Sound sensor (microphone via ADC+DMA with MAX9814 amplifier as a buffer)
- Temperature and humidity sensor (DHT11 via private serial protocol)
- Light sensor (LDR via ADC)
### Data communication & storage
- on board ESP8266 WiFi Module (via UART)
- SD card (via SDIO)
- EEPROM (onboard AT24C02 via IIC)
### User inputs
- LCD display (on board via FSMC)
- Touchscreen (onboard XPT2046 via SPI)
- RGB LED (WS2812B via private serial protocol, driven by PWM with DMA)
- Buttons (on board via GPIO)
- Vibration motor (via GPIO with MOSFET as switch)
- Buzzer (on board via PWM)
- Joystick (via ADC)


![Alt text](pictures/demo/1.jpg?raw=true)
![Alt text](pictures/demo/2.jpg?raw=true)