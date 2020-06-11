cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(lisp C)
add_executable(lisp src/main.c)

set_property(TARGET lisp PROPERTY C_STANDARD 11)

target_link_libraries(lisp PRIVATE sfml-graphics sfml-audio sfml-window sfml-system stdc++ -Wl,--no-as-needed dl m avcall pthread)

if(WITH_COVERAGE)
    target_link_libraries(lisp PRIVATE lapin-static --coverage)
else()
    target_link_libraries(lisp PRIVATE lapin-static)
endif()

add_custom_command(TARGET lisp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/*.lisp"
        "$<TARGET_FILE_DIR:lisp>/"
)

add_test(NAME lisp COMMAND lisp)