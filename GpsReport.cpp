
#ifdef UNIT_TEST
#include "Arduino.h"
#endif

#ifdef UNIT_TEST
#include "FakeSoftwareSerial.h"
#include "FakeTinyGPS.h"
#else
#include "SoftwareSerial.h"
#include "TinyGPS.h"
#endif
#include "StatusIndicator.h"
#include "fstream_headers.h"
#include "Logger.h"
#include "GpsReport.h"

#include "ElementQueue.h"

#define HDOP_UNRELIABLE 900

void GpsReport::readGps()
{
  while (ss.available())
  {
      gps.encode(ss.read());
  }
}
StatusIndicator::Status GpsReport::write(Logger& logger)
{
  StatusIndicator::Status gpsStatus = StatusIndicator::Status_ok;
  readGps();
  float latitude, longitude;
  unsigned long const HDOP = gps.hdop(); //, TinyGPS::GPS_INVALID_HDOP
  if (HDOP > HDOP_UNRELIABLE)
  {
    gpsStatus = StatusIndicator::Status_hdopUnreliable;
  }
#ifdef RUNTIME_SERIAL_ON
  Serial.println(HDOP);
#endif
  LogElement<unsigned long> hdopElement("HDOP", HDOP);
  gps.f_get_position(&latitude, &longitude, 0);
  LogElement<float> latitudeElement("Lat", latitude);
  LogElement<float> longitudeElement("Lon", longitude);
  int year;
  byte month, day, hour, minute, second;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, 0,0);
  LogElement<int> yearElement("Y", year);
  LogElement<int> monthElement("Mo", month);
  LogElement<int> dayElement("D", day);
  LogElement<int> hourElement("H", hour);
  LogElement<int> minuteElement("Mi", minute);
  LogElement<int> secondElement("S", second);
  LogElement<float> speedElement("Spe", gps.f_speed_kmph());
  //LogElement<float> courseElement("C", gps.f_course());
  ElementQueue queue;
  //queue.push(&courseElement);
  queue.push(&speedElement);
  queue.push(&secondElement);
  queue.push(&minuteElement);
  queue.push(&hourElement);
  queue.push(&dayElement);
  queue.push(&monthElement);
  queue.push(&yearElement);
  queue.push(&longitudeElement);
  queue.push(&latitudeElement);
  queue.push(&hdopElement);
  StatusIndicator::Status const logStatus = logger.myLogEvent(queue);
  return (logStatus != StatusIndicator::Status_ok) ? logStatus : gpsStatus;
}
