list(APPEND LAPIN_SRC
${CMAKE_CURRENT_LIST_DIR}/box.cpp
${CMAKE_CURRENT_LIST_DIR}/context.cpp
${CMAKE_CURRENT_LIST_DIR}/depth.cpp
${CMAKE_CURRENT_LIST_DIR}/dressing.cpp
${CMAKE_CURRENT_LIST_DIR}/loading.cpp
${CMAKE_CURRENT_LIST_DIR}/splash_screen.cpp
${CMAKE_CURRENT_LIST_DIR}/subcontext.cpp
)

include(${CMAKE_CURRENT_LIST_DIR}/box/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/cinematic/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/dressing/CMakeLists.txt)