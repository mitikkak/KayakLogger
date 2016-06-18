
struct SpeedMessage
{
    char* header;
    float value;
};

class GpsReport
{
  SoftwareSerial& ss;
  TinyGPS& gps;
  float speed;
public:
  void readGps();
  GpsReport(SoftwareSerial& s, TinyGPS& g): ss(s), gps(g), speed(0) {}
  StatusIndicator::Status write(Logger& logger);
  SpeedMessage speedMessage() const;
};
