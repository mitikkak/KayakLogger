
#ifndef _STATUS_INDICATOR_H
#define _STATUS_INDICATOR_H
class StatusIndicator
{
  public:
  enum Status
  {
  Status_ok = 0,
  Status_sdAppendFailed = 1,
  Status_hdopUnreliable = 2,
  Status_mkDirFailed = 3
  };

  StatusIndicator(const int p);
  void init();
  void newEvent(Status const st, int const milliSecs);
  void continueCurrentState(int const milliSecs);
  private:
  static const int schedulingPeriod = 1000;
  static const int okSchedule = 0x20; // 5sec LOW, 1 sec HIGH
  static const int sdFailSchedule = 0x2A; // 1sec LOW, 1 sec HIGH
  static const int hdopFailSchedule = 0x3F; // HIGH

  void startNextState(Status const st, int const milliSecs);
  void nextPeriod(const int milliSecs);
  const int pin;
  int periodStartedAt;
  int currentSchedule;
  Status currentState;
  Status queue;
};
#endif
