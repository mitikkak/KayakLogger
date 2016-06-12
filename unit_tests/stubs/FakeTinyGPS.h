
class TinyGPS
{
public:
    void encode(const char) const;
    unsigned long const hdop() const;
    void f_get_position(float*, float*, const int) const;
    void crack_datetime(int* year, byte* month, byte* day, byte* hour, byte* minute, byte* second,
                        int, int) const;
    float f_speed_kmph() const;
};
