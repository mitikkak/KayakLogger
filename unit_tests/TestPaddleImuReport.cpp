#include <gtest/gtest.h>
//#include "Arduino.h"
#include "PaddleImuReport.h"

class TestPaddleImuReport : public ::testing::Test {
public:

    TestPaddleImuReport()
	: leftCatch{-50,-90, 10},
	  leftStroke{-50,-40, 20},
	  leftExit{-50,-10, 10},
	  rightCatch{-30,45, 10},
	  rightStroke{-20,20, 20},
	  rightExit{-10,10, 10}
	{}
    void SetUp() {
        r.init();
        r.setLimits(leftCatch, leftStroke, leftExit, rightCatch, rightStroke, rightExit);
    }

    void TearDown() {

    }
    void inputOneMessage(const String& message)
    {
        r.push(message);
        r.write();
        r.decodeAngularPosition();
        r.calculateTimeOnSide();
        r.updatePosition();
    }
    PaddleImuReport r;
protected:
	Tilt leftCatch;
	Tilt leftStroke;
	Tilt leftExit;
	Tilt rightCatch;
	Tilt rightStroke;
	Tilt rightExit;
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
#endif
TEST_F(TestPaddleImuReport, positions_left_right)
{
	inputOneMessage("0;0;0;0;0");
	EXPECT_EQ(Position::unknown, r.getPosition());
	inputOneMessage("0;0;-40;-70;0");
	EXPECT_EQ(Position::unknown, r.getPosition());
	inputOneMessage("0;0;-40;-80;0");
	EXPECT_EQ(Position::leftCatch, r.getPosition());
	inputOneMessage("0;0;-50;-90;0");
	EXPECT_EQ(Position::leftCatch, r.getPosition());
	inputOneMessage("0;0;-30;-60;0");
	EXPECT_EQ(Position::leftStroke, r.getPosition());
	inputOneMessage("0;0;-40;-21;0");
	EXPECT_EQ(Position::leftStroke, r.getPosition());
	inputOneMessage("0;0;-45;-20;0");
	EXPECT_EQ(Position::leftExit, r.getPosition());
	inputOneMessage("0;0;-40;-10;0");
	EXPECT_EQ(Position::leftExit, r.getPosition());
	inputOneMessage("0;0;-40;1;0");
	EXPECT_EQ(Position::traverseRight, r.getPosition());
	EXPECT_EQ(1, r.numStrokesLeft());
	EXPECT_EQ(0, r.numStrokesRight());
	inputOneMessage("0;0;-40;56;0");
	EXPECT_EQ(Position::traverseRight, r.getPosition());
	inputOneMessage("0;0;-40;40;0");
	EXPECT_EQ(Position::rightCatch, r.getPosition());
	inputOneMessage("0;0;-25;35;0");
	EXPECT_EQ(Position::rightStroke, r.getPosition());
	inputOneMessage("0;0;-15;20;0");
	EXPECT_EQ(Position::rightExit, r.getPosition());
	inputOneMessage("0;0;-5;-1;0");
	EXPECT_EQ(Position::traverseLeft, r.getPosition());
	EXPECT_EQ(1, r.numStrokesLeft());
	EXPECT_EQ(1, r.numStrokesRight());
	inputOneMessage("0;0;-40;-80;0");
	EXPECT_EQ(Position::leftCatch, r.getPosition());
}
TEST_F(TestPaddleImuReport, positions_right_left)
{
	inputOneMessage("0;0;0;0;0");
	EXPECT_EQ(Position::unknown, r.getPosition());
	inputOneMessage("0;0;-40;40;0");
	EXPECT_EQ(Position::rightCatch, r.getPosition());
	inputOneMessage("0;0;-25;35;0");
	EXPECT_EQ(Position::rightStroke, r.getPosition());
	inputOneMessage("0;0;-15;20;0");
	EXPECT_EQ(Position::rightExit, r.getPosition());
	inputOneMessage("0;0;-5;-1;0");
	EXPECT_EQ(Position::traverseLeft, r.getPosition());
	EXPECT_EQ(0, r.numStrokesLeft());
	EXPECT_EQ(1, r.numStrokesRight());
	inputOneMessage("0;0;-40;-80;0");
	EXPECT_EQ(Position::leftCatch, r.getPosition());
	inputOneMessage("0;0;-30;-60;0");
	EXPECT_EQ(Position::leftStroke, r.getPosition());
	inputOneMessage("0;0;-40;-10;0");
	EXPECT_EQ(Position::leftExit, r.getPosition());
	inputOneMessage("0;0;-40;56;0");
	EXPECT_EQ(Position::traverseRight, r.getPosition());
	EXPECT_EQ(1, r.numStrokesLeft());
	EXPECT_EQ(1, r.numStrokesRight());
	inputOneMessage("0;0;-40;55;0");
	EXPECT_EQ(Position::rightCatch, r.getPosition());
}
TEST_F(TestPaddleImuReport, positions_lost_and_found)
{
    Arduino::timeNow = 0;
	inputOneMessage("0;0;-40;40;0");
	EXPECT_EQ(Position::rightCatch, r.getPosition());
	Arduino::timeNow = 1000;
	inputOneMessage("0;0;-15;-1;0"); //straight to traverse left
	EXPECT_EQ(Position::unknown, r.getPosition());
	inputOneMessage("0;0;-40;40;0");
	EXPECT_EQ(Position::rightCatch, r.getPosition());
	EXPECT_EQ(0, r.numStrokesLeft());
	EXPECT_EQ(0, r.numStrokesRight());
}
