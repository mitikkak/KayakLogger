
class GpsReport
{
  SoftwareSerial& ss;
  TinyGPS& gps;
  void readGps();
public:
  GpsReport(SoftwareSerial& s, TinyGPS& g): ss(s), gps(g) {}
  StatusIndicator::Status write(Logger& logger);
};
