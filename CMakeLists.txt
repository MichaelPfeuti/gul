cmake_minimum_required(VERSION 2.8)

project(gul)

# cdash settings
enable_testing()
include(CTest)

if(BUILD_TESTING)
  set(BUILDNAME "${BUILDNAME}" CACHE STRING "gul")
  mark_as_advanced(BUILDNAME)
endif(BUILD_TESTING)

# build settings
set(CMAKE_CXX_FLAGS "-Wall -Werror -g -pg -std=c++0x")

# include files
set(INCLUDE "${CMAKE_HOME_DIRECTORY}/include")
include_directories("${INCLUDE}")

add_subdirectory(src)
add_subdirectory(test)
