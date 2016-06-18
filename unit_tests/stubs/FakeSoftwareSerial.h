
class SoftwareSerial
{
public:
    static unsigned int available_rounds;
    SoftwareSerial(const int, const int);
    void begin(const int bauds) const;
    bool available() const;
    char read() const;
};

extern SoftwareSerial Serial;
