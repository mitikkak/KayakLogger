
#include "Components.h"

#ifdef ACCELEROMETER_ON
ADXL345 acc;
#endif
SdFat sdFat;
Logger logger(sdFat, 10);
StatusIndicator statusIndicator(5);
#ifdef GPS_ON
TinyGPS gps;
SoftwareSerial ss(4, 3);
#endif
#include "Arduino.h"
LiquidCrystal lcd(6, 7, A0, A1, A2, A3);
unsigned long prevTimeTiltHandled = 0;
unsigned long prevTimeGpsHandled = 0;