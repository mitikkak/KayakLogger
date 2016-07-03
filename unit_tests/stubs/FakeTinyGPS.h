
#ifndef _FAKE_TINY_GPS_H
#define _FAKE_TINY_GPS_H
class TinyGPS
{
public:
    static unsigned int encodeCounter;
    static unsigned int hdopCounter;
    static unsigned int getPosCounter;
    static unsigned int crackCounter;
    static unsigned int speedCounter;
    static void initCounters();
    void encode(const char) const;
    unsigned long const hdop() const;
    void f_get_position(float*, float*, const int) const;
    void crack_datetime(int* year, byte* month, byte* day, byte* hour, byte* minute, byte* second,
                        int, int) const;
    float f_speed_kmph() const;
};
#endif
