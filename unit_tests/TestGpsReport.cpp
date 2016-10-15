

#include <gtest/gtest.h>
#include "StatusIndicator.h"
#include "FakeSoftwareSerial.h"
#include "Arduino.h"
#include "FakeTinyGPS.h"
#include <fstream>
using namespace std;
#include "Logger.h"
#include "GpsReport.h"


class TestGpsReport : public ::testing::Test {
public:

    TestGpsReport() {}
    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestGpsReport, zeroSpeed)
{
    TinyGPS gps;
    GpsReport r(gps);
    r.readGps();
    SpeedMessage m = r.speedMessage();
    EXPECT_EQ(0.0, m.value);
    EXPECT_STREQ("Speed: ", m.header);
}
