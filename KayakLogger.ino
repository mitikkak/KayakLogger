#include <Wire.h>
#include <ADXL345.h>
#include <SdFat.h>
#include <SoftwareSerial.h>

#include <TinyGPS.h>

#define GPS_ON
#define ACCELEROMETER_ON
//#define RUNTIME_SERIAL_ON

#define TILT_MEASUREMENT_PERIOD 20
#define GPS_MEASUREMENT_PERIOD 2000

#include "ElementQueue.h"

#include "StatusIndicator.h"

#include "Logger.h"

#ifdef ACCELEROMETER_ON
ADXL345 acc;
#endif

Logger logger(10);
StatusIndicator statusIndicator(5);
#ifdef GPS_ON
TinyGPS gps;
SoftwareSerial ss(4, 3);
#endif
unsigned long prevTimeTiltHandled, prevTimeGpsHandled;
void setup()
{
  #ifdef ACCELEROMETER_ON
  acc.begin();
  #endif
#ifdef RUNTIME_SERIAL_ON
  Serial.begin(115200);
#endif
  #ifdef GPS_ON
  ss.begin(9600);
  #endif
  logger.initSdCard();
  delay(100);
  acc.setRange(ADXL345::RANGE_4G);
  statusIndicator.init();
  prevTimeTiltHandled = millis();
  prevTimeGpsHandled = millis();
}


#include "TiltReport.h"
#ifdef GPS_ON
#include "GpsReport.h"
#endif

void loop()
{
  unsigned long timeNow = millis();
  if (timeNow - prevTimeTiltHandled > TILT_MEASUREMENT_PERIOD)
  {
      TiltReport tiltReport;
    StatusIndicator::Status const reportStatus = tiltReport.write(logger);
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeTiltHandled = timeNow;
  }
#ifdef GPS_ON
  if (timeNow - prevTimeGpsHandled > GPS_MEASUREMENT_PERIOD)
  {
      GpsReport gpsReport;
    StatusIndicator::Status const reportStatus = gpsReport.write(logger);
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeGpsHandled = timeNow;
  }
  else
  {
    readGps();
  }
#endif
  statusIndicator.continueCurrentState(timeNow);
}



