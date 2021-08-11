
#include <gtest/gtest.h>
#include "Arduino.h"
#include "Distance.h"

class TestDistance : public ::testing::Test {
public:

    TestDistance() {}
    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestDistance, testInitValue)
{
  Distance d;
  EXPECT_EQ(0.0, d.value());
}
TEST_F(TestDistance, testOneValue)
{
  Distance d;
  d.add(0.055560, 5000);
  EXPECT_NEAR(0.000077, d.value(), 0.00001);
}
TEST_F(TestDistance, testSeveralValues)
{
  Distance d;
  d.add(7.463561, 5000);
  EXPECT_NEAR(0.010366, d.value(), 0.00001);
  d.add(5.78, 5000);
  EXPECT_NEAR(0.018366, d.value(), 0.0001);
  d.add(12.4, 5000);
  EXPECT_NEAR(0.035566, d.value(), 0.0001);
}
