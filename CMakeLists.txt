cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(liblapin CXX)

# Use strict C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2 REQUIRED audio graphics window system)
find_package(OpenCV REQUIRED)
find_library(LIBUSB_LIBRARY NAMES usb PATH_SUFFIXES "lib" "lib32" "lib64")

file(GLOB SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/**/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/deps/"
)

add_compile_options(-Wno-write-strings -Wno-unused-result -Wno-format-security -Wno-frame-address -Wno-narrowing)

add_library(lapin SHARED ${SRC_FILES})
add_library(lapin-static STATIC ${SRC_FILES})
