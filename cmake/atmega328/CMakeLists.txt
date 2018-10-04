
project(kayak_logger_atmega328)


include(${ARDUINO_CMAKE_DIR}/atmega328/paths.cmake)
include(${ARDUINO_CMAKE_DIR}/atmega328/tools.cmake)
include(${ARDUINO_CMAKE_DIR}/atmega328/defs.cmake)
include(${ARDUINO_CMAKE_DIR}/atmega328/core.cmake)
include(${ARDUINO_CMAKE_DIR}/atmega328/deploy.cmake)

if(ARDUINO_PATH MATCHES .*1.6.12.*)
   message("ATMEGA328: Using supported arduino version")
else()
   message(FATAL_ERROR "ATMEGA328: Non supported Arduino version used. Only version 1.6.12 is currently supported, proceed with own risk. For example, SD logging is not working with 1.8.5")
endif()
set(ARDUINO_PINS ${ARDUINO_PATH}/hardware/arduino/avr/variants/standard)
set(ARDUINO_LCD_SRC ${ARDUINO_PATH}/libraries/LiquidCrystal/src/)
set(ARDUINO_WIRE_SRC ${ARDUINO_PATH}/hardware/arduino/avr/libraries/Wire/src/)

set(sources
    ${SRC_DIR}/Loop.cpp
    ${SRC_DIR}/Setup.cpp
    ${SRC_DIR}/GpsReport.cpp
    ${SRC_DIR}/ElementQueue.cpp
    ${SRC_DIR}/AverageSpeed.cpp
    ${SRC_DIR}/Distance.cpp
    ${SRC_DIR}/LogElement.cpp
    ${SRC_DIR}/StatusIndicator.cpp
    ${SRC_DIR}/Logger.cpp
    ${SRC_DIR}/Components.cpp
    ${SRC_DIR}/TiltReport.cpp
    ${ACCELEROMETER_DIR}/ADXL345.cpp
    ${ARDUINO_LCD_SRC}/LiquidCrystal.cpp
    ${IIC_LCD_SRC}/LiquidCrystal_I2C.cpp
    ${ARDUINO_WIRE_SRC}/Wire.cpp
    ${ARDUINO_WIRE_SRC}/utility/twi.c
    ${SDFAT_DIR}/ostream.cpp
    ${SDFAT_DIR}/SdStream.cpp
    ${SDFAT_DIR}/SdFat.cpp
    ${SDFAT_DIR}/SdBaseFile.cpp
    ${SDFAT_DIR}/SdVolume.cpp
    ${SDFAT_DIR}/Sd2Card.cpp
    ${GPS_DIR}/TinyGPS.cpp
)

add_executable(${PROJECT_NAME} ${sources} ${atmega328_core_sources})
target_link_libraries(${PROJECT_NAME} ${atmega328_linker_options})
target_compile_options(
    ${PROJECT_NAME} PRIVATE
    ${atmega328_compiler_set_cpp}
)
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${ATMEGA328_CORE_SRC} 
    ${ARDUINO_PINS}
    ${SRC_DIR}
    ${GPS_DIR}
    ${SDFAT_DIR}
    ${ARDUINO_LCD_SRC}
    ${IIC_LCD_SRC}
    ${ACCELEROMETER_DIR}
    ${ARDUINO_WIRE_SRC}
)

upload_atmega328(${PROJECT_NAME} ${PROJECT_NAME})
