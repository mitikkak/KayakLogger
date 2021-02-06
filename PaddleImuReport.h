
#pragma once
#include "Arduino.h"
#include "Logger.h"

class PaddleImuReport
{
public:
    PaddleImuReport();
    void push(const String& s);
    void write(Logger& logger);
    int sn() const { return sn_; }
    int pitch() const { return pitch_; }
    int roll() const { return roll_; }
    int yaw() const { return yaw_; }
    void decodeAngularPosition();
private:
    static const String separator;
    void init();
    String message;
    String savedMessage;
    int sn_;
    int pitch_;
    int roll_;
    int yaw_;
};
