
#include <gtest/gtest.h>
#include "StatusIndicator.h"
#include "FakeSoftwareSerial.h"
#include "Arduino.h"
#include <fstream>
using namespace std;
#include "Logger.h"
#include "ADXL345.h"
#include "TiltReport.h"
#include "FakeSdFat.h"


class TestTiltReport : public ::testing::Test {
public:

    TestTiltReport() {}
    void SetUp()
    {
    }

    void TearDown()
    {
        Arduino::timeNow = 0;
    }
    class MyLogger: public Logger
    {
    public:
        static const int pin = 9;
        ElementQueue* queue;
        MyLogger(SdFat& sdFat): Logger(sdFat, pin), queue(0) {}
        ~MyLogger()
        {
            delete queue;
        }

        bool hasLog() const
        {
            return (queue != 0);
        }
        ElementQueue& getLog()
        {
            return *queue;
        }
        StatusIndicator::Status myLogEvent(ElementQueue& q)
        {
            queue = new ElementQueue(q);
            return StatusIndicator::Status_ok;
        }
    };
    class MyAccMeter: public ADXL345
    {
        double _x;
        double _y;
        double _z;
        public:
        MyAccMeter(): _x(0), _y(0), _z(0) {}
        void setValues(double x, double y, double z)
        {
            _x = x; _y = y; _z = z;
        }
        void read(double *xG, double *yG, double *zG, double& xAcc, double& yAcc, double& zAcc)
        {
            *xG = _x; *yG = _y; *zG = _z;
        }
    };
    template <typename ELEM_TYPE>
    void verifyElement(ElementQueue& queue, const char* expectedMsg, ELEM_TYPE const expectedValue)
    {
        LogElement<ELEM_TYPE>* elem = static_cast<LogElement<ELEM_TYPE>*>(queue.pop());
        ASSERT_STREQ(expectedMsg, elem->msg);
        ASSERT_EQ(expectedValue, elem->value);
    }
};

TEST_F(TestTiltReport, write)
{
    long& expectedMillis = Arduino::timeNow;
    double const expectedPitch = 0;
    double const expectedRoll = 0;
    expectedMillis = 500;
    MyAccMeter accMeter;
    accMeter.setValues(0.0,0.0,0.0);
    TiltReport r(accMeter);
    SdFat sdFat;
    MyLogger logger(sdFat);
    r.write(logger);
    EXPECT_EQ(true, logger.hasLog());
    ElementQueue& queue = logger.getLog();
    verifyElement(queue, "millis", expectedMillis);
    verifyElement(queue, "pitch", expectedPitch);
    verifyElement(queue, "roll", expectedRoll);
    LogElement<double>* x = static_cast<LogElement<double>*>(queue.pop());
    ASSERT_STREQ("x", x->msg);
    LogElement<double>* y = static_cast<LogElement<double>*>(queue.pop());
    ASSERT_STREQ("y", y->msg);
    LogElement<double>* z = static_cast<LogElement<double>*>(queue.pop());
    ASSERT_STREQ("z", z->msg);
}
