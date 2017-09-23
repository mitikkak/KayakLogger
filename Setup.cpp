
#include "Setup.h"
#include "Components.h"
#include "Arduino.h"
#include "HallSwitch.h"

void setup()
{
  #ifdef ACCELEROMETER_ON
  accMeter.begin();
  #endif
#ifdef RUNTIME_SERIAL_ON
#error use something else here!
  Serial.begin(115200);
#endif
  #ifdef GPS_ON
  Serial.begin(9600);
  #endif
  logger.initSdCard();
  delay(100);
#ifdef ACCELEROMETER_ON
  accMeter.setRange(ADXL345::RANGE_4G);
#endif
  statusIndicator.init();
  prevTimeTiltHandled = millis();
  prevTimeGpsHandled = millis();
  lcd.begin(20, 2);
  // initialize the pushbutton pin as an input:
  pinMode(HALL_SWITCH, INPUT);
  //attachInterrupt(0, hallSwitch_ISR, CHANGE);
}
