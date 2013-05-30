cmake_minimum_required(VERSION 2.8)

project(gul)
include(tools/CMake/gulProject.cmake)

gul_setup_project()
gul_setup_testing()
gul_create_version()
gul_create_astyle_target()
gul_create_doxygen_target()

# find libraries
find_package(FFMPEG)
if(FFMPEG_FOUND)
  add_definitions(-DLIBFFMPEG_FOUND)
  include_directories(${FFMPEG_INCLUDE_DIR})
endif()

find_package(PNG)
if(PNG_FOUND)
  add_definitions(-DLIBPNG_FOUND)
  include_directories(${PNG_INCLUDE_DIR})
endif(PNG_FOUND)

find_package(JPEG)
if(JPEG_FOUND)
  add_definitions(-DLIBJPEG_FOUND)
  include_directories(${JPEG_INCLUDE_DIR})
endif(JPEG_FOUND)

find_package(TIFF)
if(TIFF_FOUND)
  add_definitions(-DLIBTIFF_FOUND)
  include_directories(${TIFF_INCLUDE_DIR})
endif(TIFF_FOUND)


# include files
set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(INCLUDE_TPL "${CMAKE_CURRENT_SOURCE_DIR}/include/impl")
set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${INCLUDE}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/algorithms")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/algorithms/analyzer")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/algorithms/converter")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/algorithms/filter")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/algorithms/generator")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/base")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/containers")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/image")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/math")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/memory")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/persistance")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/media")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/media/manipulator")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/src")

# source files
if(BUILD_TESTING)
  add_definitions("-DBUILD_TESTING")
  add_subdirectory(test)
endif(BUILD_TESTING)

add_subdirectory(src)

gul_create_cdash_target()
