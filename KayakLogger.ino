#include <Wire.h>
#include <ADXL345.h>
#include <SdFat.h>
#include <SoftwareSerial.h>

#include <TinyGPS.h>

#define GPS_ON
#define ACCELEROMETER_ON
//#define RUNTIME_SERIAL_ON

#define TILT_MEASUREMENT_PERIOD 20
#define GPS_MEASUREMENT_PERIOD 2000
#define HDOP_UNRELIABLE 900

#include "ElementQueue.h"

#include "StatusIndicator.h"

#include "Logger.h"

#ifdef ACCELEROMETER_ON
ADXL345 acc;
#endif


const float alpha = 0.5;

double fXg = 0;
double fYg = 0;
double fZg = 0;

Logger logger(10);
StatusIndicator statusIndicator(5);
#ifdef GPS_ON
TinyGPS gps;
SoftwareSerial ss(4, 3);
#endif
unsigned long prevTimeTiltHandled, prevTimeGpsHandled;
void setup()
{
  #ifdef ACCELEROMETER_ON
  acc.begin();
  #endif
  Serial.begin(115200);
  #ifdef GPS_ON
  ss.begin(9600);
  #endif
  logger.initSdCard();
  delay(100);
  acc.setRange(ADXL345::RANGE_4G);
  statusIndicator.init();
  prevTimeTiltHandled = millis();
  prevTimeGpsHandled = millis();
}

StatusIndicator::Status writeTiltReport();
StatusIndicator::Status writeGpsReport();
void readGps();
void loop()
{
  unsigned long timeNow = millis();
  if (timeNow - prevTimeTiltHandled > TILT_MEASUREMENT_PERIOD)
  {
    StatusIndicator::Status const reportStatus = writeTiltReport();
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeTiltHandled = timeNow;
  }
#ifdef GPS_ON
  if (timeNow - prevTimeGpsHandled > GPS_MEASUREMENT_PERIOD)
  {
    StatusIndicator::Status const reportStatus = writeGpsReport();
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeGpsHandled = timeNow;
  }
  else
  {
    readGps();
  }
#endif
  statusIndicator.continueCurrentState(timeNow);
}

StatusIndicator::Status writeTiltReport()
{
  double pitch, roll, Xg, Yg, Zg = 0;
  #ifdef ACCELEROMETER_ON
  double xAcc, yAcc, zAcc = 0;
  acc.read(&Xg, &Yg, &Zg, xAcc, yAcc, zAcc);
  #endif
  //Low Pass Filter
  fXg = Xg * alpha + (fXg * (1.0 - alpha));
  fYg = Yg * alpha + (fYg * (1.0 - alpha));
  fZg = Zg * alpha + (fZg * (1.0 - alpha));
  //Roll & Pitch Equations
  roll  = (atan2(-fYg, fZg)*180.0)/M_PI;
  pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/M_PI;
#ifdef RUNTIME_SERIAL_ON
  Serial.print(pitch);
  Serial.print(":");
  Serial.println(roll);
#endif
  const unsigned long milliSecs = millis();
  LogElement<unsigned long> millisElement("millis", milliSecs);
  LogElement<double> rollElement("roll", roll);
  LogElement<double> pitchElement("pitch", pitch);
  LogElement<double> xElement("x", xAcc);
  LogElement<double> yElement("y", yAcc);
  LogElement<double> zElement("z", zAcc);
  ElementQueue queue;
  queue.push(&zElement);
  queue.push(&yElement);
  queue.push(&xElement);
  queue.push(&rollElement);
  queue.push(&pitchElement);
  queue.push(&millisElement);
  return logger.myLogEvent(queue);
}

#ifdef GPS_ON
StatusIndicator::Status writeGpsReport()
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
  LogElement<float> courseElement("C", gps.f_course());
  ElementQueue queue;
  queue.push(&courseElement);
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
void readGps()
{
  while (ss.available())
  {
      gps.encode(ss.read());
  }
}
#endif


