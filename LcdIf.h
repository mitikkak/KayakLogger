
#pragma once

#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"

extern Adafruit_PCD8544 lcdImpl;

class LcdIf
{
public:
    void begin(const int contrast = 50);
    Print& printer();
    void print(const String& message);
    void clear();
    void row(const int r);
    void display();
};
extern LcdIf lcd;
