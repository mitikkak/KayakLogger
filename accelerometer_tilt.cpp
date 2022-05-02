
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#ifdef ADXL345
#include <SparkFun_ADXL345.h>
#else
#include <SparkFunMPU9250-DMP.h>
#endif
#include "WiFi.h"
#include "AsyncUDP.h"
#include "ArduinoOTA.h"
#include "PaddleImuReport.h"

AsyncUDP udp;

#define LCD

#ifdef LCD
//#define RELEASE_BOARD
#if defined RELEASE_BOARD
const uint8_t CLK = 14;
const uint8_t DIN = 27;
const uint8_t DC = 26;
const uint8_t CE = 25;
const uint8_t RESET = 33;
#else
const uint8_t CLK = 25;
const uint8_t DIN = 26;
const uint8_t DC = 27;
const uint8_t CE = 14;
const uint8_t RESET = 12;
#endif
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RESET);
#endif

#ifdef ADXL345
ADXL345 acc;
void initAdxl345()
{
	  acc.powerOn();                     // Power on the ADXL345

	  acc.setRangeSetting(4);           // Give the range settings
	                                      // Accepted values are 2g, 4g, 8g or 16g
	                                      // Higher Values = Wider Measurement Range
	                                      // Lower Values = Greater Sensitivity
}
#else
MPU9250_DMP imu;
void initMpu9250()
{
	if (imu.begin() != INV_SUCCESS)
	{
#ifdef LCD
		display.setCursor(0, 20);
		display.print("imu failure");
		display.display();
#endif
		delay(5000);
		return;
	}
	imu.setSensors(INV_XYZ_ACCEL);
	imu.setAccelFSR(4);
}
#endif

const char* const ota_ssid = "paddle_imu_ap";
const char* const ota_password = "";
const char* const ssid = "kayak_logger_ap";
const char* const password = "";
bool startWiFi(uint32_t tryAttempts = 0xFFFFFFFF)
{
	uint32_t attempts{0};
    Serial.begin(115200);
    Serial.println("client begins");
    delay(1000);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        delay(1000);
        if (++attempts == tryAttempts)
        {
        	WiFi.disconnect();
        	return false;
        }
    }
    Serial.printf("Connected to: ");
    Serial.println(WiFi.SSID());
    Serial.printf("IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

bool configured{false};
bool configRequested{false};
PaddleImuReport paddleImuReport;

void packetReceive(AsyncUDPPacket packet)
{
	//Serial.println("TODO: server sent something...");
#if 1
	Serial.print("UDP Packet Type: ");
	Serial.print(
			packet.isBroadcast() ? "Broadcast" :
			packet.isMulticast() ? "Multicast" : "Unicast");
//	Serial.print(", From: ");
//	Serial.print(packet.remoteIP());
//	Serial.print(":");
//	Serial.print(packet.remotePort());
//	Serial.print(", To: ");
//	Serial.print(packet.localIP());
//	Serial.print(":");
//	Serial.print(packet.localPort());
//	Serial.print(", Length: ");
//	Serial.print(packet.length());
	const int8_t* data = reinterpret_cast<int8_t*>(packet.data());
	Tilt leftCatch(data[0], data[1], data[2], data[3]);
	Tilt leftStroke;
	Tilt leftExit;
	Tilt rightCatch(data[4], data[5], data[6], data[7]);
	Tilt rightStroke;
	Tilt rightExit;
	paddleImuReport.setLimits(leftCatch, leftStroke, leftExit, rightCatch, rightStroke, rightExit);

	Serial.print("Left catch: ");
	Serial.print(leftCatch.pitch);
	Serial.print(",");
	Serial.print(leftCatch.roll);
	Serial.print(",");
	Serial.print(leftCatch.limitPitch);
	Serial.print(",");
	Serial.print(leftCatch.limitRoll);
	Serial.println();

	Serial.print("Right catch: ");
	Serial.print(rightCatch.pitch);
	Serial.print(",");
	Serial.print(rightCatch.roll);
	Serial.print(",");
	Serial.print(rightCatch.limitPitch);
	Serial.print(",");
	Serial.print(rightCatch.limitRoll);
	Serial.println();
#endif
	configured = true;
}
void udpConnect()
{
    if(udp.connect(IPAddress(192,168,4,1), 1234)) {
        Serial.println("UDP connected");
        udp.onPacket(&packetReceive);
    }
}
void createWifiAp()
{
    WiFi.softAP(ota_ssid, ota_password);
}
void destroyWifiAp()
{

}
void waitForOtaFlash()
{
    bool otaStarted{false};
    ArduinoOTA.onStart([&otaStarted]() {otaStarted = true;});
    ArduinoOTA.onEnd([]() {});
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
    {
        const unsigned int percentage = (progress / (total / 100));
        Serial.println(percentage);
    });
    ArduinoOTA.onError([](ota_error_t error) {});
    ArduinoOTA.begin();
    unsigned long const startTime = millis();
    unsigned long deltaTime{0};
    do
    {
        deltaTime = (millis() - startTime) / 1000;
        delay(100);
        ArduinoOTA.handle();
    }
    while(deltaTime < 60 and not otaStarted);
#ifndef ESP8266
    ArduinoOTA.end();
#endif
}
void serveOtaFlashPeriod()
{
    createWifiAp();
    waitForOtaFlash();
    destroyWifiAp();
}
void setup()
{
  Serial.begin(115200);
#ifdef LCD
  display.begin();
  display.setContrast(58);
  display.clearDisplay();

  display.setTextSize(1);
  display.setRotation(2);
  display.setCursor(0,0); display.print("accelerometer_tilt begins"); display.display();
#endif
  delay(3000);
  bool const wifiConnected = startWiFi(3);
  if (not wifiConnected)
  {
	  serveOtaFlashPeriod();
	  startWiFi();
  }
  udpConnect();

#ifdef ADXL345
  initAdxl345();
#else
  initMpu9250();
#endif

#ifdef LCD
  display.setCursor(0,20); display.print("imu begin done"); display.display();
#endif
  delay(1000);
}

