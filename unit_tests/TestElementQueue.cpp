

#include <gtest/gtest.h>
#include <fstream>
using namespace std;
#include "ElementQueue.h"

class TestElementQueue : public ::testing::Test {
public:

    TestElementQueue() {}
    void SetUp() {
    }

    void TearDown() {

    }
};

TEST_F(TestElementQueue, construct)
{
    ElementQueue q;
}
