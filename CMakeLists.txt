cmake_minimum_required(VERSION 2.8)

project(gul)

# cdash settings
include(CTest)

macro(add_flags var)
  string(REPLACE "\n" " " _flags "${ARGN}")
  set(${var} "${${var}} ${_flags}")
endmacro(add_flags)

# Common Build Settings
add_flags(CMAKE_CXX_FLAGS "-std=c++0x -Wall
                                      -Wextra
                                      -W
                                      -Wswitch-default
                                      -Wshadow
                                      -Wunused-variable
                                      -Wunused-parameter
                                      -Wunused-function
                                      -Wunused
                                      -Wno-system-headers
                                      -Wno-deprecated
                                      -Woverloaded-virtual
                                      -Wwrite-strings")
                                     #-Weffc++

# Debug Build Settings
add_flags(CMAKE_CXX_FLAGS_DEBUG "-pg -fprofile-arcs -ftest-coverage")
add_flags(CMAKE_C_FLAGS_DEBUG "-pg -fprofile-arcs -ftest-coverage")
add_flags(LDFLAGS_DEBUG "-fprofile-arcs -ftest-coverage")

# Doxygen
find_package(Doxygen)

if(DOXYGEN_FOUND)
  add_custom_target(doxygen 
    COMMAND ${DOXYGEN_EXECUTABLE}
    COMMENT "Doxygen"
    WORKING_DIRECTORY "${CMAKE_HOME_DIRECTORY}/doc"
    )
endif(DOXYGEN_FOUND)

# include files
set(INCLUDE_TPL "${CMAKE_HOME_DIRECTORY}/include/impl")
set(INCLUDE "${CMAKE_HOME_DIRECTORY}/include")
include_directories("${INCLUDE}")


if(BUILD_TESTING)
  add_flags(CMAKE_CXX_FLAGS "-DBUILD_TESTING")
  add_subdirectory(test)
endif(BUILD_TESTING)

add_subdirectory(src)

