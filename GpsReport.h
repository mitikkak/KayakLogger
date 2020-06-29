
struct SpeedMessage
{
    char* header;
    float value;
};

class GpsReport
{
  public:
  unsigned int HDOP;
  TinyGPSPlus& gps;
  
  float speed;
public:
  void readGps();
  GpsReport(TinyGPSPlus& g): HDOP(), gps(g), speed(0) {}
  bool write(Logger& logger);
  SpeedMessage speedMessage() const;
};
