
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
public:
  void readGps();
  GpsReport(TinyGPS& g): gps(g), speed(0) {}
  StatusIndicator::Status write(Logger& logger);
  SpeedMessage speedMessage() const;
};
