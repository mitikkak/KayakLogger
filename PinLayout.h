
#ifdef ESP8266
/*
ESP8266:
RX- GPS
TX-GPS


*/
#define SDFAT_CS 2

#else

#ifdef RELEASE_BOARD
#error SDFAT_CS not defined
#else
#define SDFAT_CS 23
#endif

#endif

