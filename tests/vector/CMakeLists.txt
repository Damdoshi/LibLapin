project(vector C)
add_executable(vector src/main.c)

set_property(TARGET vector PROPERTY C_STANDARD 11)

target_link_libraries(vector PRIVATE lapin-static sfml-graphics sfml-audio sfml-window sfml-system stdc++ dl m avcall pthread)

add_test(NAME vector COMMAND vector)