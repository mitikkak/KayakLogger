
#include "FakeLiquidCrystal.h"
#include <gtest/gtest.h>

unsigned int LiquidCrystal::clearCounter = 0;
unsigned int LiquidCrystal::cursorCounter = 0;
unsigned int LiquidCrystal::printCounter = 0;
void LiquidCrystal::initCounters()
{
   clearCounter = 0;
   cursorCounter = 0;
   printCounter = 0;
}

LiquidCrystal::LiquidCrystal(const int rs, const int enable, const int d4, const int d5, const int d6, const int d7)
{}
void LiquidCrystal::begin(const int cols, const int rows) const
{

}
void LiquidCrystal::print(const char* const message) const
{}
void LiquidCrystal::print(float const value, const int precision) const
{
   printCounter++;
}
void LiquidCrystal::clear() const
{
    clearCounter++;
}
void LiquidCrystal::setCursor(const int column, const int row) const
{
    EXPECT_EQ(0, column);
    if (!cursorCounter)
    {
        EXPECT_EQ(1, row);
    }
    cursorCounter++;
}
