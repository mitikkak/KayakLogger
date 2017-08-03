
#include "PreCompilerOptions.h"
#include "PinLayout.h"

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
extern ADXL345 accMeter;
#endif
extern SdFat sdFat;
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
extern LiquidCrystal lcd;
extern unsigned long prevTimeTiltHandled;
extern unsigned long prevTimeGpsHandled;
#include "AverageSpeed.h"
extern AverageSpeed averageSpeed;
#include "Distance.h"
extern Distance distance;
