
#include "PreCompilerOptions.h"

#ifdef UNIT_TEST
#include "FakeSdFat.h"
#else
#include "SdFat.h"
#endif
#include "fstream_headers.h"
#include "Logger.h"

#ifdef ACCELEROMETER_ON
extern ADXL345 acc;
#endif
extern SdFat sdFat;
extern Logger logger;
extern StatusIndicator statusIndicator;
#ifdef GPS_ON
extern TinyGPS gps;
extern SoftwareSerial ss;
#endif
extern unsigned long prevTimeTiltHandled;
extern unsigned long prevTimeGpsHandled;
