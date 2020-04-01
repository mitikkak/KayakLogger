
#ifndef _LOGGER_H
#define _LOGGER_H

#include "ElementQueue.h"
#if defined ESP8266
typedef struct SDClass SD_TYPE;
#elif defined ESP32
typedef struct fs::SDFS SD_TYPE;
#else
typedef struct SdFat SD_TYPE;
#endif

class LcdIf;
class Logger
{
public:
  static constexpr unsigned int MAX_FILE_AMOUNT=5000;
  typedef enum
  {
    alreadyTaken = 0,
    ok = 1
  } FileStatus;
  Logger(SD_TYPE& s, int const pin):sd(s), sdCardChipSelect(pin), fileName() {}
  SD_TYPE& sd;
  const int sdCardChipSelect;
  void initSdCard(LcdIf& lcd);
  virtual bool myLogEvent(ElementQueue& queue);
  bool logMessage(const String& s) const;
  FileStatus reserveFile(unsigned int logNumber);
  const char* filename() const { return fileName; }
private:
  void showInitError(LcdIf& lcd) const;
  static constexpr unsigned int MAX_SIZE=30;
  char fileName[MAX_SIZE];
  const char* const prefix = "/LOGS/DATALOG";
  const char* const postfix = ".TXT";
};

#endif
