
#include "Loop.h"
#include "Arduino.h"
#include "Components.h"
#include "TiltReport.h"
#include "GpsReport.h"

void loop()
{
  unsigned long timeNow = millis();
#ifdef ACCELEROMETER_ON
  if (timeNow - prevTimeTiltHandled > TILT_MEASUREMENT_PERIOD)
  {
    TiltReport tiltReport(accMeter);
    StatusIndicator::Status const reportStatus = tiltReport.write(logger);
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeTiltHandled = timeNow;
  }
#endif
#ifdef GPS_ON
  GpsReport gpsReport(gps);
  if (timeNow - prevTimeGpsHandled > GPS_MEASUREMENT_PERIOD)
  {

    StatusIndicator::Status const reportStatus = gpsReport.write(logger);
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeGpsHandled = timeNow;
    SpeedMessage msg = gpsReport.speedMessage();
    float averageSpeedValue(0);
    if (gpsReport.HDOP < HDOP_UNRELIABLE)
    {
        averageSpeed.add(msg.value);
        StatusIndicator::Status const averageSpeedStatus = averageSpeed.write(logger, averageSpeedValue);
        statusIndicator.newEvent(averageSpeedStatus, timeNow);
        distance.add(msg.value);
        StatusIndicator::Status const distanceStatus = distance.write(logger);
        statusIndicator.newEvent(distanceStatus, timeNow);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(gpsReport.HDOP);
    lcd.setCursor(0, 1);
    lcd.print(msg.header);lcd.print(msg.value, 3);
    lcd.setCursor(0, 2);
    lcd.print(averageSpeedValue, 3);
    lcd.setCursor(0, 3);
    lcd.print(distance.value(), 3);
  }
  else
  {
      gpsReport.readGps();
  }
#endif

  statusIndicator.continueCurrentState(timeNow);
}
