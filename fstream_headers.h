
#ifdef UNIT_TEST
#include <fstream>
using namespace std;
#else
 #if defined ESP8266 || defined ESP32
  #include "SD.h"
 #else
  #include "SdFat.h"
 #endif
#endif
