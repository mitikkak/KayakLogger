
#include "Loop.h"
#include "Arduino.h"
#ifdef ESP8266
using namespace std;
#endif
#include "Components.h"
#include "TiltReport.h"
#include "GpsReport.h"

int hallSwitchState = 0;
typedef enum
{
    active = 0,
    inActive = 1,
    goingActive = 2
} Activity;
Activity activity = inActive;
unsigned long prevTimeActivityChecked = 0;
const unsigned long activityTimeCheckThreshold = 2000;
unsigned long activationTime = 0;
const unsigned long activationDelay = 180000;


Activity isActive(const unsigned long timeNow)
{
   hallSwitchState = analogRead(HALL_SWITCH);
   const int activityLowThreshold = 750;
   const int activityHighThreshold = 850;
   Activity retValue = activity;
   if ((hallSwitchState < activityLowThreshold) || (hallSwitchState > activityHighThreshold) )
   {
       if (retValue == active)
       {
           retValue = inActive;
       }
       else if (retValue == inActive)
       {
           retValue = goingActive;
           activationTime = timeNow + activationDelay;

       }
   }
   if (retValue == goingActive && timeNow > activationTime)
   {
       retValue = active;
   }
   return retValue;
}
void loop()
{
  unsigned long timeNow = millis();
#ifdef HALL_SWITCH_ON
  if (timeNow > (prevTimeActivityChecked + activityTimeCheckThreshold))
  {
    activity = isActive(timeNow);
    prevTimeActivityChecked = timeNow;
  }

  if (activity == inActive)
  {
     lcd.clear();
     lcd.print(String(hallSwitchState));
     delay(100);
     return;
  }
  if (activity == goingActive)
  {
      lcd.clear();
      lcd.print("Going active in: ");
      unsigned long const untilActive = activationTime > timeNow ? (activationTime-timeNow) : 0;
      lcd.print(String(untilActive));
      delay(100);
      return;
  }
#endif
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
    bool const reportStatus = gpsReport.write(logger);
    prevTimeGpsHandled = timeNow;
    SpeedMessage speed = gpsReport.speedMessage();
    if (gpsReport.HDOP < HDOP_UNRELIABLE)
    {
        averageSpeed.add(speed.value);
        bool const averageSpeedStatus = averageSpeed.write(logger);
        distance_.add(speed.value);
        bool const distanceStatus = distance_.write(logger);
    }
    lcd.clear();
    lcd.bigText();
#if 0
    if (gpsReport.HDOP > HDOP_UNRELIABLE) { lcd.printer().print("MAX"); }
    else { lcd.printer().print(gpsReport.HDOP); }
    lcd.printer().print("|");
    lcd.printer().print(gps.satellites());
    lcd.row(1);
    lcd.printer().print(speed.value, 3);
    lcd.row(2);
    lcd.printer().print(averageSpeed.value(), 3);
    lcd.printer().print("|");
    lcd.printer().print(distance_.value(), 3);
    lcd.row(2);
    lcd.printer().print(gpsReport.hour());
    lcd.printer().print(":");
    lcd.printer().print(gpsReport.minute());
    lcd.printer().print(":");
    lcd.printer().print(gpsReport.second());
#else
    Serial.println(millis());
    paddleImuReport.decodeAngularPosition();
    lcd.printer().print(paddleImuReport.pitch());
    lcd.row(1);
    lcd.printer().print(paddleImuReport.roll());
    lcd.row(2);
    lcd.printer().print(paddleImuReport.yaw());
#endif
    lcd.display();
    lcd.smallText();
  }
  else
  {
      gpsReport.readGps();
  }
#endif
}
