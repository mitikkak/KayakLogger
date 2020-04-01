
#pragma once
#include "Arduino.h"
#include "Logger.h"

class PaddleImuReport
{
public:
    PaddleImuReport();
    void push(const String& s);
    void write(Logger& logger);
private:
    void init();
    String message;
};
