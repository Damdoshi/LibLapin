#################################################################################

 ###############################################################################
 ## Jason Brillante "Damdoshi"                                                ##
 ## Hanged Bunny Studio 2014-2018                                             ##
 ## "MyLib" V9.12                                                             ##
 ##                                                                           ##
 ## ------------------------------------------------------------------------- ##
 ## ------------------------------------ ---   -   --- ---- --  --   - --- -- ##
 ## ------------------------------------ ---- --- - -- --- - - - -- --  -- -- ##
 ## -----|\-//-------------------------- ---- ---   -- --- - -  --- -- - - -- ##
 ## -----||//___------------------------ ---- --- - -- ---   - ---- -- - - -- ##
 ## ----O  /    \----------------------- ---- --- - -- --- - - ---- -- --  -- ##
 ## ---<________/-----------------------   -   -   ---   - - - ---   - --- -- ##
 ## ------------------------------------------------------------------------- ##
 ##                                                                           ##
 ##                              - LibLapin -                                 ##
 ##                                                                           ##
 ###############################################################################

cmake_minimum_required (VERSION 3.5)
cmake_minimum_required (VERSION 3.5 FATAL_ERROR)

#################################################################################
## Information about the project                                               ##
#################################################################################

set(PROJECT_NAME lapin)

set(INSTALL_LIB_DIR lib)
set(INSTALL_INC_DIR include)

#################################################################################
## Building details                                                            ##
#################################################################################

# Flags ----------------------------------------------------------------------- #

set(COMPILE_CONFIGURATION
  -W -Wall -fPIC -std=c++11 -Wno-write-strings -Wno-unused-result -O2
  )

if (BUNNY_DEBUG)
  set(COMPILE_CONFIGURATION ${COMPILE_CONFIGURATION} -DBUNNY_DEBUG)
endif()

if (BUNNY_ALLOCATOR_ACTIVATED)

else()
  set(COMPILE_CONFIGURATION ${COMPILE_CONFIGURATION} -DBUNNY_ALLOCATOR_DEACTIVATED)
endif()

# Headers --------------------------------------------------------------------- #

set(HEADER_DIR
  ./include/ ./include/deps/ ./extlibs/headers/
  )

# Source ---------------------------------------------------------------------- #

file(
  GLOB_RECURSE
  SOURCES
  src/*
  )

# Libraries ------------------------------------------------------------------- #

file(
  GLOB_RECURSE
  LIBRARIES_HEADER
  ./extlibs/headers/*
  )

if (MSVC)
  # MSVC ON WINDOWS
  if (ARCH_32BITS)
    set(COMPILER msvc32)
  else()
    set(COMPILER msvc64)
  endif()
elseif (LINUX)
  # GCC ON LINUX
  if (ARCH_32BITS)
    set(COMPILER gcc32)
  else()
    set(COMPILER gcc64)
  endif()
else()
  # MINGW ON WINDOW
  if (ARCH_32BITS)
    set(COMPILER mingw32)
  else()
    set(COMPILER mingw64)
  endif()
endif()

file(
  GLOB_RECURSE
  LIBRARIES
  extlibs/${COMPILER}/*
  )

#################################################################################
## Rules                                                                       ##
#################################################################################

project(${PROJECT_NAME})
include_directories(${HEADER_DIR})
add_definitions(${COMPILE_CONFIGURATION})
add_library(${PROJECT_NAME} ${SOURCES})

file(
  GLOB
  LAPIN_DEPS
  include/deps/*.hpp
  )

file(
  GLOB
  LAPIN_HEADER
  include/lapin/*.h
  )

file(
  GLOB
  LAPIN_COMPAT
  include/lapin/compat/*.h
  )

file(
  GLOB
  LAPIN_CONTAINER
  include/lapin/container/*.h
  )

file(
  GLOB
  LAPIN_CONTEXT
  include/lapin/context/*.h
  )

# Static or dynamic library file
install (TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_LIB_DIR})

# Library dependencies header file and library files
install (FILES ${LIBRARIES} DESTINATION ${INSTALL_LIB_DIR})
install (FILES ${LIBRARIES_HEADER} DESTINATION ${INSTALL_INC_DIR})

# LibLapin headers
install (FILES include/lapin.h include/lapin_enum.h DESTINATION ${INSTALL_INC_DIR})
install (FILES ${LAPIN_DEPS} DESTINATION ${INSTALL_INC_DIR}/deps)
install (FILES ${LAPIN_HEADER} DESTINATION ${INSTALL_INC_DIR}/lapin)
install (FILES ${LAPIN_COMPAT} DESTINATION ${INSTALL_INC_DIR}/lapin/compat)
install (FILES ${LAPIN_CONTAINER} DESTINATION ${INSTALL_INC_DIR}/lapin/container)
install (FILES ${LAPIN_CONTEXT} DESTINATION ${INSTALL_INC_DIR}/lapin/context)

