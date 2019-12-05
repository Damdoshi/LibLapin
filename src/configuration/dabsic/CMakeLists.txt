list(APPEND LAPIN_SRC
${CMAKE_CURRENT_LIST_DIR}/read_array.cpp
${CMAKE_CURRENT_LIST_DIR}/read_csv.cpp
${CMAKE_CURRENT_LIST_DIR}/read_dabsic.cpp
${CMAKE_CURRENT_LIST_DIR}/read_field.cpp
${CMAKE_CURRENT_LIST_DIR}/read_field_name.cpp
${CMAKE_CURRENT_LIST_DIR}/read_field_value.cpp
${CMAKE_CURRENT_LIST_DIR}/read_function.cpp
${CMAKE_CURRENT_LIST_DIR}/read_inside_array.cpp
${CMAKE_CURRENT_LIST_DIR}/read_inside_scope.cpp
${CMAKE_CURRENT_LIST_DIR}/read_litterals.cpp
${CMAKE_CURRENT_LIST_DIR}/read_scope.cpp
${CMAKE_CURRENT_LIST_DIR}/read_separator.cpp
${CMAKE_CURRENT_LIST_DIR}/read_sequence.cpp
${CMAKE_CURRENT_LIST_DIR}/read_xml.cpp
${CMAKE_CURRENT_LIST_DIR}/write_dabsic.cpp
)

include(${CMAKE_CURRENT_LIST_DIR}/seq/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/function/CMakeLists.txt)