
#ifndef _ARDUINO_H
#define _ARDUINO_H
//#define ARDUINO 100
void pinMode(const int pin, const int mode);
long millis();
void digitalWrite(const int pin, const int state);

static const int OUTPUT = 1;
static const int HIGH = 1;
static const int LOW = 0;
typedef char byte;

#endif
