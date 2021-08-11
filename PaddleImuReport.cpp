
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
  prevSide{PaddleSide::center},
  timeOnSideStart{0},
  timeOnSide{0},
  totalTimeOnLeft{0},
  totalTimeOnRight{0}
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
      i++;
    }

}
PaddleSide PaddleImuReport::getSide() const
{
    PaddleSide retVal{PaddleSide::center};
    if (onLeftside())
    {
        retVal = PaddleSide::left;
    }
    else if (onRightside())
    {
        retVal = PaddleSide::right;
    }
    return retVal;
}
String PaddleImuReport::getSideStr() const
{
    String retVal = "C";
    if (onLeftside())
    {
        retVal = "L";
    }
    else if (onRightside())
    {
        retVal = "R";
    }
    return retVal;
}
bool PaddleImuReport::onLeftside() const
{
    if (roll() > 180 and roll() < 360)
    {
        return true;
    }
    return false;
}
bool PaddleImuReport::onRightside() const
{
    if (roll() > 1 and roll() <= 180)
    {
        return true;
    }
    return false;
}
double PaddleImuReport::getLeftToRightRatio() const
{
    if (not totalTimeOnRight) { return 0.0; }
    return static_cast<double>(totalTimeOnLeft)/static_cast<double>(totalTimeOnRight);
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
        timeOnSideStart = timeNow;
        if (prevSide != PaddleSide::center)
        {
            unsigned long& totalTimeOnSide = (prevSide == PaddleSide::left) ? totalTimeOnLeft : totalTimeOnRight;
            totalTimeOnSide += timeOnSide;
        }
    }
    prevSide = side;
}
#endif

