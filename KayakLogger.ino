#include <Wire.h>
#include <ADXL345.h>
#include <SdFat.h>
#include <SoftwareSerial.h>

#include <TinyGPS.h>

#include "PreCompilerOptions.h"

#include "ElementQueue.h"

#include "StatusIndicator.h"

#include "Logger.h"

#include "Components.h"

#include "Setup.h"

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
    GpsReport gpsReport(ss, gps);
    StatusIndicator::Status const reportStatus = gpsReport.write(logger);
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeGpsHandled = timeNow;
  }
  else
  {
      GpsReport gpsReport(ss, gps);
      gpsReport.readGps();
  }
#endif
  statusIndicator.continueCurrentState(timeNow);
}



