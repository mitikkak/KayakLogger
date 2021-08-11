
#include "Arduino.h"
#include <cstring>

long Arduino::timeNow = 0;
void pinMode(const int pin, const int mode)
{

}
long millis()
{
    return Arduino::timeNow;
}
void delay(const int millis)
{

}

void digitalWrite(const int pin, const int state)
{

}

char * 	itoa (int val, char *s, int radix)
{
  std::string result{std::to_string(val)};
  strcat(s, result.c_str());
  return s;
}
