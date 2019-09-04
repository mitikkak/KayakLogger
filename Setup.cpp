
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
  accMeter.setRange(ADXL345::RANGE_4G);
  #endif
#ifdef RUNTIME_SERIAL_ON
#error use something else here!
  Serial.begin(115200);
#endif
  #ifdef GPS_ON
  Serial.begin(9600);
  #endif
  statusIndicator.init();
  prevTimeTiltHandled = millis();
  prevTimeGpsHandled = millis();

  lcd.begin();
  lcd.setContrast(50);
  lcd.clearDisplay();
  lcd.setCursor(0,0);
  lcd.print("Kayaklogger");

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
  lcd.clearDisplay();
  lcd.setCursor(0,0);
}
