
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

unsigned long prevTimeScreenChange{0};
static const unsigned long screenChangePeriod{30000};
enum Screen {velocity_and_distance, time_and_gps_status};
Screen getScreen(unsigned long timeNow)
{
    Screen ret{velocity_and_distance};
    if (not gps.gsa.fixIs3d())
    {
        ret = time_and_gps_status;
    }
    if (timeNow - prevTimeScreenChange > screenChangePeriod)
    {
        prevTimeScreenChange = timeNow;
        ret = time_and_gps_status;
    }
    return ret;
}
void loop()
{
  unsigned long timeNow = millis();
  GpsReport gpsReport(gps);
  if (timeNow - prevTimeGpsHandled > GPS_MEASUREMENT_PERIOD)
  {
    const bool reportStatus = gpsReport.write(logger);
    prevTimeGpsHandled = timeNow;
    SpeedMessage speed = gpsReport.speedMessage();
    averageSpeed.add(speed.value);
    const bool averageSpeedStatus = averageSpeed.write(logger);
    distance_.add(speed.value);
    const bool distanceStatus = distance_.write(logger);
    lcd.clear();
    lcd.bigText();
#if !defined PADDLE_IMU
    Screen const screen = getScreen(millis());
    if (screen == velocity_and_distance)
    {
        lcd.printer().print(speed.value, 1);
        lcd.row(1);
        lcd.printer().print(averageSpeed.value(), 1);
        lcd.row(2);
        lcd.printer().print(distance_.value(), 3);
    }
    else
    {
        lcd.printer().print(gps.time.hour());
        lcd.printer().print(":");
        lcd.printer().print(gps.time.minute());
        lcd.row(1);
        lcd.printer().print(gps.gsa.fix());
        lcd.row(2);
        lcd.printer().print(gps.gsa.hdop());
    }
#else
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
}
