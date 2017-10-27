
cmake_minimum_required(VERSION 3.1)
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
MESSAGE("PROJECT_ROOT: ${PROJECT_ROOT}")

add_subdirectory(cmake/atmega328)
add_subdirectory(cmake/ut)