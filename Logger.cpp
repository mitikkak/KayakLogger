#include <Arduino.h>
#ifdef UNIT_TEST
#include "FakeSdFat.h"
#include <fstream>
using namespace std;
#else
 #ifdef ESP8266
  #include "SD.h"
 #else
  #include "SdFat.h"
 #endif
#endif
#ifdef ESP8266
using namespace std;
#endif
#include "Logger.h"

void Logger::initSdCard()
{
#ifdef RUNTIME_SERIAL_ON
Serial.print("Initializing SD card...");
#endif
// see if the card is present and can be initialized:
pinMode(sdCardChipSelect, OUTPUT);
digitalWrite(sdCardChipSelect, HIGH);

if (!sd.begin(sdCardChipSelect)) {
#ifdef RUNTIME_SERIAL_ON
  Serial.println("Card failed, or not present");
#endif
  // don't do anything more:
  return;
}
#ifdef RUNTIME_SERIAL_ON
Serial.println("card initialized.");
#endif
digitalWrite(sdCardChipSelect, HIGH);
}

StatusIndicator::Status Logger::myLogEvent(ElementQueue& queue)
{
  // create dir if needed
  if (!sd.mkdir("LOGS/"))
  {
    //return StatusIndicator::Status_mkDirFailed;
  }
#ifndef ESP8266_BUILD_ERRORS
  // create or open a file for append
  ofstream sdlog("LOGS/datalog.txt", ios::out | ios::app);
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
#endif
  // file will be closed when sdlog goes out of scope
  return StatusIndicator::Status_ok;
}
