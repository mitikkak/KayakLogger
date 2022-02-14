
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
	unknown = 1,
    leftCatch = 2,
	leftStroke = 3,
	leftExit = 4,
	traverseRight = 5,
	rightCatch = 6,
	rightStroke = 7,
	rightExit = 8,
	traverseLeft = 9,
};

class Tilt
{
public:
	Tilt()
	: pitch{0}, roll{0}, limit{0}
	{}

	Tilt(int const _pitch, int const _roll, int const _limit)
	: pitch{_pitch},
	  roll{_roll},
	  limit{_limit}
	{}
	int pitch;
	int roll;
	int limit;
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
    void setLimits(const Tilt& _leftCatch, const Tilt& _leftStroke, const Tilt& _leftExit, const Tilt& _rightCatch, const Tilt& _rightStroke, const Tilt& _rightExit);
    void updatePosition();
    Position getPosition() const { return currPos; }
    unsigned int numStrokesLeft() const { return stats.strokesLeft; }
    unsigned int numStrokesRight() const { return stats.strokesRight; }
private:
    struct Stats
	{
    	Stats(): strokesLeft{0}, strokesRight{0} {}
    	unsigned int strokesLeft;
    	unsigned int strokesRight;
	};
    bool onRightside() const;
    bool onLeftside() const;
    bool isWithin(const Tilt& tilt, const Tilt& candidate) const;
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
    Tilt rightStroke;
    Tilt rightExit;
    Position currPos;
    unsigned long prevTimePosUpdated;
    Stats stats;

};
