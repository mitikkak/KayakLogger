
#include <gtest/gtest.h>
#include "Loop.h"
#include "FakeSoftwareSerial.h"
#include "Arduino.h"
#include "FakeTinyGPS.h"
#include "PreCompilerOptions.h"
#include "FakeLiquidCrystal.h"
#include "Components.h"

class TestLoop : public ::testing::Test {
public:

    TestLoop() : pin(0) {}
    const int pin;
    void SetUp()
    {
        TinyGPS::initCounters();
        LiquidCrystal::initCounters();
        Arduino::timeNow = 0;
        prevTimeGpsHandled = 0;
        prevTimeTiltHandled = 0;
    }

    void TearDown() {

    }
};

TEST_F(TestLoop, construct)
{
    SoftwareSerial::available_rounds = 1;
    loop();
}
TEST_F(TestLoop, gpsReportNotWritten)
{
    SoftwareSerial::available_rounds = 1;
    Arduino::timeNow =  GPS_MEASUREMENT_PERIOD;
    loop();
    EXPECT_EQ(TinyGPS::encodeCounter, 1);
    EXPECT_EQ(TinyGPS::hdopCounter, 0);
    EXPECT_EQ(TinyGPS::getPosCounter, 0);
    EXPECT_EQ(TinyGPS::crackCounter, 0);
    EXPECT_EQ(TinyGPS::speedCounter, 0);
}
TEST_F(TestLoop, gpsReportWritten)
{
    SoftwareSerial::available_rounds = 1;
    Arduino::timeNow =  GPS_MEASUREMENT_PERIOD+1;
    loop();
    EXPECT_EQ(TinyGPS::encodeCounter, 1);
    EXPECT_EQ(TinyGPS::hdopCounter, 1);
    EXPECT_EQ(TinyGPS::getPosCounter, 1);
    EXPECT_EQ(TinyGPS::crackCounter, 1);
    EXPECT_EQ(TinyGPS::speedCounter, 1);
}
TEST_F(TestLoop, lcdDisplayRefreshed)
{
    SoftwareSerial::available_rounds = 1;
    Arduino::timeNow =  GPS_MEASUREMENT_PERIOD+1;
    loop();
    EXPECT_EQ(LiquidCrystal::clearCounter, 1);
    EXPECT_EQ(LiquidCrystal::cursorCounter, 1);
    EXPECT_EQ(LiquidCrystal::printCounter, 1);
}

