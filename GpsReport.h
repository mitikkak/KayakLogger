
struct SpeedMessage
{
    SpeedMessage(): header{}, value{0.0f} {}
    SpeedMessage(const double v) : header{}, value{v} {}
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
  GpsReport(TinyGPSPlus& g): HDOP(), gps(g), speed(0) {}
  bool write(Logger& logger);
  SpeedMessage speedMessage() const;
};
