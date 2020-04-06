
#include "PaddleImuReport.h"

const String PaddleImuReport::separator{";"};
PaddleImuReport::PaddleImuReport()
: message{},
  savedMessage{},
  pitch_{},
  roll_{},
  yaw_{}
{
}
void PaddleImuReport::init()
{
    message = "";
}
void PaddleImuReport::push(const String& s)
{
    message += String(millis());
    message += separator;
    message += s;
}
void PaddleImuReport::write(Logger& logger)
{
    message += "\n";
    logger.logMessage(message);
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
    const char* pch = strtok (str,";");
    int i = 0;
    while (pch != NULL)
    {
      //printf ("%p, %s\n",pch, pch);
      pch = strtok (NULL,";");
      if (i == 0) { } // millis of sender, do nothing
      else if (i == 1) { } // sn, do nothing
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

