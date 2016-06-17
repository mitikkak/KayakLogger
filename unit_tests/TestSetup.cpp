
#include <gtest/gtest.h>
#include "Setup.h"

class TestSetup : public ::testing::Test {
public:

    TestSetup() {}
    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestSetup, setup)
{
    setup();
}
