cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(liblapin-tests CXX)

add_subdirectory(flexible_load)
add_subdirectory(ini)
add_subdirectory(lisp)
add_subdirectory(unix)
add_subdirectory(vector)
add_subdirectory(xml)