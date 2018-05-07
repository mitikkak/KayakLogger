
#include <SPI.h>
#include <SD.h>
#include "Logger.h"
#include "LiquidCrystal_I2C.h"

void Logger::initSdCard(LiquidCrystal_I2C& lcd)
{
  if (!SD.begin(sdCardChipSelect)) {
    lcd.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
}
static const char* const fileName = "LOGS/datalog.txt";
StatusIndicator::Status Logger::myLogEvent(ElementQueue& queue)
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
        element->outputValue(dataString);
        dataString += " ; ";
        delete element;
      }
    }

    if (somethingWasWritten)
    {
      dataString += "\n";
    }
    Serial.println(dataString);
    // create dir if needed
    if (!SD.mkdir("LOGS/"))
    {
      return StatusIndicator::Status_mkDirFailed;
    }
    File dataFile = SD.open(fileName, FILE_WRITE);

    // if the file is available, write to it:
    if (!dataFile) {
        return StatusIndicator::Status_sdAppendFailed;
    }
    dataFile.println(dataString);
    dataFile.close();
  return StatusIndicator::Status_ok;
}
