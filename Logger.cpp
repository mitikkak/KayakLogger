#include <Arduino.h>
#ifdef UNIT_TEST
#include "FakeSdFat.h"
using namespace std;
#else
 #if defined ESP8266 || defined ESP32
  #include "SD.h"
 #else
  #include "SdFat.h"
 #endif
#endif
#if defined ESP8266 || defined ESP32
using namespace std;
#endif
#include "Components.h"

#ifdef ESP8266
void Logger::initSdCard(LcdIf& lcd)
{
#ifdef RUNTIME_SERIAL_ON
Serial.print("Initializing SD card...");
#endif
// see if the card is present and can be initialized:
pinMode(sdCardChipSelect, OUTPUT);
digitalWrite(sdCardChipSelect, HIGH);

if (!sd.begin(sdCardChipSelect)) {
    showInitError(lcd);
  // don't do anything more:
  return;
}
#ifdef RUNTIME_SERIAL_ON
Serial.println("card initialized.");
#endif
digitalWrite(sdCardChipSelect, HIGH);
}
#else // ESP32
void Logger::initSdCard(LcdIf& lcd)
{
    if (!SD.begin())
    {
        showInitError(lcd);
    }
}
#endif
void Logger::showInitError(LcdIf& lcd) const
{
    lcd.clear();
    lcd.print("Card failed, or not present");
    delay(5000);
}
void Logger::reserveFile()
{
    bool reserved{false};
    int cnt{0};
    while(not reserved)
    {
        lcd.clear();
        lcd.smallText();
        lcd.print("Get filename ");
        lcd.print(String(cnt++));
        gps.readSerial();
        lcd.row(1);
        bool const fixIs3d = gps.gsa.fixIs3d();
        bool const dateInRange = gps.date.inRange();
        bool const timeInRange = gps.time.inRange();
        lcd.print(String(fixIs3d));
        lcd.separator();
        lcd.print(String(dateInRange));
        lcd.separator();
        lcd.print(String(timeInRange));
        if (fixIs3d and dateInRange and timeInRange)
        {
            const int bufferSize{5};
            char itoa_buffer[bufferSize]{};
            strcat(fileName, prefix);
            int length{strlen(prefix)};
            const char* const year_cstr = itoa(gps.date.year(), itoa_buffer, DEC);
            const int yearLength = strlen(year_cstr);
            memcpy(&fileName[length], year_cstr, yearLength);
            length += yearLength;
            fileName[length++] = '_';
            memset(itoa_buffer, 0, bufferSize);
            const char* const month_cstr = itoa(gps.date.month(), itoa_buffer, DEC);
            const int monthLength = strlen(month_cstr);
            memcpy(&fileName[length], month_cstr, monthLength);
            length += monthLength;
            fileName[length++] = '_';
            memset(itoa_buffer, 0, bufferSize);
            const char* const day_cstr = itoa(gps.date.day(), itoa_buffer, DEC);
            const int dayLength = strlen(day_cstr);
            memcpy(&fileName[length], day_cstr, dayLength);
            length += dayLength;
            fileName[length++] = '_';
            memset(itoa_buffer, 0, bufferSize);
            const char* const hour_cstr = itoa(gps.time.hour(), itoa_buffer, DEC);
            const int hourLength = strlen(hour_cstr);
            memcpy(&fileName[length], hour_cstr, hourLength);
            length += hourLength;
            fileName[length++] = '_';
            memset(itoa_buffer, 0, bufferSize);
            const char* const minute_cstr = itoa(gps.time.minute(), itoa_buffer, DEC);
            const int minuteLength = strlen(minute_cstr);
            memcpy(&fileName[length], minute_cstr, minuteLength);
            length += minuteLength;
            memset(itoa_buffer, 0, bufferSize);
            strcat(fileName, postfix);
            lcd.row(2);
            lcd.print(fileName);
            reserved = true;
        }
        delay(2000);
    }
}

bool Logger::logMessage(const String& message) const
{
//    if (!sd.mkdir("/LOGS"))
//    {
//        //Serial.printf("mkdir failed \n\r");
//      return false;
//    }
    File dataFile = sd.open(fileName,
#if defined ESP8266
            FILE_WRITE
#else
            FILE_APPEND
#endif
            );

    // if the file is available, write to it:
    if (!dataFile) {
        lcd.clear();
        lcd.smallText();
        lcd.print("sd write failed");
        delay(1000);
        return false;
    }
    dataFile.println(message);
    dataFile.close();
}
bool Logger::myLogEvent(ElementQueue& queue)
{
    String dataString = "";
    bool somethingWasWritten = false;
    while (queue.peek())
    {
      Element* element = queue.pop();
      if (element)
      {
        somethingWasWritten = true;
        dataString += element->msg;
        dataString += ": ";
        #if 1
        element->outputValue(dataString);
        #endif
        dataString += " ; ";
        delete element;
      }
    }

    if (somethingWasWritten)
    {
      dataString += "\n";
    }
    return logMessage(dataString);
}
