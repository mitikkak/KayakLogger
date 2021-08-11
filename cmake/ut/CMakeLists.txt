project(ut)

set(STUBS_DIR ${PROJECT_ROOT}/unit_tests/stubs)
set(TEST_SRC_DIR ${PROJECT_ROOT}/unit_tests)
set(TEST_SRC ${TEST_SRC_DIR}/TestDistance.cpp
             #${TEST_SRC_DIR}/TestLogger.cpp
             ${TEST_SRC_DIR}/TestPaddleImuReport.cpp
             ${TEST_SRC_DIR}/test_main.cpp
)
set(KAYAK_LOGGER_SRC ${SRC_DIR}/Distance.cpp
        ${SRC_DIR}/ElementQueue.cpp
        ${SRC_DIR}/PaddleImuReport.cpp
        #${SRC_DIR}/Logger.cpp
        ${STUBS_DIR}/FakeSdFat.cpp
        ${STUBS_DIR}/Arduino.cpp
)
add_executable(${PROJECT_NAME} ${TEST_SRC} ${ACCELEROMETER_SRC} ${STUBS_SRC} ${KAYAK_LOGGER_SRC})

set(GTEST_LIBRARIES gtest gmock)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
target_compile_options(
    ${PROJECT_NAME} PRIVATE
    -std=gnu++11
)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE 
      ${PROJECT_ROOT}/googletest/googletest/include 
      ${STUBS_DIR} 
      ${SRC_DIR} 
      ${ACCELEROMETER_DIR} 
      ${IIC_LCD_SRC}
      #${GFX_SRC}
      #${PCD8544_ESP32_SRC}
)

target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
    UNIT_TEST
    ARDUINO=10800
)
