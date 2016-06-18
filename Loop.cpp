
#include "Loop.h"
#include "Arduino.h"
#include "Components.h"
#include "TiltReport.h"
#include "GpsReport.h"

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
  GpsReport gpsReport(gps);
  if (timeNow - prevTimeGpsHandled > GPS_MEASUREMENT_PERIOD)
  {

    StatusIndicator::Status const reportStatus = gpsReport.write(logger);
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeGpsHandled = timeNow;
    SpeedMessage msg = gpsReport.speedMessage();
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(msg.header);lcd.print(msg.value, 3);
  }
  else
  {
      gpsReport.readGps();
  }
#endif

  statusIndicator.continueCurrentState(timeNow);
}
