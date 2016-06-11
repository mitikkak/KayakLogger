
#include <gtest/gtest.h>
#include "Arduino.h"
#include "StatusIndicator.h"

class TestStatusIndicator : public ::testing::Test {
public:

    TestStatusIndicator() : pin(0) {}
    const int pin;
    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestStatusIndicator, construct)
{
    StatusIndicator s(pin);
}
