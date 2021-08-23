#include <gtest/gtest.h>
//#include "Arduino.h"
#include "PaddleImuReport.h"

class TestPaddleImuReport : public ::testing::Test {
public:

    TestPaddleImuReport() {}
    void SetUp() {
        r.init();
    }

    void TearDown() {

    }
    void inputOneMessage(const String& message)
    {
        r.push(message);
        r.write();
        r.decodeAngularPosition();
        r.calculateTimeOnSide();
    }
    PaddleImuReport r;
};

#if 0
TEST_F(TestPaddleImuReport, calculateTimeOnSide_centerNoStrokes)
{
    Arduino::timeNow = 20;
    inputOneMessage("1000;0;100;360;100");
    EXPECT_EQ(0, r.getTimeOnSide());
    EXPECT_EQ(0, r.getTimeOnSideStart());
    EXPECT_EQ(0.0, r.getLeftToRightRatio());
}
TEST_F(TestPaddleImuReport, calculateTimeOnSide_centerAfterStrokeSet)
{
    Arduino::timeNow = 1000;
    inputOneMessage("0;0;100;10;100");
    EXPECT_EQ(1000, r.getTimeOnSide());
    EXPECT_EQ(1000, r.getTimeOnSideStart());
    Arduino::timeNow = 2000;
    inputOneMessage("0;0;100;5;100");
    EXPECT_EQ(1000, r.getTimeOnSide());
    EXPECT_EQ(1000, r.getTimeOnSideStart());
    Arduino::timeNow = 3000;
    inputOneMessage("0;0;100;350;100");
    EXPECT_EQ(2000, r.getTimeOnSide());
    EXPECT_EQ(3000, r.getTimeOnSideStart());
    Arduino::timeNow = 4000;
    inputOneMessage("0;0;100;355;100");
    EXPECT_EQ(2000, r.getTimeOnSide());
    EXPECT_EQ(3000, r.getTimeOnSideStart());
    Arduino::timeNow = 4500;
    inputOneMessage("0;0;100;360;100");
    EXPECT_EQ(1500, r.getTimeOnSide());
    EXPECT_EQ(4500, r.getTimeOnSideStart());
    double const expectedRatio = static_cast<double>(1500)/static_cast<double>(2000);
    EXPECT_NEAR(expectedRatio, r.getLeftToRightRatio(), 0.0001);
}
TEST_F(TestPaddleImuReport, calculateTimeOnSide_leftToCenterToRightEqualsOneStroke)
{
    Arduino::timeNow = 1000;
    inputOneMessage("0;0;100;350;100");
    EXPECT_EQ(PaddleSide::left, r.getSide());
    EXPECT_EQ(1000, r.getTimeOnSide());
    EXPECT_EQ(1000, r.getTimeOnSideStart());
    EXPECT_EQ(0, r.getTotalTimeOnLeft());
    Arduino::timeNow = 2000;
    inputOneMessage("0;0;100;360;100");
    EXPECT_EQ(PaddleSide::center, r.getSide());
    EXPECT_EQ(2000, r.getTimeOnSide());
    EXPECT_EQ(1000, r.getTimeOnSideStart());
    EXPECT_EQ(0, r.getTotalTimeOnLeft());
    Arduino::timeNow = 2100;
    inputOneMessage("0;0;100;10;100");
    EXPECT_EQ(PaddleSide::right, r.getSide());
    EXPECT_EQ(0, r.getTimeOnSide());
    EXPECT_EQ(2100, r.getTimeOnSideStart());
    EXPECT_EQ(2100, r.getTotalTimeOnLeft());
}
#endif
TEST_F(TestPaddleImuReport, calculateTimeOnSide_leftToRightOneStroke)
{
    Arduino::timeNow = 1000;
    inputOneMessage("0;0;100;350;100");
    EXPECT_EQ(PaddleSide::left, r.getSide());
    EXPECT_EQ(1000, r.getTimeOnSide()); // init -> left
    EXPECT_EQ(1000, r.getTimeOnSideStart());
    EXPECT_EQ(0, r.getTotalTimeOnLeft());
    Arduino::timeNow = 1500;
    inputOneMessage("0;0;100;360;100");
    EXPECT_EQ(PaddleSide::left, r.getSide());
    EXPECT_EQ(1000, r.getTimeOnSide()); // not updated live, but post-stroke
    EXPECT_EQ(1000, r.getTimeOnSideStart());
    EXPECT_EQ(0, r.getTotalTimeOnLeft());
    Arduino::timeNow = 1600;
    inputOneMessage("0;0;100;1;100");
    EXPECT_EQ(PaddleSide::right, r.getSide());
    EXPECT_EQ(600, r.getTimeOnSide());
    EXPECT_EQ(1600, r.getTimeOnSideStart());
    EXPECT_EQ(600, r.getTotalTimeOnLeft());
    EXPECT_EQ(0, r.getTotalTimeOnRight());
}
TEST_F(TestPaddleImuReport, calculateTimeOnSide_rightToLeftOneStroke)
{
    Arduino::timeNow = 1000;
    inputOneMessage("0;0;100;10;100");
    EXPECT_EQ(PaddleSide::right, r.getSide());
    EXPECT_EQ(1000, r.getTimeOnSide()); // init -> right
    EXPECT_EQ(1000, r.getTimeOnSideStart());
    EXPECT_EQ(0, r.getTotalTimeOnRight());
    Arduino::timeNow = 1500;
    inputOneMessage("0;0;100;1;100");
    EXPECT_EQ(PaddleSide::right, r.getSide());
    EXPECT_EQ(1000, r.getTimeOnSide()); // not updated live, but post-stroke
    EXPECT_EQ(1000, r.getTimeOnSideStart());
    EXPECT_EQ(0, r.getTotalTimeOnRight());
    Arduino::timeNow = 1600;
    inputOneMessage("0;0;100;360;100");
    EXPECT_EQ(PaddleSide::left, r.getSide());
    EXPECT_EQ(600, r.getTimeOnSide());
    EXPECT_EQ(1600, r.getTimeOnSideStart());
    EXPECT_EQ(600, r.getTotalTimeOnRight());
    EXPECT_EQ(0, r.getTotalTimeOnLeft());
}
