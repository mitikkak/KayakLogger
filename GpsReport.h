
struct SpeedMessage
{
    char* header;
    double value;
};

class GpsReport
{
  public:
  unsigned int HDOP;
  TinyGPSPlus& gps;
  
  double speed;
public:
  bool readGps();
  GpsReport(TinyGPSPlus& g): HDOP(), gps(g), speed(0) {}
  bool write(Logger& logger);
  SpeedMessage speedMessage() const;
};
