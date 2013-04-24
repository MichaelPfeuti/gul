cmake_minimum_required(VERSION 2.8)

project(gul)
include(tools/CMake/gulProject.cmake)

gul_setup_project()
gul_setup_testing()
gul_create_version()
gul_create_astyle_target()
gul_create_doxygen_target()


# include files
set(INCLUDE_TPL "${CMAKE_HOME_DIRECTORY}/include/impl")
set(INCLUDE "${CMAKE_HOME_DIRECTORY}/include")
include_directories("${INCLUDE}")
include_directories("${CMAKE_HOME_DIRECTORY}/include/algorithms")
include_directories("${CMAKE_HOME_DIRECTORY}/include/algorithms/analyzer")
include_directories("${CMAKE_HOME_DIRECTORY}/include/algorithms/converter")
include_directories("${CMAKE_HOME_DIRECTORY}/include/algorithms/filter")
include_directories("${CMAKE_HOME_DIRECTORY}/include/algorithms/generator")
include_directories("${CMAKE_HOME_DIRECTORY}/include/base")
include_directories("${CMAKE_HOME_DIRECTORY}/include/containers")
include_directories("${CMAKE_HOME_DIRECTORY}/include/image")
include_directories("${CMAKE_HOME_DIRECTORY}/include/math")
include_directories("${CMAKE_HOME_DIRECTORY}/include/memory")
include_directories("${CMAKE_HOME_DIRECTORY}/include/persistance")
include_directories("${CMAKE_HOME_DIRECTORY}/include/video")
include_directories("${CMAKE_HOME_DIRECTORY}/include/video/manipulator")

# source files
if(BUILD_TESTING)
  add_definitions("-DBUILD_TESTING")
  add_subdirectory(test)
endif(BUILD_TESTING)

add_subdirectory(src)

gul_create_cdash_target()
