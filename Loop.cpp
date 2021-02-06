
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
    return gps.hdop.hdop() < badHdop;
}
bool gpsGoodStatus()
{
    return(gps.ggaFix and hdopBelowLimit());
}

class ScreenSelector
{
public:
    enum Type {velocity, time_and_distance, gps_status};
    ScreenSelector()
    : currentStatus{unstable},
      goodStatus{0},
      listIdx{0},
      unstableList{time_and_distance, velocity,
               gps_status, velocity,
               gps_status, velocity,
               gps_status, velocity,
               gps_status, velocity},
      stableList{time_and_distance,
            velocity, velocity,
            velocity, velocity,
            gps_status,
            velocity, velocity,
            velocity, velocity}
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
            if (goodStatus > numOf and currentStatus == unstable)
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
        if (listIdx >= numOf)
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
double lat1{0.0f};
double lng1{0.0f};
unsigned int timesLogged{0};
bool timeToLog(unsigned long timeNow)
{
    return (timeNow - prevTimeLogged > GPS_MEASUREMENT_PERIOD);
}
unsigned long prevTimeRefreshed{0};
bool timeToRefreshScreen(unsigned long timeNow)
{
    static const unsigned long SCREEN_REFRESH_PERIOD{5000};
    return (timeNow - prevTimeRefreshed > SCREEN_REFRESH_PERIOD);
}
bool timeToRefreshScreen_paddleImu(unsigned long timeNow)
{
    static const unsigned long SCREEN_REFRESH_PERIOD{200};
    return (timeNow - prevTimeRefreshed > SCREEN_REFRESH_PERIOD);
}
double totalDistance{0.0f};
double totalDistanceWithSpeed{0.0f};
double totalSpeed{0.0f};
double highestSpeed{0.0f};
const double lowestSpeedInitValue{99.0f};
double lowestSpeed{lowestSpeedInitValue};
unsigned long prevTimeSpeedCalculated{0};
unsigned int numOfMessages{0};

bool paddleImuConnected()
{
    return (numOfMsgs > 0);
}
void paddleImuLogging()
{
    unsigned long timeNow = millis();
    if (timeToRefreshScreen_paddleImu(timeNow))
    {
        paddleImuReport.decodeAngularPosition();
        lcd.clear();
        lcd.row(0);
        //lcd.smallText();
//        lcd.printer().print(numOfMsgs);
//        lcd.row(1);
//        lcd.printer().print(paddleImuReport.sn());
//        lcd.row(2);
        lcd.printer().print(paddleImuReport.pitch());
        lcd.row(1);
        lcd.printer().print(paddleImuReport.roll());
        lcd.row(2);
        lcd.printer().print(paddleImuReport.yaw());
        prevTimeRefreshed = timeNow;
        lcd.display();
        numOfMsgs = 0;
    }
}
void normalLogging()
{
    unsigned long timeNow = millis();
    GpsReport gpsReport(gps);
    TinyGPSPlus::EncodeStatus const encodeStatus = gps.readSerialGiveStatus();
    // Purpose is to not log during GPS's  burst of sentences
  #if 0
    if (encodeStatus == TinyGPSPlus::EncodeStatus::GGA and
        gpsGoodStatus())
    {
        if (prevTimeSpeedCalculated)
        {
            numOfMessages++;
            double const deltaTimeInHours = static_cast<double>(timeNow - prevTimeSpeedCalculated) / 1000 / 60 / 60;
            totalSpeed += gps.speed.kmph();
            double const distanceWithSpeed = (gps.speed.kmph() * deltaTimeInHours) * 1000;
            totalDistanceWithSpeed += distanceWithSpeed;
        }
        prevTimeSpeedCalculated = timeNow;
    }
    if (timeToLog(timeNow))
    {
        timesLogged++;
        prevTimeLogged = timeNow;
        lcd.clear();
        lcd.printer().print(totalDistanceWithSpeed, 7);
        lcd.row(1);
        double const averageSpeed = (numOfMessages) ? (totalSpeed / numOfMessages) : 0.0f;
        lcd.printer().print(averageSpeed, 7);
        lcd.row(2);
        lcd.printer().print(timesLogged);
        lcd.display();
    }
  #else
    if (encodeStatus == TinyGPSPlus::EncodeStatus::GGA and
        gpsGoodStatus())
    {
        //const bool reportStatus = gpsReport.write(logger);
        unsigned const deltaTime = timeNow - prevTimeLogged;
        //if (timeToLog(timeNow)) // TODO: deltaTime
        {
            SpeedMessage const speed{gps.speed.kmph()};
            if (speed.value > highestSpeed) { highestSpeed = speed.value; }
            if (speed.value < lowestSpeed) { lowestSpeed = speed.value; }
            averageSpeed.add(speed.value);
            //const bool averageSpeedStatus = averageSpeed.write(logger);
            distance_.add(speed.value, deltaTime);
            //const bool distanceStatus = distance_.write(logger);
        }
        prevTimeLogged = timeNow;
    }
    if (timeToRefreshScreen(timeNow))
    {
        prevTimeRefreshed = timeNow;
        lcd.clear();
        screenSelector.update();
        if (screenSelector.get() == ScreenSelector::velocity)
        {
            lcd.printer().print(lowestSpeed, 1);
            lcd.row(1);
            lcd.printer().print(highestSpeed, 1);
            lcd.row(2);
            lcd.printer().print(averageSpeed.value(), 3);
            highestSpeed = 0.0f;
            lowestSpeed = lowestSpeedInitValue;
        }
        else if (screenSelector.get() == ScreenSelector::time_and_distance)
        {
            lcd.printer().print(gps.time.hour());
            lcd.printer().print(":");
            lcd.printer().print(gps.time.minute());
            lcd.row(1);
            lcd.printer().print(timeNow / 1000 / 60);
            lcd.row(2);
            lcd.printer().print(distance_.value(), 3);
        }
        else if (screenSelector.get() == ScreenSelector::gps_status)
        {
            lcd.printer().print(gps.ggaFix);
            lcd.row(1);
            lcd.printer().print(gps.hdop.hdop());
        }
        //else if (screenSelector.get() == ScreenSelector::gps_status)
        //{
        //    lcd.printer().print(gps.satsInView.numOfDb());
        //    lcd.printer().print(":");
        //    lcd.printer().print(gps.satsInView.totalSnr());
        //    lcd.row(1);
        //    lcd.printer().print(gps.gsa.fix());
        //    lcd.printer().print(":");
        //    lcd.print(String(gps.gsa.numSats()));
        //    lcd.row(2);
        //    lcd.printer().print(gps.gsa.hdop());
        //}
  #endif
      lcd.display();
    }
}
void loop()
{
    if (paddleImuConnected())
    {
        paddleImuLogging();
    }
    else
    {
        normalLogging();
    }
}
