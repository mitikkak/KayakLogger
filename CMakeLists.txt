
cmake_minimum_required(VERSION 3.1)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE("PROJECT_ROOT: ${PROJECT_ROOT}")

set(ARDUINO_CMAKE_DIR ${PROJECT_ROOT}/arduino_cmake)

add_definitions(-DIIC_LCD)
#add_definitions(-DHALL_SWITCH_ON)
add_definitions(-DGPS_ON)
#add_definitions(-DACCELEROMETER_ON)
#add_definitions(-DSTATUS_INDICATOR_ON)
#add_definitions(-DRUNTIME_SERIAL_ON)

set(SRC_DIR ${PROJECT_ROOT})
set(IIC_LCD_SRC ${PROJECT_ROOT}/externals/LiquidCrystal_I2C)
set(EXTERNALS_DIR ${PROJECT_ROOT}/externals)
set(GPS_DIR ${PROJECT_ROOT}/externals/TinyGPS)
set(SDFAT_DIR ${PROJECT_ROOT}/externals/SdFat)
set(ACCELEROMETER_DIR ${PROJECT_ROOT}/externals/ADXL345)
set(GFX_SRC ${PROJECT_ROOT}/Adafruit-GFX-Library)
set(PCD8544_ESP8266_SRC ${PROJECT_ROOT}/Adafruit-PCD8544-Nokia-5110-LCD-library)
set(PCD8544_ESP32_SRC ${PROJECT_ROOT}/Adafruit-PCD8544-ShiftOut)

set(adafruit_lcd_esp8266_sources 
        ${PCD8544_ESP8266_SRC}/Adafruit_PCD8544.cpp
        ${GFX_SRC}/Adafruit_GFX.cpp
)

set(adafruit_lcd_esp32_sources 
        ${PCD8544_ESP32_SRC}/Adafruit_PCD8544.cpp
        ${GFX_SRC}/Adafruit_GFX.cpp
)

#add_subdirectory(${PROJECT_ROOT}/googletest)
#add_subdirectory(cmake/atmega328)
add_subdirectory(${ARDUINO_CMAKE_DIR}/esp8266/core)
add_subdirectory(${ARDUINO_CMAKE_DIR}/esp32/core)
#add_subdirectory(cmake/esp8266)
add_subdirectory(cmake/esp8266_12e)
add_subdirectory(cmake/esp_wroom32)

#Run cmake with - DCMAKE_BUILD_TYPE = Debug
#add_subdirectory(cmake/ut)
