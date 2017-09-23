
#include "Loop.h"
#include "Arduino.h"
#include "Components.h"
#include "TiltReport.h"
#include "GpsReport.h"

int hallSwitchState = 0;
bool activity = false;
int loggingOn = 0;
unsigned long prevTimeActivityChecked = 0;
const unsigned long activityTimeCheckThreshold = 3000;
bool isActive()
{
   hallSwitchState = analogRead(HALL_SWITCH);
   const int activityThreshold = 300;
   if (hallSwitchState < activityThreshold)
   {
      return activity ? false : true;
   }
   return activity;
}
void loop()
{
  unsigned long timeNow = millis();
  
  if (timeNow > (prevTimeActivityChecked + activityTimeCheckThreshold))
  {
    activity = isActive();
    prevTimeActivityChecked = timeNow;
  }
  if (!activity)
  {
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print(hallSwitchState);
     delay(100);
     return;
  }
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
    if (gpsReport.HDOP < HDOP_UNRELIABLE)
    {
        averageSpeed.add(msg.value);
        StatusIndicator::Status const averageSpeedStatus = averageSpeed.write(logger);
        statusIndicator.newEvent(averageSpeedStatus, timeNow);
        distance.add(msg.value);
        StatusIndicator::Status const distanceStatus = distance.write(logger);
        statusIndicator.newEvent(distanceStatus, timeNow);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(gpsReport.HDOP);
    //lcd.print("|");
    //lcd.print(hallSwitchActive);
    lcd.print("|");
    lcd.print(loggingOn);
    lcd.setCursor(0, 1);
    lcd.print(msg.value, 3);
    lcd.print("|");
    lcd.print(averageSpeed.value(), 3);
    lcd.print("|");
    lcd.print(distance.value(), 3);
  }
  else
  {
      gpsReport.readGps();
  }
#endif

  statusIndicator.continueCurrentState(timeNow);
}
