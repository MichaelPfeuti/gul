cmake_minimum_required(VERSION 2.8)

project (gul)

# cdash settings
enable_testing()
include(CTest)

if(BUILD_TESTING)
  set(BUILDNAME "${BUILDNAME}" CACHE STRING "gul")
  mark_as_advanced(BUILDNAME)
endif(BUILD_TESTING)

# tool paths
set (MEMLEAK_PATH "tools/nvwa-0.8.2/nvwa")
set (XMLLIB_PATH "tools/pugixml-1.0/src")

# build settings
set(CMAKE_CXX_FLAGS "-Wall -g -pg")

include_directories("include")
include_directories("${MEMLEAK_PATH}")
include_directories("${XMLLIB_PATH}")

add_subdirectory(src)

add_library(gul SHARED src/setup.h
	               ${MEMLEAK_PATH}/debug_new.cpp
         	       ${XMLLIB_PATH}/pugixml.cpp)
