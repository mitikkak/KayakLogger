
#ifdef UNIT_TEST
#include "Arduino.h"
#endif

#ifdef UNIT_TEST
#include "FakeSoftwareSerial.h"
#include "FakeTinyGPS.h"
#else
#include "TinyGPS++.h"
#endif
#include "fstream_headers.h"
#ifdef ESP8266
using namespace std;
#endif
#include "Logger.h"
#include "GpsReport.h"
#include "ElementQueue.h"
#include "PreCompilerOptions.h"

void GpsReport::readGps()
{
  while (Serial.available())
  {
      gps.encode(Serial.read());
  }
}
bool GpsReport::write(Logger& logger)
{
  bool gpsStatus = true;
  readGps();
  float latitude, longitude;
#if 0
  HDOP = gps.hdop(); //, TinyGPS::GPS_INVALID_HDOP
  if (HDOP > HDOP_UNRELIABLE)
  {
    gpsStatus = false;
  }
#endif

#ifdef RUNTIME_SERIAL_ON
  Serial.println(HDOP);
#endif
  Element* hdopElement = new LogElement<unsigned long>("HDOP", HDOP);
  latitude = gps.location.lat();
  longitude = gps.location.lng();
  speed = gps.speed.kmph();
  Element* latitudeElement = new LogElement<float>("Lat", latitude);
  Element* longitudeElement = new LogElement<float>("Lon", longitude);
  Element* yearElement = new LogElement<int>("Y", gps.date.year());
  Element* monthElement = new LogElement<int>("Mo", gps.date.month());
  Element* dayElement = new LogElement<int>("D", gps.date.day());
  Element* hourElement = new LogElement<int>("H", gps.time.hour());
  Element* minuteElement = new LogElement<int>("Mi", gps.time.minute());
  Element* secondElement = new LogElement<int>("S", gps.time.second());
  Element* speedElement = new LogElement<float>("Spe", speed);
  ElementQueue queue;
  queue.push(speedElement);
  queue.push(secondElement);
  queue.push(minuteElement);
  queue.push(hourElement);
  queue.push(dayElement);
  queue.push(monthElement);
  queue.push(yearElement);
  queue.push(longitudeElement);
  queue.push(latitudeElement);
  queue.push(hdopElement);
  bool const logStatus = logger.myLogEvent(queue);
  return (logStatus and gpsStatus);
}
SpeedMessage GpsReport::speedMessage() const
{
    SpeedMessage msg;
    //msg.header = "Speed: ";
    msg.value = speed;
    return msg;
}
