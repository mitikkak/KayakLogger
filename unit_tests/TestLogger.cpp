
#include <gtest/gtest.h>
#include "Arduino.h"
using namespace std;
#include "FakeSdFat.h"
#include "Logger.h"

class TestLogger : public ::testing::Test {
public:

    SdFat sd;
    const int pin;
    Logger* logger;
    TestLogger():sd(), pin(9), logger(nullptr) {}
    void SetUp() {
      logger = new Logger(sd, pin);
    }

    void TearDown() {
	delete logger;
    }
};

#if 0
TEST_F(TestLogger, reserveFile)
{
  sd.add("LOGS/DATALOG_1.TXT");
  EXPECT_EQ(Logger::FileStatus::alreadyTaken, logger->reserveFile(1));
  EXPECT_EQ(Logger::FileStatus::ok, logger->reserveFile(2));
}
#endif
