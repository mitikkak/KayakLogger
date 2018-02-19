
#include "StatusIndicator.h"
#include "fstream_headers.h"
#ifdef ESP8266
using namespace std;
#endif
#include "Logger.h"
#include "Distance.h"
#include "PreCompilerOptions.h"

static const unsigned int GPS_MEASUREMENT_PERIOD_SECONDS = GPS_MEASUREMENT_PERIOD/1000;
static const unsigned int METERS_TO_KILOMETERS = 1000;

void Distance::add(const float& speed)
{
    v += (speed*3.6*(GPS_MEASUREMENT_PERIOD_SECONDS))/METERS_TO_KILOMETERS;
}
StatusIndicator::Status Distance::write(Logger& logger) const
{
    Element* elem = new LogElement<float>("DIST", v);
    ElementQueue queue;
    queue.push(elem);
    return logger.myLogEvent(queue);
}



