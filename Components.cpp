#ifdef ESP8266
using namespace std;
#endif
#include "Components.h"

#ifdef ACCELEROMETER_ON
ADXL345 accMeter;
#endif

#ifndef ESP8266
SD_TYPE sdFat;
Logger logger(sdFat, SDFAT_CS);
#else
Logger logger(SD, SDFAT_CS);
#endif
StatusIndicator statusIndicator(STATUS_INDICATOR_LED);
#ifdef GPS_ON
TinyGPS gps;
#endif
#include "Arduino.h"
#ifdef IIC_LCD
LiquidCrystal_I2C lcd(IIC_LCD_ADDRESS,20,4);
#else
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
#endif
unsigned long prevTimeTiltHandled = 0;
unsigned long prevTimeGpsHandled = 0;
AverageSpeed averageSpeed;
Distance distance_;
