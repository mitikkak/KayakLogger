
#pragma once

#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"

extern Adafruit_PCD8544 lcdImpl;

class LcdIf
{
public:
    void begin(const int contrast = 50);
    void bigText();
    void smallText();
    Print& printer();
    void print(const String& message);
    void clear();
    void row(const int r);
    void display();
    void upsideDown();
    void sideways();
    void separator();
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    int16_t width();

private:
    int textSize{1};
};
extern LcdIf lcd;
