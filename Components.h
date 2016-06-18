
#include "PreCompilerOptions.h"

#ifdef UNIT_TEST
#include "FakeSdFat.h"
#else
#include "SdFat.h"
#endif
#include "fstream_headers.h"
#include "Logger.h"
#ifdef UNIT_TEST
#include "FakeLiquidCrystal.h"
#else
#include "LiquidCrystal.h"
#endif

#ifdef ACCELEROMETER_ON
#include "ADXL345.h"
extern ADXL345 acc;
#endif
extern SdFat sdFat;
extern Logger logger;
extern StatusIndicator statusIndicator;
#ifdef GPS_ON
#ifdef UNIT_TEST
#include "FakeTinyGPS.h"
#include "FakeSoftwareSerial.h"
#else
#include "TinyGPS.h"
#include "SoftwareSerial.h"
#endif
extern TinyGPS gps;
extern SoftwareSerial ss;
#endif
extern LiquidCrystal lcd;
extern unsigned long prevTimeTiltHandled;
extern unsigned long prevTimeGpsHandled;
