
class GpsReport
{
  SoftwareSerial& ss;
  TinyGPS& gps;
public:
  void readGps();
  GpsReport(SoftwareSerial& s, TinyGPS& g): ss(s), gps(g) {}
  StatusIndicator::Status write(Logger& logger);
};
