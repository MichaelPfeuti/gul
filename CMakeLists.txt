cmake_minimum_required(VERSION 2.8)

project(gul)

# cdash settings
include(CTest)

#if(BUILD_TESTING)
#  set(BUILDNAME "${BUILDNAME}" CACHE STRING "gul")
#  mark_as_advanced(BUILDNAME)
#endif(BUILD_TESTING)

macro(add_flags var)
  string(REPLACE "\n" " " _flags "${ARGN}")
  set(${var} "${${var}} ${_flags}")
endmacro(add_flags)

# Common Build Settings
add_flags(CMAKE_CXX_FLAGS_COMMON "-std=c++0x -Wall
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
                                             #-Weffc++

# Default Build Settings
add_flags(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_COMMON})
add_flags(CMAKE_CXX_FLAGS "-g -O0 -pg")
add_flags(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS_COMMON})
add_flags(CMAKE_C_FLAGS "-g -O0 -pg")

# Debug Build Settings
add_flags(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_COMMON})
add_flags(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -pg")
add_flags(CMAKE_C_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_COMMON})
add_flags(CMAKE_C_FLAGS_DEBUG "-g -O0 -pg")

# Release Build Settings
add_flags(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_COMMON})
add_flags(CMAKE_CXX_FLAGS "-O3")
add_flags(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS_COMMON})
add_flags(CMAKE_C_FLAGS "-O3")


add_flags(LDFLAGS_DEBUG "-fprofile-arcs -ftest-coverage")

# include files
set(INCLUDE_TPL "${CMAKE_HOME_DIRECTORY}/include/impl")
set(INCLUDE "${CMAKE_HOME_DIRECTORY}/include")
include_directories("${INCLUDE}")

add_subdirectory(src)
add_subdirectory(test)
