#include "PreCompilerOptions.h"
#include "StatusIndicator.h"
#include "fstream_headers.h"
#include "ElementQueue.h"
#include "Logger.h"
#include "ADXL345.h"
#include "TiltReport.h"

#ifdef UNIT_TEST
#include <math.h>
#include "Arduino.h"
#endif

double fXg = 0;
double fYg = 0;
double fZg = 0;
const float alpha = 0.5;

StatusIndicator::Status TiltReport::write(Logger& logger)
{
  double pitch, roll, Xg, Yg, Zg = 0;
  double xAcc, yAcc, zAcc = 0;
  #ifdef ACCELEROMETER_ON
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
  Element* millisElement = new LogElement<unsigned long> ("millis", milliSecs);
  Element* rollElement = new LogElement<double> ("roll", roll);
  Element* pitchElement = new LogElement<double>("pitch", pitch);
  Element* xElement = new LogElement<double>("x", xAcc);
  Element* yElement = new LogElement<double>("y", yAcc);
  Element* zElement = new LogElement<double>("z", zAcc);
  ElementQueue queue;
  queue.push(zElement);
  queue.push(yElement);
  queue.push(xElement);
  queue.push(rollElement);
  queue.push(pitchElement);
  queue.push(millisElement);
  return logger.myLogEvent(queue);
}
