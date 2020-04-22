
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
  #ifdef GPS_ON
  Serial.begin(9600);
  #endif
  prevTimeTiltHandled = millis();
  prevTimeGpsHandled = millis();

  lcd.begin(50);
  lcd.upsideDown();
  lcd.print("Kayaklogger");
  lcd.row(1);
  logger.initSdCard(lcd);
  delay(100);
  for (unsigned int i = 0; i < Logger::MAX_FILE_AMOUNT; i++)
  {
     Logger::FileStatus const status = logger.reserveFile(i);
     if (status == Logger::FileStatus::ok)
     {
        lcd.print("File: " + String(logger.filename()));
        delay(3000);
        break;
     }
  }
  lcd.clear();
#ifdef PADDLE_IMU
  WiFi.softAP(ssid, password);
  lcd.print("IP: ");
  lcd.print(String(WiFi.softAPIP()));
  lcd.row(1);
  if(udp.listen(1234))
  {
      lcd.print("UDP Listening on IP: ");
      lcd.print(String(WiFi.localIP()));
      udp.onPacket([](AsyncUDPPacket packet) {
          //Serial.printf("udpPacketReceiver[%llu] %u \n\r", millis(), numOfMsgs);
          paddleImuReport.push(String((const char*) packet.data()));
          paddleImuReport.write(logger);
          numOfMsgs++;
      });

  }
  delay(3000);
  lcd.clear();
  lcd.row(0);
#endif
}
