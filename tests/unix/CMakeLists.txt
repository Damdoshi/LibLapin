cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(unix C)
add_executable(unix src/main.c)

set_property(TARGET unix PROPERTY C_STANDARD 11)

target_link_libraries(unix PRIVATE sfml-graphics sfml-audio sfml-window sfml-system stdc++ dl m avcall pthread)

if(WITH_COVERAGE)
    target_link_libraries(unix PRIVATE lapin-static --coverage)
else()
    target_link_libraries(unix PRIVATE lapin-static)
endif()

add_test(NAME unix COMMAND unix)