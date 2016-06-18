
class LiquidCrystal
{
public:
    LiquidCrystal(const int rs, const int enable, const int d4, const int d5, const int d6, const int d7);
    void begin(const int cols, const int rows) const;
    void print(const char* const message) const;
    void print(float const value, const int precision) const;
    void clear() const;
    void setCursor(const int, const int) const;
};
