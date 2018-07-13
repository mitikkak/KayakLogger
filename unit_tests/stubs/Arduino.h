
#pragma once

#include <string.h>
void pinMode(const int pin, const int mode);
namespace Arduino {
extern long timeNow;
}
long millis();
void digitalWrite(const int pin, const int state);
void delay(const int millis);

static const int OUTPUT = 1;
static const int HIGH = 1;
static const int LOW = 0;
typedef char byte;
// typedef unsigned int size_t;

static const int A0 = 90;
static const int A1 = 91;
static const int A2 = 92;
static const int A3 = 93;

static constexpr int DEC{3};

char *itoa(int val, char *s, int radix);
