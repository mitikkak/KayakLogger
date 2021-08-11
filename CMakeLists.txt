
cmake_minimum_required(VERSION 3.1)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE("PROJECT_ROOT: ${PROJECT_ROOT}")

set(ARDUINO_CMAKE_DIR ${PROJECT_ROOT}/arduino_cmake)

add_definitions(-DIIC_LCD)
#add_definitions(-DHALL_SWITCH_ON)
add_definitions(-DGPS_ON)
#add_definitions(-DPADDLE_IMU)
#add_definitions(-DACCELEROMETER_ON)
#add_definitions(-DSTATUS_INDICATOR_ON)
#add_definitions(-DRUNTIME_SERIAL_ON)
#add_definitions(-DFS_NO_GLOBALS)

set(SRC_DIR ${PROJECT_ROOT})
set(IIC_LCD_SRC ${PROJECT_ROOT}/externals/LiquidCrystal_I2C)
set(EXTERNALS_DIR ${PROJECT_ROOT}/externals)
set(GPS_DIR ${PROJECT_ROOT}/TinyGPSPlusExtended/src)
set(SDFAT_DIR ${PROJECT_ROOT}/externals/SdFat)
set(ACCELEROMETER_DIR ${PROJECT_ROOT}/externals/ADXL345)
set(GFX_SRC ${PROJECT_ROOT}/Adafruit-GFX-Library)
set(PCD8544_ESP8266_SRC ${PROJECT_ROOT}/Adafruit-PCD8544-Nokia-5110-LCD-library)
set(PCD8544_ESP32_SRC ${PROJECT_ROOT}/Adafruit-PCD8544-ShiftOut)
set(ESP_ASYNC_WEB_SERVER_DIR ${PROJECT_ROOT}/ESPAsyncWebServer/src)
set(ESP_ASYNC_TCP_DIR ${PROJECT_ROOT}/ESPAsyncTCP/src)
set(ESP32_ASYNC_TCP_DIR ${PROJECT_ROOT}/AsyncTCP_ESP32/src)

set(adafruit_lcd_esp8266_sources 
        ${PCD8544_ESP8266_SRC}/Adafruit_PCD8544.cpp
        ${GFX_SRC}/Adafruit_GFX.cpp
)

set(adafruit_lcd_esp32_sources 
        ${PCD8544_ESP32_SRC}/Adafruit_PCD8544.cpp
        ${GFX_SRC}/Adafruit_GFX.cpp
)
set(ESP_ASYNC_UDP_DIR ${PROJECT_ROOT}/ESPAsyncUDP/src)
set(esp8266_async_udp_sources ${ESP_ASYNC_UDP_DIR}/AsyncUDP.cpp)
set(gps_sources ${GPS_DIR}/TinyGPS++.cpp)
set(esp_async_web_server_sources
    ${ESP_ASYNC_WEB_SERVER_DIR}/WebServer.cpp
    ${ESP_ASYNC_WEB_SERVER_DIR}/WebRequest.cpp
    ${ESP_ASYNC_WEB_SERVER_DIR}/WebResponses.cpp
)
set(esp_async_tcp_sources
    ${ESP_ASYNC_TCP_DIR}/ESPAsyncTCP.cpp
)
set(esp32_async_tcp_sources ${ESP32_ASYNC_TCP_DIR}/AsyncTCP.cpp)

add_subdirectory(${PROJECT_ROOT}/googletest)
#add_subdirectory(cmake/atmega328)
add_subdirectory(${ARDUINO_CMAKE_DIR}/esp8266/core)
add_subdirectory(${ARDUINO_CMAKE_DIR}/esp32/core)
#add_subdirectory(cmake/esp8266)
add_subdirectory(cmake/esp8266_12e)
add_subdirectory(cmake/esp_wroom32)

#Run cmake with - DCMAKE_BUILD_TYPE = Debug
add_subdirectory(cmake/ut)
