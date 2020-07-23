
#include "Loop.h"
#include "Arduino.h"
#ifdef ESP8266
using namespace std;
#endif
#include "Components.h"
#include "TiltReport.h"
#include "GpsReport.h"

double const badHdop{3.0};
bool hdopBelowLimit()
{
    return gps.gsa.hdop() < badHdop;
}
bool gpsGoodStatus()
{
    return(gps.gsa.fixIs3d() and hdopBelowLimit());
}

class ScreenSelector
{
public:
    enum Type {velocity_and_distance, time_status, gps_status};
    ScreenSelector()
    : currentStatus{unstable},
      goodStatus{0},
      listIdx{0},
      unstableList{time_status, velocity_and_distance,
               gps_status, velocity_and_distance,
               gps_status, velocity_and_distance,
               gps_status, velocity_and_distance,
               gps_status, velocity_and_distance},
      stableList{time_status,
            velocity_and_distance, velocity_and_distance,
            velocity_and_distance, velocity_and_distance,
            gps_status,
            velocity_and_distance, velocity_and_distance,
            velocity_and_distance, velocity_and_distance}
    {}
    void update()
    {
        if (not gpsGoodStatus())
        {
            goodStatus = 0;
            currentStatus = unstable;
        }
        else
        {
            goodStatus++;
            if (goodStatus > 10 and currentStatus == unstable)
            {
                currentStatus = stable;
            }
        }
        updateListIndex();
    }
    Type get() const
    {
        return (currentStatus == stable) ? stableList[listIdx] : unstableList[listIdx];
    }
private:
    void updateListIndex()
    {
        listIdx++;
        if (listIdx > numOf)
        {
            listIdx = 0;
        }
    }
    enum status {unstable, stable};
    status currentStatus;
    unsigned int listIdx;
    unsigned int goodStatus;
    static const unsigned int numOf{10};
    const Type unstableList[numOf];
    const Type stableList[numOf];
};

ScreenSelector screenSelector;

unsigned long prevTimeLogged{0};
bool timeToLog(unsigned long timeNow)
{
    return (timeNow - prevTimeLogged > GPS_MEASUREMENT_PERIOD);
}
void loop()
{
  unsigned long timeNow = millis();
  GpsReport gpsReport(gps);
  bool const gpsUpdated = gps.readSerial();
  // Purpose is to not log during GPS's  burst of sentences
  if (not gpsUpdated and timeToLog(timeNow))
  {
    const bool reportStatus = gpsReport.write(logger);
    prevTimeLogged = timeNow;
    SpeedMessage speed;
    if (gpsGoodStatus())
    {
        speed = gpsReport.speedMessage();
        averageSpeed.add(speed.value);
        const bool averageSpeedStatus = averageSpeed.write(logger);
        distance_.add(speed.value);
        const bool distanceStatus = distance_.write(logger);
    }
    lcd.clear();
    lcd.bigText();
#if !defined PADDLE_IMU
    screenSelector.update();
    if (screenSelector.get() == ScreenSelector::velocity_and_distance)
    {
        lcd.printer().print(speed.value, 1);
        lcd.row(1);
        lcd.printer().print(averageSpeed.value(), 3);
        lcd.row(2);
        lcd.printer().print(distance_.value(), 3);
    }
    else if (screenSelector.get() == ScreenSelector::time_status)
    {
        lcd.printer().print(gps.time.hour());
        lcd.printer().print(":");
        lcd.printer().print(gps.time.minute());
        lcd.row(1);
        lcd.printer().print(timeNow / 1000 / 60);
    }
    else if (screenSelector.get() == ScreenSelector::gps_status)
    {
        lcd.printer().print(gps.satsInView.numOfDb());
        lcd.printer().print(":");
        lcd.printer().print(gps.satsInView.totalSnr());
        lcd.row(1);
        lcd.printer().print(gps.gsa.fix());
        lcd.printer().print(":");
        lcd.print(String(gps.gsa.numSats()));
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
}
