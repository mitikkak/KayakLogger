
#ifdef ACCELEROMETER_ON
class TiltReport
{
    ADXL345& acc;
public:

    TiltReport(ADXL345& a) : acc(a) {}
    StatusIndicator::Status write(Logger& logger);

};
#endif
