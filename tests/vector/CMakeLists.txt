cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(vector C)
add_executable(vector src/main.c)

set_property(TARGET vector PROPERTY C_STANDARD 11)

target_link_libraries(vector PRIVATE sfml-graphics sfml-audio sfml-window sfml-system stdc++ dl m avcall pthread)

if(WITH_COVERAGE)
    target_link_libraries(vector PRIVATE lapin-static --coverage)
else()
    target_link_libraries(vector PRIVATE lapin-static)
endif()

add_test(NAME vector COMMAND vector)