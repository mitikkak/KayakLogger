
#include <gtest/gtest.h>
#include "Arduino.h"
using namespace std;
#include "Logger.h"
#include "FakeSdFat.h"

class TestLogger : public ::testing::Test {
public:

    SdFat sd;
    const int pin;
    TestLogger():sd(), pin(9) {}
    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestLogger, construct)
{
    Logger l(sd, pin);
}
