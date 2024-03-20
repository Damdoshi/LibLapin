cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(flexible_load C)
add_executable(flexible_load src/main.c)

set_property(TARGET flexible_load PROPERTY C_STANDARD 11)

target_link_libraries(flexible_load PRIVATE sfml-graphics sfml-audio sfml-window sfml-system stdc++ -Wl,--no-as-needed dl m avcall pthread)

if(WITH_COVERAGE)
    target_link_libraries(flexible_load PRIVATE lapin-static --coverage)
else()
    target_link_libraries(flexible_load PRIVATE lapin-static)
endif()

add_custom_command(TARGET flexible_load POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/*.dab"
        "$<TARGET_FILE_DIR:flexible_load>/"
)

add_test(NAME flexible_load COMMAND flexible_load)