
#include "StatusIndicator.h"
#include "fstream_headers.h"
#ifdef ESP8266
using namespace std;
#endif
#include "Logger.h"
#include "Distance.h"
#include "PreCompilerOptions.h"

static const unsigned int GPS_MEASUREMENT_PERIOD_SECONDS = GPS_MEASUREMENT_PERIOD/1000;
static const float GPS_MEASUREMENT_PERIOD_HOURS = static_cast<float>(GPS_MEASUREMENT_PERIOD_SECONDS)/3600;

void Distance::add(const float& speed)
{
    v += (speed*(GPS_MEASUREMENT_PERIOD_HOURS));
}
StatusIndicator::Status Distance::write(Logger& logger) const
{
    Element* elem = new LogElement<float>("DIST", v);
    ElementQueue queue;
    queue.push(elem);
    return logger.myLogEvent(queue);
}



