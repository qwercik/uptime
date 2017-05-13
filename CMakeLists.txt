cmake_minimum_required(VERSION 3.7)
project(uptime)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/uptime.c include/uptime/uptime.h)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}_DIR}/lib)
include_directories(include)
add_library(uptime ${SOURCE_FILES})