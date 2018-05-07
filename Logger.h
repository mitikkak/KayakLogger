
#ifndef _LOGGER_H
#define _LOGGER_H

#include "StatusIndicator.h"
#include "ElementQueue.h"
#ifdef ESP8266
typedef struct SDClass SD_TYPE;
#else
typedef struct SdFat SD_TYPE;
#endif

class LiquidCrystal_I2C;
class Logger
{
  public:
  Logger(SD_TYPE& s, int const pin):sd(s), sdCardChipSelect(pin) {}
  SD_TYPE& sd;
  const int sdCardChipSelect;
  void initSdCard(LiquidCrystal_I2C& lcd);
  virtual StatusIndicator::Status myLogEvent(ElementQueue& queue);
};

#endif
