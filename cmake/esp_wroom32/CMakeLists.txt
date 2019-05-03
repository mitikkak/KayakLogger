
project(kayak_logger_wroom32)
include(${ARDUINO_CMAKE_DIR}/esp32/wroom32.cmake)

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
    ${IIC_LCD_SRC}/LiquidCrystal_I2C.cpp
    ${GPS_DIR}/TinyGPS.cpp
)

set(EXT_SRC_DIR
    ${ESP32_WIRE_SRC_DIR}
    ${ESP32_SD_SRC_DIR}
    ${ESP32_FS_SRC_DIR}
    ${ESP32_SPI_SRC_DIR}
    ${IIC_LCD_SRC}
    ${ACCELEROMETER_DIR}
    ${GPS_DIR}
)
set(all_sources ${sources} ${ext_sources})
build_targets_espwroom32("${all_sources}" "${EXT_SRC_DIR}")