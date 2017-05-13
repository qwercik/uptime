cmake_minimum_required(VERSION 3.7)
project(uptime)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/uptime.c include/uptime/uptime.h)
include_directories(include)
add_library(uptime ${SOURCE_FILES})