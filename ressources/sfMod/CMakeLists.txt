cmake_minimum_required( VERSION 2.8 )

project( sfMod )

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE )
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

set( BUILD_SHARED false CACHE BOOL "Build a shared library." )

if( BUILD_SHARED )
	set( LIB_TYPE SHARED )
else()
	set( LIB_TYPE STATIC )
endif()

set( SFML_COMPONENTS ${SFML_COMPONENTS} AUDIO SYSTEM GRAPHICS WINDOW)

find_package( ModPlug REQUIRED )
find_package( SFML 2.0 REQUIRED COMPONENTS ${SFML_COMPONENTS} )

set( INC_DIR "include" )
set( SRC_DIR "src" )

set(
	SOURCES
	${SRC_DIR}/sfMod/sfMod.cpp
)

set(
  HEADERS
	${INC_DIR}/sfMod.h
	${INC_DIR}/sfMod/Error.h
)

include_directories( ${INC_DIR} )
include_directories( ${INC_DIR}/sfMod )

include_directories( ${MODPLUG_INCLUDE_DIR} )
include_directories( ${SFML_INCLUDE_DIR} )

add_library( sfMod ${LIB_TYPE} ${SOURCES} )

target_link_libraries( sfMod ${MODPLUG_LIBRARY} )
target_link_libraries( sfMod ${SFML_AUDIO_LIBRARY} )
target_link_libraries( sfMod ${SFML_SYSTEM_LIBRARY} )

if( BUILD_SHARED )
	set_target_properties( sfMod PROPERTIES DEBUG_POSTFIX -d )
else()
	set_target_properties( sfMod PROPERTIES DEBUG_POSTFIX -s-d )
	set_target_properties( sfMod PROPERTIES RELEASE_POSTFIX -s )
	set_target_properties( sfMod PROPERTIES MINSIZEREL_POSTFIX -s )
endif()

# Build test/main.cpp

message("!!!!!!!!! ${SFML_LIBRARIES}")
set(EXECUTABLE_NAME sfmod-test)
add_executable(${EXECUTABLE_NAME} test/main.cpp)
target_link_libraries( sfmod-test ${SFML_LIBRARIES} ${MODPLUG_LIBRARY} sfMod)
file(COPY "test/bg.png" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "test/rainysum.mod" DESTINATION ${CMAKE_BINARY_DIR})

# Installing

install(
	DIRECTORY include
	DESTINATION .
)

install(
	FILES license.txt
	DESTINATION .
)

install(
	FILES readme.txt
	DESTINATION .
)

if(WIN32)
	install(
		TARGETS sfMod
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
	)
else()
	install(
		TARGETS sfMod
		RUNTIME DESTINATION lib
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
	)
endif()
