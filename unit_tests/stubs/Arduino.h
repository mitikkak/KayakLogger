
#ifndef _ARDUINO_H
#define _ARDUINO_H
//#define ARDUINO 100
void pinMode(const int pin, const int mode);
long millis();
void digitalWrite(const int pin, const int state);
void delay(const int millis);

static const int OUTPUT = 1;
static const int HIGH = 1;
static const int LOW = 0;
typedef char byte;

static const int A0 = 90;
static const int A1 = 91;
static const int A2 = 92;
static const int A3 = 93;
#endif
