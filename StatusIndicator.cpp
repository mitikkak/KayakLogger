
#include "Arduino.h"
#include "StatusIndicator.h"

StatusIndicator::StatusIndicator(const int p): pin(p), currentState(Status_ok),
   queue(Status_ok){}

void StatusIndicator::init()
{
  pinMode(pin, OUTPUT);
  startNextState(Status_ok, millis());
}
void StatusIndicator::newEvent(Status const st, int const milliSecs)
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
void StatusIndicator::continueCurrentState(int const milliSecs)
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
void StatusIndicator::startNextState(Status const st, int const milliSecs)
{
  periodStartedAt = milliSecs;
  currentState = st;
  if (st == Status_ok) currentSchedule = okSchedule;
  if (st == Status_sdAppendFailed) currentSchedule = sdFailSchedule;
  if (st == Status_hdopUnreliable) currentSchedule = hdopFailSchedule;
}
void StatusIndicator::nextPeriod(const int milliSecs)
{
  const int nextLedState = currentSchedule & 0x1;
//    Serial.print("sch:");Serial.print(currentSchedule);Serial.print(",nextLedState:"); Serial.print(nextLedState); Serial.print(", at:");Serial.println(milliSecs);
  digitalWrite(pin, nextLedState);
  periodStartedAt = milliSecs;
}
