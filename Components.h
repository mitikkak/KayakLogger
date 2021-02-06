
#pragma once

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

#include "LcdIf.h"

#if defined ESP8266
typedef struct SDClass SD_TYPE;
#elif defined ESP32
typedef struct fs::SDFS SD_TYPE;
#else
typedef struct SdFat SD_TYPE;
#endif
extern SD_TYPE sdFat;
extern Logger logger;
#ifdef GPS_ON
 #ifdef UNIT_TEST
  #include "FakeSoftwareSerial.h"
  #include "FakeTinyGPS.h"
 #else
  #include "TinyGPS++.h"
 #endif
 extern TinyGPSPlus gps;
#endif
#include "AverageSpeed.h"
extern AverageSpeed averageSpeed;
#include "Distance.h"
extern Distance distance_;
#ifdef ESP32
#include "WiFi.h"
#include "AsyncUDP.h"
#include "ESPmDNS.h"
#else
#include <ESP8266WiFi.h>
#include "ESPAsyncUDP.h"
#include "ESP8266mDNS.h"
#endif
extern const char* const ssid;
extern const char* const password;
extern const char* const mdnsHost;
#include "AsyncWebServerWrapper.h"
extern AsyncWebServerWrapper server;

extern AsyncUDP udp;
extern uint32_t numOfMsgs;

#include "PaddleImuReport.h"
extern PaddleImuReport paddleImuReport;
