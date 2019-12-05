cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(xml C)
add_executable(xml src/main.c)

set_property(TARGET xml PROPERTY C_STANDARD 11)

target_link_libraries(xml PRIVATE sfml-graphics sfml-audio sfml-window sfml-system stdc++ dl m avcall pthread)

if(WITH_COVERAGE)
    target_link_libraries(xml PRIVATE lapin-static --coverage)
else()
    target_link_libraries(xml PRIVATE lapin-static)
endif()

add_custom_command(TARGET xml POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/*.xml"
        "$<TARGET_FILE_DIR:xml>/"
)

add_test(NAME xml COMMAND xml)