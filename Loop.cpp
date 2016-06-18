
#include "Loop.h"
#include "Arduino.h"
#include "Components.h"
#include "TiltReport.h"

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
