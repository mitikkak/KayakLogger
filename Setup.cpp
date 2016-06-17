
#include "Setup.h"
#include "Components.h"
#include "Arduino.h"

void setup()
{
  #ifdef ACCELEROMETER_ON
  acc.begin();
  #endif
#ifdef RUNTIME_SERIAL_ON
  Serial.begin(115200);
#endif
  #ifdef GPS_ON
  ss.begin(9600);
  #endif
  logger.initSdCard();
  delay(100);
#ifdef ACCELEROMETER_ON
  acc.setRange(ADXL345::RANGE_4G);
#endif
  statusIndicator.init();
  prevTimeTiltHandled = millis();
  prevTimeGpsHandled = millis();
}
