#include <Wire.h>
#include <ADXL345.h>
#include <SdFat.h>
#include <SoftwareSerial.h>

#include <TinyGPS.h>

#define GPS_ON
#define ACCELEROMETER_ON
//#define RUNTIME_SERIAL_ON

#define TILT_MEASUREMENT_PERIOD 20
#define GPS_MEASUREMENT_PERIOD 2000
#define HDOP_UNRELIABLE 900

struct Element
{
  explicit Element(const char *p_msg): msg(p_msg) {}
  const char *msg;
  virtual void outputValue(ofstream& sdlog) const = 0;
};

template <class TYPE>
struct LogElement : public Element
{
  explicit LogElement(const char *p_msg, TYPE const val):
  Element(p_msg), value(val) {}
  void outputValue(ofstream& sdlog) const
  {
    sdlog << value;
  }
  TYPE const value;
};

struct ElementQueue
{
  ElementQueue():
  numOf(0)
  { for (int i = 0; i < maximum; i++) {elems[i] = 0;} }
  void push(Element* elem)
  {
    if (numOf < maximum)
    {
      elems[numOf] = elem;
      numOf++;
    }
  }
  bool peek() const
  {
    return (numOf>0);
  }
  Element* pop()
  {
    if (numOf > 0)
    {
      numOf--;
      return elems[numOf];
    }
    return 0;
  }
  private:
  static const int maximum = 11;
  int numOf;
  Element* elems[maximum];
};

class StatusIndicator
{
  public:
  enum Status
  {
  Status_ok = 0,
  Status_sdAppendFailed = 1,
  Status_hdopUnreliable = 2
  };

  StatusIndicator(const int p): pin(p), currentState(Status_ok),
     queue(Status_ok){}
  void init()
  {
    pinMode(pin, OUTPUT);
    startNextState(Status_ok, millis());
  }
  void newEvent(Status const st, int const milliSecs)
  {
//    Serial.print("new st:"); Serial.print(st); Serial.print(",at:"); Serial.println(milliSecs);
    if (currentState == Status_ok && st != Status_ok)
    {
      startNextState(st, milliSecs);
    }
    else if (queue == Status_ok)
    {
      queue = st;
    }
  }
  void continueCurrentState(int const milliSecs)
  {
    if (milliSecs - periodStartedAt > schedulingPeriod)
    {
      currentSchedule = currentSchedule >> 1;
      if (currentSchedule == 0)
      {
//        Serial.print("queue:");Serial.println(queue);
        startNextState(queue, milliSecs);
        queue = Status_ok;
      }
      nextPeriod(milliSecs);
    }
  }
  private:
  static const int schedulingPeriod = 1000;
  static const int okSchedule = 0x20; // 5sec LOW, 1 sec HIGH
  static const int sdFailSchedule = 0x2A; // 1sec LOW, 1 sec HIGH
  static const int hdopFailSchedule = 0x3F; // HIGH

  void startNextState(Status const st, int const milliSecs)
  {
    periodStartedAt = milliSecs;
    currentState = st;
    if (st == Status_ok) currentSchedule = okSchedule;
    if (st == Status_sdAppendFailed) currentSchedule = sdFailSchedule;
    if (st == Status_hdopUnreliable) currentSchedule = hdopFailSchedule;
  }
  void nextPeriod(const int milliSecs)
  {
    const int nextLedState = currentSchedule & 0x1;
//    Serial.print("sch:");Serial.print(currentSchedule);Serial.print(",nextLedState:"); Serial.print(nextLedState); Serial.print(", at:");Serial.println(milliSecs);
    digitalWrite(pin, nextLedState);
    periodStartedAt = milliSecs;
  }
  const int pin;
  int periodStartedAt;
  int currentSchedule;
  Status currentState;
  Status queue;
};

