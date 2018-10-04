
#include "LcdDbg.h"
#include "Components.h"

void lcdDbg(const char* const msg, int value)
{
#ifndef UNIT_TEST
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
  lcd.print(value);
  delay(1000);
#endif
}
