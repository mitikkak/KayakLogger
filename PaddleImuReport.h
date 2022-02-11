
#pragma once
#include "Arduino.h"
#include "Logger.h"

enum class PaddleSide
{
   // center = 1,
    //init = 1,
    left = 2,
    right = 3
};

enum class Position
{
	transit = 1,
    leftCatch = 2,
	leftStroke = 3,
	leftExit = 4,
	traverseRight = 5,
};

class Tilt
{
public:
	Tilt()
	: pitch{0}, roll{0}
	{}

	Tilt(int const _pitch, int const _roll)
	: pitch{_pitch},
	  roll{_roll}
	{}
	int pitch;
	int roll;
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
    void resetSide();
    unsigned long getTimeOnSide() const { return timeOnSide; };
    unsigned long getTimeOnSideStart() const { return timeOnSideStart; }
    double getLeftToRightRatio() const;
    unsigned long getTotalTimeOnLeft() const { return totalTimeOnLeft; }
    unsigned long getTotalTimeOnRight() const { return totalTimeOnRight; }
    void setLimits(const Tilt& _leftCatch, const Tilt& _leftStroke, const Tilt& _leftExit, const Tilt& _rightCatch, const Tilt& _rightExit);
    Position updatePosition();
private:
    bool onRightside() const;
    bool onLeftside() const;
    bool isWithin(const Tilt& tilt, const Tilt& candidate, const int limit) const;
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
    Tilt leftCatch;
    Tilt leftStroke;
    Tilt leftExit;
    Tilt rightCatch;
    Tilt rightExit;
    Position prevPos;
};
