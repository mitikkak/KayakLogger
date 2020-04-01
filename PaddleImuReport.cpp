
#include "PaddleImuReport.h"

PaddleImuReport::PaddleImuReport()
: message{}
{
}
void PaddleImuReport::init()
{
    message = "";
}
void PaddleImuReport::push(const String& s)
{
    message += s;
}
void PaddleImuReport::write(Logger& logger)
{
    message += "\n";
    logger.logMessage(message);
    init();
}
