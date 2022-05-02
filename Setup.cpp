
#include "Setup.h"
#ifdef ESP8266
using namespace std;
#endif
#include "Components.h"
#include "Arduino.h"

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
        gps.readSerial();
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
void createWifiAp()
{
    lcd.clear();
    lcd.smallText();
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    delay(3000);
    lcd.print("AP: ");
    lcd.row(1);
    lcd.print(ssid);
}

void createMdns()
{
    lcd.row(3);
    lcd.print("domain:");
    lcd.row(4);
    if (!MDNS.begin(mdnsHost))
    {
        lcd.print("failed!");
    }
    else
    {
        lcd.print(String(mdnsHost) + String(".local"));
    }
    delay(3000);
}

Tilt leftCatch{-50,-80, 15, 20};
Tilt leftStroke{-35,-75, 5, 0};
Tilt leftExit{}; //{-50,-10, 10};
Tilt rightCatch{-20, 60, 30, 30};//{-25, 40, 15, 20}; //{-30,45, 10};
Tilt rightStroke{-20, 50, 0, 10}; //{-20,20, 20};
Tilt rightExit{}; //{-10,10, 10};

void packetReceive(AsyncUDPPacket packet)
{
	//Serial.printf("udpPacketReceiver[%llu] %u \n\r", millis(), numOfMsgs);
	paddleImuReport.push(String((const char*) packet.data()));
	paddleImuReport.write(/*logger*/);
	paddleImuReport.decodeAngularPosition();
	if (0 == paddleImuReport.sn())
	{
//		lcd.clear();
//		lcd.print("sending ctrl");
//		delay(3000);
		int8_t msg[] = {leftCatch.pitch,
						leftCatch.roll,
						leftCatch.limitPitch,
						leftCatch.limitRoll,
						rightCatch.pitch,
						rightCatch.roll,
						rightCatch.limitPitch,
						rightCatch.limitRoll
				 };
		udp.writeTo(reinterpret_cast<const uint8_t*>(msg), sizeof(msg),
				packet.remoteIP(), packet.remotePort());
	}
	else
	{
		//paddleImuReport.calculateTimeOnSide();
		//paddleImuReport.updatePosition();
		numOfMsgs++;
	}
}
void createPaddleImuListener()
{
	paddleImuReport.setLimits(leftCatch, leftStroke, leftExit, rightCatch, rightStroke, rightExit);
    if(udp.listen(1234))
    {
        lcd.print("PaddleImu listener created");
        //lcd.print(String(WiFi.localIP()));
        udp.onPacket(&packetReceive);
    }
}
// const int contrast{60}; // ESP8266 dev unit
const int contrast{50}; // ESP32 finished unit

void setup()
{
  Serial.begin(9600);
  gps.baudrateTo115200();
  //gps.periodTo5000ms();
  gps.periodTo100ms();

  lcd.begin(contrast);
  lcd.upsideDown();
  lcd.print("Kayaklogger");
  lcd.row(1);
  delay(1000);
  createWifiAp();
  createMdns();
  delay(1000);
  //logger.initSdCard(lcd);
  delay(100);
  server.create();
  server.waitUntilConnectionServed();
  server.destroy();
  createPaddleImuListener();
  delay(3000);
  //waitUntilGpsFix();
  //logger.reserveFile(); // After 3d fix we supposedly have proper date and time
  //gps.setMinimumNmeaSentences();
  lcd.clear();
  lcd.bigText();
}
