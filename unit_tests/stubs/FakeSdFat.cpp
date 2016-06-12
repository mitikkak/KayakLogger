
#include "FakeSdFat.h"

bool SdFat::begin(const int cs) const
{
    return true;
}
bool SdFat::mkdir(const char* const) const
{
    return true;
}
