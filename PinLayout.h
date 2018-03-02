
#ifdef ESP8266
/*
ESP8266:
RX- GPS
TX-GPS


*/
#define SDFAT_CS 4
#define STATUS_INDICATOR_LED 0xFF
#define HALL_SWITCH A0
#ifndef IIC_LCD
#error "Only IIC LCD supported on ESP8266"
#endif

#else
/*
ATMEGA328:

RX - GPS
TX - GPS
D2 - NC
D3 - LCD_RS
D4 - LCD_EN
D5 - LCD_D4
D6 - LCD_D5
D7 - LCD_D6
D8 - LCD_D7
D9 - STATUS_INDICATOR_LED
D10 - SDCARD
D11 - SDCARD (SPI)
D12 - SDCARD (SPI)
D13 - SDCARD (SPI)
A0 - HALL_SWITCH
A1 - NC
A2 - NC
A3 - NC
A4 - ADXL (I2C)
A5 - ADXL (I2C)
*/

#define SDFAT_CS 10
#define STATUS_INDICATOR_LED 9
#ifndef IIC_LCD
#define LCD_RS 3
#define LCD_ENABLE 4
#define LCD_D4 5
#define LCD_D5 6
#define LCD_D6 7
#define LCD_D7 8
#endif
#define HALL_SWITCH A0
#endif

