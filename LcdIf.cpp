
#include "LcdIf.h"
#include "Components.h"

void LcdIf::begin(const int contrast)
{
    lcdImpl.begin();
    lcdImpl.setContrast(contrast);
    clear();
}
void LcdIf::clear()
{
  lcdImpl.clearDisplay();
  lcdImpl.setCursor(0,0);
}
void LcdIf::row(const int r)
{
    lcdImpl.setCursor(0, r);
}
void LcdIf::display()
{
    lcdImpl.display();
}
Print& LcdIf::printer()
{
    return lcdImpl;
}
void LcdIf::print(const String& message)
{
    lcdImpl.print(message);
    display();
}
