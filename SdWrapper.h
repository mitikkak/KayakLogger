#pragma once

#include "SD.h"
class SdWrapper
{
public:
    int printCardContent(char* const area, const int maxSize) const;
    File getFirst();
    void deleteFirst();
};
