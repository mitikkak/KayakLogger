
#include "FakeSoftwareSerial.h"

bool SoftwareSerial::available() const
{
    return true;
}
char SoftwareSerial::read() const
{
    return -1;
}
