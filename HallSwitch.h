
#if 0
#include "Components.h"

void hallSwitch_ISR() {
  hallSwitchState = digitalRead(HALL_SWITCH);
  if (hallSwitchState == LOW)
  {
     loggingOn = true;
  }
}

#endif
