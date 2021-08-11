
#pragma once
#include "Arduino.h"
#include "Logger.h"

enum class PaddleSide
{
    center = 1,
    left = 2,
    right = 3
};

class PaddleImuReport
{
public:
    PaddleImuReport();
    void init();
    void push(const String& s);
    void write(/*Logger& logger*/);
    int sn() const { return sn_; }
    int pitch() const { return pitch_; }
    int roll() const { return roll_; }
    int yaw() const { return yaw_; }
    void decodeAngularPosition();
    void calculateTimeOnSide();
    PaddleSide getSide() const;
    String getSideStr() const;
    unsigned long getTimeOnSide() const { return timeOnSide; };
    unsigned long getTimeOnSideStart() const { return timeOnSideStart; }
    double getLeftToRightRatio() const;
private:
    bool onRightside() const;
    bool onLeftside() const;
    static const String separator;
    String message;
    String savedMessage;
    int sn_;
    int pitch_;
    int roll_;
    int yaw_;
    PaddleSide prevSide;
    unsigned long timeOnSideStart;
    unsigned long timeOnSide;
    unsigned long totalTimeOnLeft;
    unsigned long totalTimeOnRight;
};
