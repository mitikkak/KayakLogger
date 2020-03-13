
#include "PreCompilerOptions.h"
#include "PinLayout.h"

#ifdef UNIT_TEST
 #include "FakeSdFat.h"
#else
 #if defined ESP8266 || defined ESP32
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

#if defined ESP8266
typedef struct SDClass SD_TYPE;
#elif defined ESP32
typedef struct fs::SDFS SD_TYPE;
#else
typedef struct SdFat SD_TYPE;
#endif
extern SD_TYPE sdFat;
extern Logger logger;
extern StatusIndicator statusIndicator;
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

#ifdef PADDLE_IMU

#ifdef ESP32
#include "WiFi.h"
#include "AsyncUDP.h"
#else
#include <ESP8266WiFi.h>
#include "ESPAsyncUDP.h"
#endif

extern const char* const ssid;
extern const char* const password;
extern AsyncUDP udp;

#endif //PADDLE_IMU