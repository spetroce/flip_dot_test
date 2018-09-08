cmake_minimum_required(VERSION 2.8.11)
project(FlipDotTest)

## Setup Release and Debug variables
include(modules/mio/cmake/DefaultConfigTypes.cmake)

## libmio_serialCom
include_directories(modules)
add_library(mio_serial_com modules/mio/serial_com/serial_com.cpp)

add_executable(flip_dot_test modules/flip_dot_test/main.cpp)
target_link_libraries(flip_dot_test mio_serial_com)
