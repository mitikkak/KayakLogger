
#include "Components.h"

#ifdef ACCELEROMETER_ON
ADXL345 accMeter;
#endif
SdFat sdFat;
Logger logger(sdFat, SDFAT_CS);
StatusIndicator statusIndicator(STATUS_INDICATOR_LED);
#ifdef GPS_ON
TinyGPS gps;
#endif
#include "Arduino.h"
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
unsigned long prevTimeTiltHandled = 0;
unsigned long prevTimeGpsHandled = 0;
AverageSpeed averageSpeed;
Distance distance;
