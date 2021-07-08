cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(liblapin-src CXX)

add_compile_options(
    -Wno-write-strings
    -Wno-unused-result
    -Wno-format-security
    -Wno-frame-address
    -Wno-narrowing
)

add_compile_definitions(BUNNY_ALLOCATOR_DEACTIVATED)

set(LAPIN_SRC)
list(APPEND LAPIN_SRC
    ${PROJECT_SOURCE_DIR}/color_configuration.cpp
    ${PROJECT_SOURCE_DIR}/parsing.cpp
    ${PROJECT_SOURCE_DIR}/placement_configuration.cpp
    ${PROJECT_SOURCE_DIR}/placement.cpp
)
include(allocator/CMakeLists.txt)
include(asynclock/CMakeLists.txt)
include(camera/CMakeLists.txt)
include(collide/CMakeLists.txt)
include(configuration/CMakeLists.txt)
include(container/CMakeLists.txt)
include(context/CMakeLists.txt)
include(database/CMakeLists.txt)
include(deps/CMakeLists.txt)
include(error/CMakeLists.txt)
include(events/CMakeLists.txt)
include(graphics/CMakeLists.txt)
include(hardware/CMakeLists.txt)
include(hash/CMakeLists.txt)
include(history/CMakeLists.txt)
include(misc/CMakeLists.txt)
include(monitor/CMakeLists.txt)
include(network/CMakeLists.txt)
include(parallax/CMakeLists.txt)
include(plugin/CMakeLists.txt)
include(security/CMakeLists.txt)
include(shader/CMakeLists.txt)
include(sound/CMakeLists.txt)
include(sound_sprite/CMakeLists.txt)
include(text/CMakeLists.txt)
include(threads/CMakeLists.txt)
include(tilemap/CMakeLists.txt)
include(unix/CMakeLists.txt)
include(window/CMakeLists.txt)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(BUNNY_DEBUG)
endif()

add_library(objlib OBJECT ${LAPIN_SRC})
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE ON)

if(BUILD_SHARED)
    add_library(lapin SHARED $<TARGET_OBJECTS:objlib>)
endif()

if(BUILD_STATIC)
    add_library(lapin-static STATIC $<TARGET_OBJECTS:objlib>)
endif()
