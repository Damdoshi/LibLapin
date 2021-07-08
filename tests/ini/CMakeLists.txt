cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(ini C)
add_executable(ini src/main.c)

set_property(TARGET ini PROPERTY C_STANDARD 11)

target_link_libraries(ini PRIVATE sfml-graphics sfml-audio sfml-window sfml-system stdc++ -Wl,--no-as-needed dl m avcall pthread)

if(WITH_COVERAGE)
    target_link_libraries(ini PRIVATE lapin-static --coverage)
else()
    target_link_libraries(ini PRIVATE lapin-static)
endif()

add_custom_command(TARGET ini POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ini"
        "$<TARGET_FILE_DIR:ini>/"
)

add_test(NAME ini COMMAND ini)