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
    lcd.print("Card failed, or not present");
    delay(5000);
}
Logger::FileStatus Logger::reserveFile(unsigned int logNumber)
{
  FileStatus retValue = FileStatus::ok;
  char candidate[MAX_SIZE]{};
  strcat(candidate, prefix);
  char itoa_buffer[5]{};
  const char* const number_cstr = itoa(logNumber, itoa_buffer, DEC);
  strcat(candidate, number_cstr);
  strcat(candidate, postfix);
  if (sd.exists(candidate))
  {
    retValue = FileStatus::alreadyTaken;
  }
  else
  {
    strcat(fileName, candidate);
  }
  return retValue;
}

#if defined ESP8266 || defined ESP32
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
    //Serial.println(dataString);
    // create dir if needed
    if (!sd.mkdir("/LOGS"))
    {
        //Serial.printf("mkdir failed \n\r");
      return false;
    }
    File dataFile = sd.open(fileName,
#if defined ESP8266
            FILE_WRITE
#else
            FILE_APPEND
#endif
            );

    // if the file is available, write to it:
    if (!dataFile) {
        //Serial.printf("open failed \n\r");
        return false;
    }
    dataFile.println(dataString);
    dataFile.close();

  return true;
}
#else
StatusIndicator::Status Logger::myLogEvent(ElementQueue& queue)
{
  // create dir if needed
  if (!sd.mkdir("LOGS/"))
  {
      // TODO: returning here causes memory leak of queue elements
 //      return StatusIndicator::Status_mkDirFailed;
  }
  // create or open a file for append
  ofstream sdlog(fileName, ios::out | ios::app);
  bool somethingWasWritten = false;

  sdlog.precision(6);
  // append a line to the file

  while (queue.peek())
  {
    Element* element = queue.pop();
    if (element)
    {
      somethingWasWritten = true;
      sdlog << element->msg << ": ";
      element->outputValue(sdlog);
      sdlog << " ; ";
      delete element;
    }
  }


  if (somethingWasWritten)
  {
    sdlog << endl;
  }
  // check for errors
  if (!sdlog) /**/
  {
    return StatusIndicator::Status_sdAppendFailed;
  }
  // file will be closed when sdlog goes out of scope
  return StatusIndicator::Status_ok;
}
#endif
