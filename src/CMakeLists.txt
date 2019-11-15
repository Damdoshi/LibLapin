option(BUILD_STATIC "Build static lib" ON)
option(BUILD_SHARED "Build shared lib" ON)

file(GLOB SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/**/**/**/*.cpp
    ${PROJECT_SOURCE_DIR}/src/**/**/*.cpp
    ${PROJECT_SOURCE_DIR}/src/**/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

add_compile_options(
    -Wno-write-strings
    -Wno-unused-result
    -Wno-format-security
    -Wno-frame-address
    -Wno-narrowing
    -DBUNNY_ALLOCATOR_DEACTIVATED
    -DBUNNY_DEBUG
)

if(BUILD_SHARED)
    add_library(lapin SHARED ${SRC_FILES})
    set_property(TARGET lapin PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()
if(BUILD_STATIC)
    add_library(lapin-static STATIC ${SRC_FILES})
endif()
