#ifdef ESP8266
using namespace std;
#endif
#include "Components.h"

#ifdef ACCELEROMETER_ON
ADXL345 accMeter;
#endif

#if defined ESP8266 || defined ESP32
Logger logger(SD, SDFAT_CS);
#else
SD_TYPE sdFat;
Logger logger(sdFat, SDFAT_CS);
#endif
#ifdef GPS_ON
TinyGPS gps;
#endif
#include "Arduino.h"

#if defined ESP8266
Adafruit_PCD8544 lcdImpl = Adafruit_PCD8544(D3, D2, D1);
#elif defined ESP32
const uint8_t CLK = 25;
const uint8_t DIN = 26;
const uint8_t DC = 27;
const uint8_t CE = 14;
const uint8_t RESET = 12;
Adafruit_PCD8544 lcdImpl = Adafruit_PCD8544(CLK, DIN, DC, CE, RESET);
#else
#error Non-supported platform for lcd!
#endif
LcdIf lcd;

unsigned long prevTimeTiltHandled = 0;
unsigned long prevTimeGpsHandled = 0;
AverageSpeed averageSpeed;
Distance distance_;
