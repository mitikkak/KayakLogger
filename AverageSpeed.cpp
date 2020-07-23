
#include "fstream_headers.h"
#ifdef ESP8266
using namespace std;
#endif
#include "Logger.h"
#include "AverageSpeed.h"
#include "PreCompilerOptions.h"

void AverageSpeed::add(const double& speed)
{
    samples++;
    total+=speed;
}
double AverageSpeed::value() const
{
    if(samples)
    {
        return total / samples;
    }
    return 0;
}
bool AverageSpeed::write(Logger& logger) const
{
    Element* totalElement = new LogElement<double>("AS_TOTAL", total, 3);
    Element* samplesElement = new LogElement<unsigned int>("AS_SAMPLES", samples);
    Element* resultElement = new LogElement<double>("AS_RES", value(), 3);
    ElementQueue queue;
    queue.push(totalElement);
    queue.push(samplesElement);
    queue.push(resultElement);
    return logger.myLogEvent(queue);
}
