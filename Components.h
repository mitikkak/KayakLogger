
#include "PreCompilerOptions.h"
#include "PinLayout.h"

#ifdef UNIT_TEST
 #include "FakeSdFat.h"
#else
 #ifdef ESP8266
  #include "SD.h"
 #else
  #include "SdFat.h"
 #endif
#endif
#include "fstream_headers.h"
#include "Logger.h"
#ifdef UNIT_TEST
 #include "FakeLiquidCrystal.h"
#else
  #ifndef IIC_LCD
  #include "LiquidCrystal.h"
  #else
  #define IIC_LCD_ADDRESS 0x27
  #include "LiquidCrystal_I2C.h"
  #endif
#endif

#ifdef ACCELEROMETER_ON
 #include "ADXL345.h"
 extern ADXL345 accMeter;
#endif

#ifdef ESP8266
typedef struct SDClass SD_TYPE;
#else
typedef struct SdFat SD_TYPE;
#endif
extern SD_TYPE sdFat;
extern Logger logger;
#ifdef STATUS_INDICATOR_ON
extern StatusIndicator statusIndicator;
#endif
#ifdef GPS_ON
 #ifdef UNIT_TEST
  #include "FakeSoftwareSerial.h"
  #include "FakeTinyGPS.h"
 #else
  #include "TinyGPS.h"
 #endif
 extern TinyGPS gps;
#endif
#ifndef IIC_LCD
 extern LiquidCrystal lcd;
#else
 extern LiquidCrystal_I2C lcd;
#endif
extern unsigned long prevTimeTiltHandled;
extern unsigned long prevTimeGpsHandled;
#include "AverageSpeed.h"
extern AverageSpeed averageSpeed;
#include "Distance.h"
extern Distance distance_;
