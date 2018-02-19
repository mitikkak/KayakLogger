
#ifndef _LOGGER_H
#define _LOGGER_H

#include "StatusIndicator.h"
#include "ElementQueue.h"
#ifdef ESP8266
typedef struct SDClass SD_TYPE;
#else
typedef struct SdFat SD_TYPE;
#endif

class Logger
{
  public:
  Logger(SD_TYPE& s, int const pin):sd(s), sdCardChipSelect(pin) {}
  SD_TYPE& sd;
  const int sdCardChipSelect;
  void initSdCard();
  virtual StatusIndicator::Status myLogEvent(ElementQueue& queue);
};

#endif
