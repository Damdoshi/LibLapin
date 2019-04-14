cmake_minimum_required (VERSION 2.6)
project (sfMidi)

set(INCROOT   ${PROJECT_SOURCE_DIR}/include)
set(INCSFMIDI ${INCROOT}/sfMidi)
set(SRCROOT   ${PROJECT_SOURCE_DIR}/src)
set(SRCSFMIDI ${SRCROOT}/sfMidi)

include_directories(${INCROOT})

set(CMAKE_DEBUG_POSTFIX "_d")

set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

add_library(sfMidi STATIC
              ${INCSFMIDI}/Midi.h
              ${INCSFMIDI}/Loader.h
              ${INCSFMIDI}/Music.h
              ${INCROOT}/sfMidi.h
              ${SRCSFMIDI}/Midi.cpp
              ${SRCSFMIDI}/Loader.cpp
              ${SRCSFMIDI}/Music.cpp
            )
            
add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)
            
install (TARGETS sfMidi DESTINATION lib)
install (FILES ${INCROOT}/sfMidi.h DESTINATION include)
install (FILES ${INCSFMIDI}/Midi.h
               ${INCSFMIDI}/Loader.h
               ${INCSFMIDI}/Music.h
         DESTINATION include/sfMidi)
