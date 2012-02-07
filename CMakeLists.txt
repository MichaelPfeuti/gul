cmake_minimum_required(VERSION 2.8)

project(gul)

# cdash settings
include(CTest)

if(BUILD_TESTING)
  set(BUILDNAME "${BUILDNAME}" CACHE STRING "gul")
  mark_as_advanced(BUILDNAME)
endif(BUILD_TESTING)

macro(add_flags var)
  string(REPLACE "\n" " " _flags "${ARGN}")
  set(${var} "${${var}} ${_flags}")
endmacro(add_flags)

# build settings
add_flags(CMAKE_CXX_FLAGS "-std=c++0x -g -O0 -pg    -Wall
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
                                                    -Wwrite-strings                                           
                                                    -fprofile-arcs
                                                    -ftest-coverage")

set(CFLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
set(LDFLAGS "-fprofile-arcs -ftest-coverage")

# include files
set(INCLUDE_TPL "${CMAKE_HOME_DIRECTORY}/include/impl")
set(INCLUDE "${CMAKE_HOME_DIRECTORY}/include")
include_directories("${INCLUDE}")

add_subdirectory(src)
add_subdirectory(test)
