cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and call cmake from there")
endif()

project(liblapin CXX)

# Use strict C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

option(WITH_TESTS "Build unitests" OFF)
option(WITH_COVERAGE "Build with code coverage" OFF)
option(BUILD_STATIC "Build static lib" ON)
option(BUILD_SHARED "Build shared lib" ON)
option(WITH_OPENCV "Build with opencv" ON)
option(WITH_LIBUSB "Build with libusb" ON)


if(WITH_COVERAGE)
    add_compile_options(-O0 -g --coverage)
    if(NOT BUILD_STATIC)
        message(FATAL_ERROR "Coverage need static build")
    endif()
endif()

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/deps/"
)

add_subdirectory(src)

if(WITH_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
