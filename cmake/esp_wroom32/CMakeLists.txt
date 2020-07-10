
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
    ${SRC_DIR}/Logger.cpp
    ${SRC_DIR}/Components.cpp
    ${SRC_DIR}/TiltReport.cpp
    ${SRC_DIR}/LcdIf.cpp
    ${SRC_DIR}/PaddleImuReport.cpp
    ${SRC_DIR}/AsyncWebServerWrapper.cpp
    ${SRC_DIR}/SdWrapper.cpp
    ${gps_sources}
)
set(ext_sources
    ${esp32_wire_sources}
    ${esp32_spi_sources}
    ${esp32_fs_sources}
    ${esp32_sd_sources}
    ${adafruit_lcd_esp32_sources}
    ${esp32_wifi_sources}
    ${esp32_async_udp_sources}
    ${esp_async_web_server_sources}
    ${esp32_async_tcp_sources}
    ${esp32_mdns_sources}
)

set(EXT_SRC_DIR
    ${ESP32_WIRE_SRC_DIR}
    ${ESP32_SD_SRC_DIR}
    ${ESP32_FS_SRC_DIR}
    ${ESP32_SPI_SRC_DIR}
    ${ESP32_WIFI_SRC_DIR}
    ${ESP32_ASYNC_UDP_SRC_DIR}
    ${ESP32_MDNS_SRC_DIR}
    ${ESP32_ASYNC_TCP_DIR}
    ${ESP_ASYNC_WEB_SERVER_DIR}
    ${GFX_SRC}
    ${PCD8544_ESP32_SRC}
    ${ACCELEROMETER_DIR}
    ${GPS_DIR}
)
set(all_sources ${sources} ${ext_sources})
build_targets_espwroom32("${all_sources}" "${EXT_SRC_DIR}")