class Logger
{
  public:
  Logger(int const pin):sdCardChipSelect(pin) {}
  const int sdCardChipSelect;
  void initSdCard()
{
#ifdef RUNTIME_SERIAL_ON
  Serial.print("Initializing SD card...");
#endif
  // see if the card is present and can be initialized:
  pinMode(sdCardChipSelect, OUTPUT);
  digitalWrite(sdCardChipSelect, HIGH);

  if (!sd.begin(sdCardChipSelect)) {
#ifdef RUNTIME_SERIAL_ON
    Serial.println("Card failed, or not present");
#endif
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  digitalWrite(sdCardChipSelect, HIGH);
}
SdFat sd;

StatusIndicator::Status myLogEvent(ElementQueue& queue)
{
  // create dir if needed
  if (!sd.mkdir("LOGS/"))
  {
    //return StatusIndicator::Status_mkDirFailed;
  }
  // create or open a file for append
  ofstream sdlog("LOGS/datalog.txt", ios::out | ios::app);
  bool somethingWasWritten = false;
  
  sdlog.precision(6);
  // append a line to the file
  
  while (queue.peek())
  {
    
    
    Element* element = queue.pop();
    if (element)
    {
      somethingWasWritten = true;
      sdlog << element->msg << ": ";
      element->outputValue(sdlog);
      sdlog << " ; ";
    }
  }
  
  
  if (somethingWasWritten)
  {
    sdlog << endl;
  }
  // check for errors
  if (!sdlog) /**/
  {
    return StatusIndicator::Status_sdAppendFailed;
  }
  // file will be closed when sdlog goes out of scope
  return StatusIndicator::Status_ok;
}
};

#ifdef ACCELEROMETER_ON
ADXL345 acc;
#endif


const float alpha = 0.5;

double fXg = 0;
double fYg = 0;
double fZg = 0;

Logger logger(10);
StatusIndicator statusIndicator(5);
#ifdef GPS_ON
TinyGPS gps;
SoftwareSerial ss(4, 3);
#endif
unsigned long prevTimeTiltHandled, prevTimeGpsHandled;
void setup()
{
  #ifdef ACCELEROMETER_ON
  acc.begin();
  #endif
  Serial.begin(115200);
  #ifdef GPS_ON
  ss.begin(9600);
  #endif
  logger.initSdCard();
  delay(100);
  acc.setRange(ADXL345::RANGE_4G);
  statusIndicator.init();
  prevTimeTiltHandled = millis();
  prevTimeGpsHandled = millis();
}

StatusIndicator::Status writeTiltReport();
StatusIndicator::Status writeGpsReport();
void readGps();
void loop()
{
  unsigned long timeNow = millis();
  if (timeNow - prevTimeTiltHandled > TILT_MEASUREMENT_PERIOD)
  {
    StatusIndicator::Status const reportStatus = writeTiltReport();
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeTiltHandled = timeNow;
  }
#ifdef GPS_ON
  if (timeNow - prevTimeGpsHandled > GPS_MEASUREMENT_PERIOD)
  {
    StatusIndicator::Status const reportStatus = writeGpsReport();
    statusIndicator.newEvent(reportStatus, timeNow);
    prevTimeGpsHandled = timeNow;
  }
  else
  {
    readGps();
  }
#endif
  statusIndicator.continueCurrentState(timeNow);
}

StatusIndicator::Status writeTiltReport()
{
  double pitch, roll, Xg, Yg, Zg = 0;
  #ifdef ACCELEROMETER_ON
  double xAcc, yAcc, zAcc = 0;
  acc.read(&Xg, &Yg, &Zg, xAcc, yAcc, zAcc);
  #endif
  //Low Pass Filter
  fXg = Xg * alpha + (fXg * (1.0 - alpha));
  fYg = Yg * alpha + (fYg * (1.0 - alpha));
  fZg = Zg * alpha + (fZg * (1.0 - alpha));
  //Roll & Pitch Equations
  roll  = (atan2(-fYg, fZg)*180.0)/M_PI;
  pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/M_PI;
#ifdef RUNTIME_SERIAL_ON
  Serial.print(pitch);
  Serial.print(":");
  Serial.println(roll);
#endif
  const unsigned long milliSecs = millis();
  LogElement<unsigned long> millisElement("millis", milliSecs);
  LogElement<double> rollElement("roll", roll);
  LogElement<double> pitchElement("pitch", pitch);
  LogElement<double> xElement("x", xAcc);
  LogElement<double> yElement("y", yAcc);
  LogElement<double> zElement("z", zAcc);
  ElementQueue queue;
  queue.push(&zElement);
  queue.push(&yElement);
  queue.push(&xElement);
  queue.push(&rollElement);
  queue.push(&pitchElement);
  queue.push(&millisElement);
  return logger.myLogEvent(queue);
}

#ifdef GPS_ON
StatusIndicator::Status writeGpsReport()
{
  StatusIndicator::Status gpsStatus = StatusIndicator::Status_ok;
  readGps();
  float latitude, longitude;
  unsigned long const HDOP = gps.hdop(); //, TinyGPS::GPS_INVALID_HDOP
  if (HDOP > HDOP_UNRELIABLE)
  {
    gpsStatus = StatusIndicator::Status_hdopUnreliable;
  }
#ifdef RUNTIME_SERIAL_ON
  Serial.println(HDOP);
#endif
  LogElement<unsigned long> hdopElement("HDOP", HDOP);
  gps.f_get_position(&latitude, &longitude, 0);
  LogElement<float> latitudeElement("Lat", latitude);
  LogElement<float> longitudeElement("Lon", longitude);
  int year;
  byte month, day, hour, minute, second;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, 0,0);
  LogElement<int> yearElement("Y", year);
  LogElement<int> monthElement("Mo", month);
  LogElement<int> dayElement("D", day);
  LogElement<int> hourElement("H", hour);
  LogElement<int> minuteElement("Mi", minute);
  LogElement<int> secondElement("S", second);
  LogElement<float> speedElement("Spe", gps.f_speed_kmph());
  LogElement<float> courseElement("C", gps.f_course());
  ElementQueue queue;
  queue.push(&courseElement);
  queue.push(&speedElement);
  queue.push(&secondElement);
  queue.push(&minuteElement);
  queue.push(&hourElement);
  queue.push(&dayElement);
  queue.push(&monthElement);
  queue.push(&yearElement);
  queue.push(&longitudeElement);
  queue.push(&latitudeElement);
  queue.push(&hdopElement);
  StatusIndicator::Status const logStatus = logger.myLogEvent(queue);
  return (logStatus != StatusIndicator::Status_ok) ? logStatus : gpsStatus;
}
void readGps()
{
  while (ss.available())
  {
      gps.encode(ss.read());
  }
}
#endif


