
#include <gtest/gtest.h>

class TestAccelerometer : public ::testing::Test {
public:

    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestAccelerometer, something)
{
    ASSERT_EQ(1,0);
}
