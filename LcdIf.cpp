
#include "LcdIf.h"
#include "Components.h"

void LcdIf::begin(const int contrast)
{
    lcdImpl.begin();
    lcdImpl.setContrast(contrast);
    clear();
}
void LcdIf::bigText()
{
    textSize = 2;
    lcdImpl.setTextSize(textSize, textSize);
}
void LcdIf::smallText()
{
    textSize = 1;
    lcdImpl.setTextSize(textSize, textSize);
}
void LcdIf::clear()
{
  lcdImpl.clearDisplay();
  display();
  lcdImpl.setCursor(0,0);
}
void LcdIf::row(const int r)
{
    lcdImpl.setCursor(0, r*8*textSize);
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
