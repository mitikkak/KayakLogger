
#pragma once
#include "Arduino.h"
//#include "Logger.h"

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
//	leftStroke = 3,
//	leftExit = 4,
	traverseRight = 5,
	rightCatch = 6,
//	rightStroke = 7,
//	rightExit = 8,
	traverseLeft = 9,
};

struct TiltValues
{
	double roll{0.0f};
	double pitch{0.0f};
	double yaw{0.0f};
};

class Tilt
{
public:
	Tilt()
	: pitch{0}, roll{0}, limitPitch{0}, limitRoll{0}
	{}

	Tilt(int const _pitch, int const _roll, int const _limit)
	: pitch{_pitch},
	  roll{_roll},
	  limitPitch{_limit},
	  limitRoll{_limit}
	{}
	Tilt(int const _pitch, int const _roll, int const _limitPitch, int const _limitRoll)
	: pitch{_pitch},
	  roll{_roll},
	  limitPitch{_limitPitch},
	  limitRoll{_limitRoll}
	{}
	int pitch;
	int roll;
	int limitPitch;
	int limitRoll;
};
class PaddleImuReport
{
public:
    struct Stats
	{
    	Stats(): strokesLeft{0}, strokesRight{0}, leftDeltaTime{0}, timeOnLeftStart{0}, rightDeltaTime{0}, timeOnRightStart{0} {}
    	unsigned int strokesLeft;
    	unsigned int strokesRight;
    	unsigned long leftDeltaTime;
        unsigned long timeOnLeftStart;
    	unsigned long rightDeltaTime;
        unsigned long timeOnRightStart;
	};

    PaddleImuReport();
    void init();
    void push(const String& s);
    void push(const TiltValues& tilt);
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
    String getPositionStr() const;
    unsigned int numStrokesLeft() const { return stats.strokesLeft; }
    unsigned int numStrokesRight() const { return stats.strokesRight; }
    bool timeToSend() const;
    const Stats& getStats() const { return stats; }
private:
    bool onRightside() const;
    bool onLeftside() const;
    bool isWithin(const Tilt& tilt, const Tilt& candidate) const;
    bool isPitchWithin(const Tilt& tilt, const Tilt& candidate) const;
    bool isRollWithin(const Tilt& tilt, const Tilt& candidate) const;
    bool isRollAbove(const Tilt& tilt, const Tilt& candidate) const;
    bool isRollBelow(const Tilt& tilt, const Tilt& candidate) const;
    bool isPitchAbove(const Tilt& tilt, const Tilt& candidate) const;
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
    unsigned long prevTimePositionChecked;
    bool updated;
    static unsigned long constexpr positionCheckPeriod{50};
    Stats stats;

};
