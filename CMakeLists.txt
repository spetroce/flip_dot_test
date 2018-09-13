cmake_minimum_required(VERSION 2.8.11)
project(FlipDotTest)

## mio
set(MIO_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/modules")
include_directories(${MIO_INCLUDE_DIR})

## Setup Release and Debug variables
include("${MIO_INCLUDE_DIR}/mio/cmake/DefaultConfigTypes.cmake")

## Qt5
option(WITH_QT "Build flip_dot_test with Qt GUI interface" ON)
if(WITH_QT)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  find_package(Qt5 QUIET COMPONENTS Core Widgets)
  if(${Qt5_FOUND})
    add_definitions(-DHAVE_QT)
    message(STATUS "Package Qt5: Found")
  else()
    message(STATUS "Package Qt5: Not Found")
  endif()
endif()

## libmio_serial_com
add_library(mio_serial_com "${MIO_INCLUDE_DIR}/mio/serial_com/serial_com.cpp")

set(FLIP_DOT_TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/modules/flip_dot_test")
set(FLIP_DOT_TEST_SRC "${FLIP_DOT_TEST_DIR}/main.cpp")
if(Qt5_FOUND)
  qt5_wrap_ui(ui_image_list_viewer "${FLIP_DOT_TEST_DIR}/flip_dot_test.ui")
  list(APPEND FLIP_DOT_TEST_SRC ${ui_image_list_viewer} "${FLIP_DOT_TEST_DIR}/flip_dot_test.cpp")
endif()
add_executable(flip_dot_test ${FLIP_DOT_TEST_SRC})
target_link_libraries(flip_dot_test mio_serial_com)
if(Qt5_FOUND)
  target_link_libraries(flip_dot_test Qt5::Core Qt5::Widgets)
endif()

