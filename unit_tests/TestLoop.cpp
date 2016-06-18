
#include <gtest/gtest.h>
#include "Loop.h"

class TestLoop : public ::testing::Test {
public:

    TestLoop() : pin(0) {}
    const int pin;
    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestLoop, construct)
{
    loop();
}
