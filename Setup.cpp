
#include "Setup.h"
#ifdef ESP8266
using namespace std;
#endif
#include "Components.h"
#include "Arduino.h"
#include "HallSwitch.h"

void readGps()
{
  while (Serial.available())
  {
      gps.encode(Serial.read());
  }
}

void displayGpsFixStatus()
{
    lcd.clear();
    lcd.bigText();
    lcd.row(0);
    lcd.print(String(gps.gsa.numSats()));
    lcd.separator();
    lcd.print(String(gps.gsa.fix()));
    lcd.row(1);
    const int numSats = gps.satsInView.numOf();
    lcd.print(String(numSats));
    lcd.separator();
    lcd.printer().print(gps.satsInView.numOfDb());
    lcd.row(2);
    lcd.printer().print(gps.satsInView.totalSnr());
    lcd.display();
}
void waitUntilGpsFix()
{
    bool fix{false};
    while(not fix)
    {
        readGps();
        displayGpsFixStatus();
        if (gps.gsa.fixIs3d())
        {
            lcd.row(2);
            fix = true;
        }
        delay(2000);
    }
    lcd.clear();
    lcd.row(0);
    lcd.print("gps ok");
    delay(2000);
}

// const int contrast{60}; // ESP8266 dev unit
const int contrast{50}; // ESP32 finished unit

void setup()
{
  Serial.begin(9600);
  gps.baudrateTo115200();
  gps.periodTo5000ms();

  lcd.begin(contrast);
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
  waitUntilGpsFix();
}