typedef unsigned long TIME;

double fXg, fYg, fZg;
TiltValues getTiltValues()
{
   TiltValues values;
   double pitch, roll = 0;
   int Xg, Yg, Zg = 0;
#ifdef ADXL345
   acc.readAccel(&Xg, &Yg, &Zg);
#else
	if ( imu.dataReady() )
	{
	    // Use dmpUpdateFifo to update the ax, gx, mx, etc. values
		imu.update(UPDATE_ACCEL);
	}
	Xg = imu.ax;
	Yg = imu.ay;
	Zg = imu.az;
#endif
	//Low Pass Filter
	const float alpha = 0.5;
	fXg = Xg * alpha + (fXg * (1.0 - alpha));
	fYg = Yg * alpha + (fYg * (1.0 - alpha));
	fZg = Zg * alpha + (fZg * (1.0 - alpha));
	//Roll & Pitch Equations
	values.roll = (atan2(-fYg, fZg) * 180.0) / M_PI;
	values.pitch = (atan2(fXg, sqrt(fYg * fYg + fZg * fZg)) * 180.0) / M_PI;
	return values;
}

TIME const timeLogThreshold = 200;
TIME timePrevLog = 0;
void printTilt(const TiltValues& tilt)
{
#ifdef LCD
	TIME const timeNow = millis();
	if (timeNow - timePrevLog > timeLogThreshold)
	{
		display.clearDisplay();
		display.display();
        int textSize = 2;
        display.setTextSize(textSize);
        display.setCursor(0, 0);
        display.print(tilt.pitch);
        display.setCursor(0, 1*8*textSize);
        display.print(tilt.roll);
//        display.setCursor(0, 2*8*textSize);
//        display.print(sn);
//        display.setCursor(0, 2*8*textSize);
//        display.print(tilt.yaw);
        display.display();
		timePrevLog = timeNow;
	}
#endif
}

int toInteger(const float val)
{
    return static_cast<int>(std::ceil(val));
}
unsigned long sn{0};
const String separator(";");
void parseTiltMessage(String& msg, const TiltValues&  tilt)
{

    msg += millis();
    msg += String(separator);
    msg += String(sn++);
    msg += String(separator);
    msg += String(toInteger(tilt.pitch));
    msg += String(separator);
    msg += String(toInteger(tilt.roll));
    msg += String(separator);
    msg += String(toInteger(tilt.yaw));
    msg += String(separator);
}
void sendTiltMessage(const TiltValues& tilt)
{
    String msg{};
    parseTiltMessage(msg, tilt);
    udp.print(msg);
}
void sendTiltMessage2(String& msg, const PaddleImuReport& paddleImuReport)
{
	msg += String(static_cast<int>(paddleImuReport.getPosition()));
	msg += String(separator);
	msg += String(paddleImuReport.getStats().strokesLeft);
	msg += String(separator);
	msg += String(paddleImuReport.getStats().strokesRight);
	msg += String(separator);
	msg += String(paddleImuReport.getStats().leftDeltaTime);
	msg += String(separator);
	msg += String(paddleImuReport.getStats().rightDeltaTime);
	msg += String(separator);
    udp.print(msg);
}

TIME prevTimeSent{0};
const TIME measInterval{50};
const TIME configInterval{5000};
Position prevPosition = Position::unknown;
int numOfMsgs{0};
void loop()
{
	TIME const timeNow = millis();
	if (not configured and (timeNow >= prevTimeSent + configInterval))
	{
		sn = 0;
		String msg{};
		parseTiltMessage(msg, getTiltValues());
		sendTiltMessage2(msg, paddleImuReport);
		prevTimeSent = timeNow;
#ifdef LCD
		display.clearDisplay();
		display.print("conf: ");
		display.print(timeNow);
		display.display();
#endif

	}
#if 0
	else if (configured and (timeNow >= prevTimeSent + measInterval))
	{
		TiltValues const tilt = getTiltValues();
		sendTiltMessage(tilt);
		printTilt(tilt);
		prevTimeSent = timeNow;
	}
#else
	else if (configured)
	{
		TiltValues const tilt = getTiltValues();
	    String msg{};
		paddleImuReport.push(tilt);
		//paddleImuReport.decodeAngularPosition();
		//paddleImuReport.calculateTimeOnSide();
		paddleImuReport.updatePosition();
		//if (paddleImuReport.timeToSend())
		if (prevPosition != paddleImuReport.getPosition())
		{
			numOfMsgs++;
#ifdef LCD
			display.clearDisplay();
			display.print(paddleImuReport.getPositionStr());
			display.setCursor(0, 8);
			display.print(paddleImuReport.getStats().strokesLeft);
			display.setCursor(0, 16);
			display.print(paddleImuReport.getStats().strokesRight);
			display.setCursor(0, 24);
			display.print(paddleImuReport.getStats().leftDeltaTime);
			display.setCursor(0, 32);
			display.print(paddleImuReport.getStats().rightDeltaTime);
			display.display();
#endif
			prevPosition = paddleImuReport.getPosition();
			parseTiltMessage(msg, tilt);
			sendTiltMessage2(msg, paddleImuReport);
		}
	}
#endif
}
