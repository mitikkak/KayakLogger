
#include "StatusIndicator.h"
#include "fstream_headers.h"
#ifdef ESP8266
using namespace std;
#endif
#include "Logger.h"
#include "AverageSpeed.h"
#include "PreCompilerOptions.h"

void AverageSpeed::add(const float& speed)
{
    samples++;
    total+=speed;
}
float AverageSpeed::value() const
{
    if(samples)
    {
        return total / samples;
    }
    return 0;
}
StatusIndicator::Status AverageSpeed::write(Logger& logger) const
{
    Element* totalElement = new LogElement<float>("AS_TOTAL", total);
    Element* samplesElement = new LogElement<unsigned int>("AS_SAMPLES", samples);
    Element* resultElement = new LogElement<float>("AS_RES", value());
    ElementQueue queue;
    queue.push(totalElement);
    queue.push(samplesElement);
    queue.push(resultElement);
    return logger.myLogEvent(queue);
}
