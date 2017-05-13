cmake_minimum_required(VERSION 3.7)
project(uptime)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES uptime.c uptime.h)
add_library(uptime ${SOURCE_FILES})