
#include "StatusIndicator.h"
#include "ElementQueue.h"
struct SdFat;
class Logger
{
  public:
  Logger(SdFat& s, int const pin):sd(s), sdCardChipSelect(pin) {}
  SdFat& sd;
  const int sdCardChipSelect;
  void initSdCard();
  StatusIndicator::Status myLogEvent(ElementQueue& queue);
};
