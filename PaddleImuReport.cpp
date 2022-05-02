
#include <cstring>
#include "PaddleImuReport.h"

const String PaddleImuReport::separator{";"};
PaddleImuReport::PaddleImuReport()
: message{},
  savedMessage{},
  sn_{},
  pitch_{},
  roll_{},
  yaw_{},
  prevSide{PaddleSide::right},
  timeOnSideStart{0},
  timeOnSide{0},
  totalTimeOnLeft{0},
  totalTimeOnRight{0},
  leftCatch{},
  leftStroke{},
  leftExit{},
  rightCatch{},
  rightStroke{},
  rightExit{},
  currPos{Position::unknown},
  prevTimePosUpdated{0},
  prevTimePositionChecked{0},
  updated{false}
{
}
void PaddleImuReport::init()
{
    message = "";
}
void PaddleImuReport::push(const String& s)
{
#ifndef UNIT_TEST
    message += String(millis());
#else
    message += String(std::to_string(millis()));
#endif
    message += separator;
    message += s;
}
void PaddleImuReport::push(const TiltValues& tilt)
{
	pitch_ = static_cast<int>(tilt.pitch);
	roll_ = static_cast<int>(tilt.roll);
	yaw_ = static_cast<int>(tilt.yaw);
}
void PaddleImuReport::write(/*Logger& logger*/)
{
    message += "\n";
    //logger.logMessage(message);
    savedMessage = message;
    init();
}
void PaddleImuReport::decodeAngularPosition()
{
    if (savedMessage.length() == 0)
    {
        return;
    }
    char* str = const_cast<char*>(savedMessage.c_str());
    const char* pch = strtok (str,separator.c_str());
    int i = 0;
    while (pch != NULL)
    {
      //printf ("%p, %s\n",pch, pch);
      pch = strtok (NULL,separator.c_str());
      if (i == 0) { } // millis of sender, do nothing
      else if (i == 1)
      {
          sn_ = atoi(pch);
      }
      else if (i == 2)
      { // pitch
          //Serial.printf("Pitch: %s \n\r", pch);
          pitch_ = atoi(pch);
      }
      else if (i == 3)
      { // roll
          //Serial.printf("Roll: %s \n\r", pch);
          roll_ = atoi(pch);
      }
      else if (i == 4)
      { // yaw
          //Serial.printf("Yaw: %s \n\r", pch);
          yaw_ = atoi(pch);
      }
      else if (i == 5)
      {
    	  currPos = static_cast<Position>(atoi(pch));
      }
      else if (i == 6)
      {
    	  stats.strokesLeft = atoi(pch);
      }
      else if (i == 7)
      {
    	  stats.strokesRight = atoi(pch);
      }
      else if (i == 8)
      {
    	  stats.leftDeltaTime = atoi(pch);
      }
      else if (i == 9)
      {
    	  stats.rightDeltaTime = atoi(pch);
      }
      i++;
    }

}
PaddleSide PaddleImuReport::getSide() const
{
    PaddleSide retVal{PaddleSide::right};
    if (onLeftside())
    {
        retVal = PaddleSide::left;
    }
//    else if (onRightside())
//    {
//        retVal = PaddleSide::right;
//    }
    return retVal;
}
String PaddleImuReport::getSideStr() const
{
    String retVal = "R";
    if (onLeftside())
    {
        retVal = "L";
    }
//    else if (onRightside())
//    {
//        retVal = "R";
//    }
    return retVal;
}
bool PaddleImuReport::onLeftside() const
{
    if (roll() < 0 and roll() >= -180)
    {
        return true;
    }
    return false;
}
//bool PaddleImuReport::onRightside() const
//{
//    if (roll() >= 0 and roll() <= 180)
//    {
//        return true;
//    }
//    return false;
//}
double PaddleImuReport::getLeftToRightRatio() const
{
    if (not totalTimeOnRight) { return 0.0; }
    return static_cast<double>(totalTimeOnLeft)/static_cast<double>(totalTimeOnRight);
}
void PaddleImuReport::resetSide()
{
    totalTimeOnLeft = 0;
    totalTimeOnRight = 0;
}
#if 0
void PaddleImuReport::calculateTimeOnSide()
{
    PaddleSide const side = getSide();
    if ((side != prevSide) and (side != PaddleSide::center))
    {
        prevTimeOnSide = timeOnSide - timeOnSideStart;
        timeOnSide = 0;
        timeOnSideStart = 0;
    }
    else
    {
        if (not timeOnSide)
        {
            timeOnSideStart = millis();
        }
        timeOnSide = millis();
    }
    prevSide = side;
}
#else
void PaddleImuReport::calculateTimeOnSide()
{
    PaddleSide const side = getSide();
    unsigned long timeNow = millis();
    if (side != prevSide)
    {
        timeOnSide = timeNow - timeOnSideStart;
        //if (prevSide != PaddleSide::init)
        {
            unsigned long& totalTimeOnSide = (prevSide == PaddleSide::left) ? totalTimeOnLeft : totalTimeOnRight;
            totalTimeOnSide += timeOnSide;
        }
        timeOnSideStart = timeNow;
    }
    prevSide = side;
}
#endif
void PaddleImuReport::setLimits(const Tilt& _leftCatch, const Tilt& _leftStroke, const Tilt& _leftExit, const Tilt& _rightCatch, const Tilt& _rightStroke, const Tilt& _rightExit)
{
	leftCatch = _leftCatch;
	leftStroke = _leftStroke;
	leftExit = _leftExit;
	rightCatch = _rightCatch;
	rightStroke = _rightStroke;
	rightExit = _rightExit;
}
bool PaddleImuReport::isRollWithin(const Tilt& tilt, const Tilt& candidate) const
{
	const int limit = candidate.limitRoll;
	bool const retVal = ((tilt.roll >= candidate.roll) and (tilt.roll - candidate.roll <= limit))
    	    	    or ((candidate.roll > tilt.roll) and (candidate.roll - tilt.roll <= limit));
	//printf("retVal: %u [%d][%d] \n", retVal, tilt.roll, candidate.roll);
	return retVal;
}
bool PaddleImuReport::isPitchWithin(const Tilt& tilt, const Tilt& candidate) const
{
	const int limit = candidate.limitPitch;
	bool const retVal = ((tilt.pitch >= candidate.pitch) and (tilt.pitch - candidate.pitch <= limit))
    	    	    or ((candidate.pitch > tilt.pitch) and (candidate.pitch - tilt.pitch <= limit));
	//printf("retVal: %u [%d][%d] \n", retVal, tilt.roll, candidate.roll);
	return retVal;
}
bool PaddleImuReport::isRollAbove(const Tilt& tilt, const Tilt& candidate) const
{
	return tilt.roll >= candidate.roll;
}
bool PaddleImuReport::isRollBelow(const Tilt& tilt, const Tilt& candidate) const
{
	return tilt.roll <= candidate.roll;
}
bool PaddleImuReport::isPitchAbove(const Tilt& tilt, const Tilt& candidate) const
{
	return tilt.pitch >= candidate.pitch;
}
bool PaddleImuReport::isWithin(const Tilt& tilt, const Tilt& candidate) const
{
	return /*isPitchWithin(tilt, candidate) and*/ isRollWithin(tilt, candidate);
}
void PaddleImuReport::updatePosition()
{
	unsigned long timeNow = millis();
	if (timeNow < prevTimePositionChecked + positionCheckPeriod)
	{
		updated = false;
		return;
	}
	updated = true;
	prevTimePositionChecked = timeNow;
	unsigned long const positionLostThreshold{2000};
    Tilt const tilt{pitch(), roll(), 0};
    Position const prevPos{currPos};
    const Tilt middlePoint{0, 0, 0};
    if (currPos == Position::unknown)
    {
    	if (isWithin(tilt, leftCatch))
    	{
    		currPos = Position::leftCatch;
    	}
    	else if (isWithin(tilt, rightCatch))
    	{
    		currPos = Position::rightCatch;
    	}
    }
#if 0
    else if (currPos == Position::leftCatch)
    {
    	if (isPitchWithin(tilt, leftStroke) and isRollAbove(tilt, leftStroke))
    	{
    		currPos = Position::leftStroke;
    	}
    }
    else if (currPos == Position::leftStroke)
    {
    	if (isRollAbove(tilt, middlePoint))
    	{
    		currPos = Position::traverseRight;
    		stats.strokesLeft++;
    	}
    }
#else
    else if (currPos == Position::leftCatch)
    {
//    	if (isRollAbove(tilt, middlePoint))
//    	{
//    		currPos = Position::traverseRight;
//    		stats.strokesLeft++;
//    	}
    	if (not isWithin(tilt, leftCatch))
    	{
    		currPos = Position::traverseRight;
    		stats.strokesLeft++;
    		stats.leftDeltaTime = timeNow - stats.timeOnLeftStart;
    		stats.timeOnLeftStart = timeNow;
    	}
    }
#endif
    else if (currPos == Position::traverseRight)
    {
    	if (isWithin(tilt, rightCatch))
    	{
    		currPos = Position::rightCatch;
    	}
    }
#if 0
    else if (currPos == Position::rightCatch)
    {
    	if (isRollWithin(tilt, rightStroke) and isPitchAbove(tilt, rightStroke))
    	{
    		currPos = Position::rightStroke;
    	}
    }
    else if (currPos == Position::rightStroke)
    {
    	if (isRollBelow(tilt, middlePoint))
    	{
    		currPos = Position::traverseLeft;
    		stats.strokesRight++;
    	}
    }
#else
    else if (currPos == Position::rightCatch)
    {
//    	if (isRollBelow(tilt, middlePoint))
//    	{
//    		currPos = Position::traverseLeft;
//    		stats.strokesRight++;
//    	}
    	if (not isWithin(tilt, rightCatch))
    	{
    		currPos = Position::traverseLeft;
    		stats.strokesRight++;
    		stats.rightDeltaTime = timeNow - stats.timeOnRightStart;
    		stats.timeOnRightStart = timeNow;
    	}
    }
#endif
    else if (currPos == Position::traverseLeft)
    {
    	if (isWithin(tilt, leftCatch))
    	{
    		currPos = Position::leftCatch;
    	}
    }
#if 0
    else if (currPos == Position::leftStroke)
    {
    	if (isWithin(tilt, leftExit))
    	{
    		currPos = Position::leftExit;
    	}
    }
    else if (currPos == Position::leftExit)
    {
    	if (not isWithin(tilt, leftExit))
    	{
    		currPos = Position::traverseRight;
    		stats.strokesLeft++;
    	}
    }
    else if (currPos == Position::traverseRight)
    {
    	if (isWithin(tilt, rightCatch))
    	{
    		currPos = Position::rightCatch;
    	}
    }
    else if (currPos == Position::rightCatch)
    {
    	if (isWithin(tilt, rightStroke))
    	{
    		currPos = Position::rightStroke;
    	}
    }
    else if (currPos == Position::rightStroke)
    {
    	if (isWithin(tilt, rightExit))
    	{
    		currPos = Position::rightExit;
    	}
    }
    else if (currPos == Position::rightExit)
    {
    	if (not isWithin(tilt, rightExit))
    	{
    		currPos = Position::traverseLeft;
    		stats.strokesRight++;
    	}
    }
    else if (currPos == Position::traverseLeft)
    {
    	if (isWithin(tilt, leftCatch))
    	{
    		currPos = Position::leftCatch;
    	}
    }
#endif
    if (currPos != prevPos)
    {
    	prevTimePosUpdated = timeNow;
    }
    if ((currPos == prevPos) and (timeNow - prevTimePosUpdated >= positionLostThreshold))
    {
    	currPos = Position::unknown;
    }
}
bool PaddleImuReport::timeToSend() const
{
	return updated;
}
String PaddleImuReport::getPositionStr() const
{
	String retVal;
	switch(currPos)
	{
		case Position::unknown:
			retVal = "UNK";
			break;
		case Position::leftCatch:
			retVal = "LCA";
			break;
#if 0
		case Position::leftStroke:
			retVal = "LST";
			break;
#endif
		case Position::traverseRight:
			retVal = "RTR";
			break;
		case Position::traverseLeft:
			retVal = "LTR";
			break;
		case Position::rightCatch:
			retVal = "RCA";
			break;
#if 0
		case Position::rightStroke:
			retVal = "RST";
			break;
		case Position::leftExit:
			retVal = "LEX";
			break;
		case Position::rightExit:
			retVal = "REX";
			break;
#endif
		default:
			retVal = "ERR";
			break;
	}
	return retVal;
}
