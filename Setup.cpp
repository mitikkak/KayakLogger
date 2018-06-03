
#include "Setup.h"
#ifdef ESP8266
using namespace std;
#endif
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
#ifdef ACCELEROMETER_ON
  accMeter.setRange(ADXL345::RANGE_4G);
#endif
  statusIndicator.init();
  prevTimeTiltHandled = millis();
  prevTimeGpsHandled = millis();
#ifdef IIC_LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Kayaklogger");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
#else
  lcd.begin(20, 2);
#endif
  logger.initSdCard(lcd);
  delay(100);
  for (unsigned int i = 0; i < Logger::MAX_FILE_AMOUNT; i++)
  {
     Logger::FileStatus const status = logger.reserveFile(i);
     if (status == Logger::FileStatus::ok)
     {
        lcd.print("File: ");
        lcd.print(logger.filename());
        delay(3000);
        break;
     }
  }
  // initialize the pushbutton pin as an input:
  pinMode(HALL_SWITCH, INPUT);
  //attachInterrupt(0, hallSwitch_ISR, CHANGE);
  lcd.clear();
  lcd.setCursor(0,0);
}
