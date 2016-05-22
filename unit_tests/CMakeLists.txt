project(kayak_logger)
cmake_minimum_required(VERSION 2.8)

# Locate GTest
find_package(GTest REQUIRED)
#set(MOTOR_DIR /home/mikko/Arduino/libraries/Motor)
#set(STUBS_DIR /home/mikko/qt_projects/Stubs)
include_directories(${GTEST_INCLUDE_DIRS})

set( CMAKE_BUILD_TYPE Debug)
aux_source_directory(. TEST_SRC)
#aux_source_directory(${MOTOR_DIR} MOTOR_SRC)
add_executable(${PROJECT_NAME} ${TEST_SRC})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
