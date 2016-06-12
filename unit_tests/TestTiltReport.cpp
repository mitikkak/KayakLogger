
#include <gtest/gtest.h>
#include "StatusIndicator.h"
#include "FakeSoftwareSerial.h"
#include "Arduino.h"
#include <fstream>
using namespace std;
#include "Logger.h"
#include "TiltReport.h"

class TestTiltReport : public ::testing::Test {
public:

    TestTiltReport() {}
    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestTiltReport, construct)
{
    //SoftwareSerial ss;
    TiltReport r; //(ss, gps);
}
