
struct SpeedMessage
{
    char* header;
    float value;
};

class GpsReport
{
  public:
  unsigned int HDOP;
  private:
  TinyGPS& gps;
  
  float speed;
  byte hour_, minute_, second_;
public:
  void readGps();
  GpsReport(TinyGPS& g): HDOP(), gps(g), speed(0), hour_(0), minute_(0), second_(0) {}
  bool write(Logger& logger);
  SpeedMessage speedMessage() const;
  byte hour() const { return hour_; }
  byte minute() const { return minute_; }
  byte second() const { return second_; }
};
