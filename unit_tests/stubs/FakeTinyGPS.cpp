
#include "Arduino.h"
#include "FakeTinyGPS.h"

unsigned int TinyGPS::encodeCounter = 0;
unsigned int TinyGPS::hdopCounter = 0;
unsigned int TinyGPS::getPosCounter = 0;
unsigned int TinyGPS::crackCounter = 0;
unsigned int TinyGPS::speedCounter = 0;

void TinyGPS::initCounters()
{
    encodeCounter = 0;
    hdopCounter = 0;
    getPosCounter = 0;
    crackCounter = 0;
    speedCounter = 0;
}

void TinyGPS::encode(const char) const
{
    encodeCounter++;
}
unsigned long const TinyGPS::hdop() const
{
    hdopCounter++;
    return 0;
}
void TinyGPS::f_get_position(float*, float*, const int) const
{
    getPosCounter++;
}
void TinyGPS::crack_datetime(int* year, byte* month, byte* day, byte* hour, byte* minute, byte* second,
                    int, int) const
{
    crackCounter++;
}
float TinyGPS::f_speed_kmph() const
{
    speedCounter++;
    return 0;
}
