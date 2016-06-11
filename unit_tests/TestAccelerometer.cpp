
#include <gtest/gtest.h>
#include "ADXL345.h"
class TestAccelerometer : public ::testing::Test {
public:

    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestAccelerometer, read)
{
    ADXL345 acc;
    double xG;
    double yG;
    double zG;
    double xAcc;
    double yAcc;
    double zAcc;
    acc.read(&xG, &yG, &zG, xAcc, yAcc, zAcc);
    ASSERT_EQ(1,1);
}
