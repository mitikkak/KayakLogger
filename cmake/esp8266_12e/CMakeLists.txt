
project(kayak_logger_esp8266_12e)

include(${ARDUINO_CMAKE_DIR}/esp8266/paths.cmake)
include(${ARDUINO_CMAKE_DIR}/esp8266/tools.cmake)
include(${ARDUINO_CMAKE_DIR}/esp8266/defs.cmake)
include(${ARDUINO_CMAKE_DIR}/esp8266/core.cmake)
include(${ARDUINO_CMAKE_DIR}/esp8266/deploy.cmake)
include(${ARDUINO_CMAKE_DIR}/esp8266/libs.cmake)

set(sources
    ${SRC_DIR}/Loop.cpp
    ${SRC_DIR}/Setup.cpp
    ${SRC_DIR}/GpsReport.cpp
    ${SRC_DIR}/ElementQueue.cpp
    ${SRC_DIR}/AverageSpeed.cpp
    ${SRC_DIR}/Distance.cpp
    ${SRC_DIR}/LogElement.cpp
    ${SRC_DIR}/Logger.cpp
    ${SRC_DIR}/Components.cpp
    ${SRC_DIR}/TiltReport.cpp
    ${SRC_DIR}/LcdIf.cpp
    ${SRC_DIR}/PaddleImuReport.cpp
    ${ACCELEROMETER_DIR}/ADXL345.cpp
    ${SDFAT_ESP8266_DIR}
    ${gps_sources}
    ${SPI_ESP8266_DIR}/SPI.cpp
    ${SDFAT_ESP8266_DIR}/File.cpp
    ${SDFAT_ESP8266_DIR}/SD.cpp
    ${SDFAT_ESP8266_DIR}/utility/Sd2Card.cpp
    ${SDFAT_ESP8266_DIR}/utility/SdFile.cpp
    ${SDFAT_ESP8266_DIR}/utility/SdVolume.cpp
    ${WIRE_ESP8266_DIR}/Wire.cpp
    ${wifi_sources}
    ${esp8266_async_udp_sources}
)

add_executable(${PROJECT_NAME} ${sources} ${adafruit_lcd_esp8266_sources})
target_link_libraries(${PROJECT_NAME} PRIVATE ${esp8266_12e_linker_options})
add_dependencies(${PROJECT_NAME} ${esp8266_12e_core_libs})

target_compile_options(
    ${PROJECT_NAME} PRIVATE
    ${compiler_set_cpp}
    ${esp8266_12e_defs}
)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${SRC_DIR}
    ${GPS_DIR}
    ${SDFAT_ESP8266_DIR}
    ${SPI_ESP8266_DIR}
    ${WIRE_ESP8266_DIR}
    ${WIFI_ESP8266_DIR}
    ${ESP_ASYNC_UDP_DIR}
    ${GFX_SRC}
    ${PCD8544_ESP8266_SRC}
    ${ACCELEROMETER_DIR}
    ${esp8266_12e_path}
)

elf_to_bin_esp8266_12e(${PROJECT_NAME})
upload_esp8266_12e(${PROJECT_NAME} elf_to_bin_esp8266_12e_${PROJECT_NAME})




