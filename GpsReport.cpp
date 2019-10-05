
#ifdef UNIT_TEST
#include "Arduino.h"
#endif

#ifdef UNIT_TEST
#include "FakeSoftwareSerial.h"
#include "FakeTinyGPS.h"
#else
#include "TinyGPS.h"
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
  HDOP = gps.hdop(); //, TinyGPS::GPS_INVALID_HDOP
  if (HDOP > HDOP_UNRELIABLE)
  {
    gpsStatus = false;
  }
#ifdef RUNTIME_SERIAL_ON
  Serial.println(HDOP);
#endif
  Element* hdopElement = new LogElement<unsigned long>("HDOP", HDOP);
  gps.f_get_position(&latitude, &longitude, 0);
  Element* latitudeElement = new LogElement<float>("Lat", latitude);
  Element* longitudeElement = new LogElement<float>("Lon", longitude);
  int year;
  byte month, day;
  gps.crack_datetime(&year, &month, &day, &hour_, &minute_, &second_, 0,0);
  speed = gps.f_speed_kmph();
  Element* yearElement = new LogElement<int>("Y", year);
  Element* monthElement = new LogElement<int>("Mo", month);
  Element* dayElement = new LogElement<int>("D", day);
  Element* hourElement = new LogElement<int>("H", hour_);
  Element* minuteElement = new LogElement<int>("Mi", minute_);
  Element* secondElement = new LogElement<int>("S", second_);
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
