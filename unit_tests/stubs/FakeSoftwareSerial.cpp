
#include "FakeSoftwareSerial.h"

unsigned int SoftwareSerial::available_rounds = 0;
SoftwareSerial::SoftwareSerial(const int, const int)
{}
void SoftwareSerial::begin(const int bauds) const
{

}
bool SoftwareSerial::available() const
{
    if (available_rounds == 0)
    {
        return false;
    }
    else
    {
        available_rounds--;
        return true;
    }
}
char SoftwareSerial::read() const
{
    return -1;
}
