project(ut)
cmake_minimum_required(VERSION 2.8)

# Locate GTest
find_package(GTest REQUIRED GTEST_ROOT=/home/mitikkak/googletest/googletest)
set(EXTERNALS_DIR ${PROJECT_ROOT}/externals)
MESSAGE("Externals: ${EXTERNALS_DIR}")
set(ACCELEROMETER_DIR ${EXTERNALS_DIR}/ADXL345)
MESSAGE("Accelerometer: ${ACCELEROMETER_DIR}")
set(KAYAK_LOGGER_SRC_DIR ${PROJECT_ROOT})
set(STUBS_DIR ${PROJECT_ROOT}/unit_tests/stubs)
set(TEST_SRC_DIR ${PROJECT_ROOT}/unit_tests)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${KAYAK_LOGGER_SRC_DIR})
include_directories(${ACCELEROMETER_DIR})
include_directories(${STUBS_DIR})
include_directories(${IIC_LCD_SRC})

set( CMAKE_BUILD_TYPE Debug)
set(TEST_SRC ${TEST_SRC_DIR}/TestDistance.cpp
             ${TEST_SRC_DIR}/TestLogger.cpp
             ${TEST_SRC_DIR}/test_main.cpp
)
set(KAYAK_LOGGER_SRC ${KAYAK_LOGGER_SRC_DIR}/Distance.cpp
        ${KAYAK_LOGGER_SRC_DIR}/ElementQueue.cpp
        ${KAYAK_LOGGER_SRC_DIR}/Logger.cpp
        ${STUBS_DIR}/FakeSdFat.cpp
        ${STUBS_DIR}/Arduino.cpp
)
add_executable(${PROJECT_NAME} ${TEST_SRC} ${ACCELEROMETER_SRC} ${STUBS_SRC} ${KAYAK_LOGGER_SRC})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
target_compile_options(
    ${PROJECT_NAME} PRIVATE
    -std=gnu++11
)
target_compile_definitions(
    ${PROJECT_NAME} PRIVATE
    UNIT_TEST
    ARDUINO=10800
)

