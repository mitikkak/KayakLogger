
#include "FakeSdFat.h"

bool SdFat::begin(const int cs) const
{
    return true;
}
bool SdFat::mkdir(const char* const) const
{
    return true;
}
void SdFat::add(std::string name)
{
   files.emplace_back(name);
}
bool SdFat::exists(const char* const name) const
{
   bool retValue = false;
   for (std::string file : files)
   {
     if (0 == file.compare(name))
     {
        retValue = true;
     }
   }
   return retValue;
}
