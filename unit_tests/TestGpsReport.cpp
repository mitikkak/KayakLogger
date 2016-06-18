

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

TEST_F(TestGpsReport, construct)
{
    SoftwareSerial ss(0,0);
    TinyGPS gps;
    GpsReport r(ss, gps);
}
