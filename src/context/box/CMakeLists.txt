list(APPEND LAPIN_SRC
${CMAKE_CURRENT_LIST_DIR}/click.cpp
${CMAKE_CURRENT_LIST_DIR}/delete_box.cpp
${CMAKE_CURRENT_LIST_DIR}/display.cpp
${CMAKE_CURRENT_LIST_DIR}/entering.cpp
${CMAKE_CURRENT_LIST_DIR}/fetch_box.cpp
${CMAKE_CURRENT_LIST_DIR}/init_box_environ.cpp
${CMAKE_CURRENT_LIST_DIR}/label.cpp
${CMAKE_CURRENT_LIST_DIR}/leaving.cpp
${CMAKE_CURRENT_LIST_DIR}/load.cpp
${CMAKE_CURRENT_LIST_DIR}/loop.cpp
${CMAKE_CURRENT_LIST_DIR}/move.cpp
${CMAKE_CURRENT_LIST_DIR}/new_box.cpp
${CMAKE_CURRENT_LIST_DIR}/read.cpp
${CMAKE_CURRENT_LIST_DIR}/simple_box.cpp
)

include(${CMAKE_CURRENT_LIST_DIR}/label/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/simple_box/CMakeLists.txt)