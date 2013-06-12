cmake_minimum_required(VERSION 2.8.11)

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
endif()

find_package(JPEG)
if(JPEG_FOUND)
  add_definitions(-DLIBJPEG_FOUND)
  include_directories(${JPEG_INCLUDE_DIR})
endif()

find_package(TIFF)
if(TIFF_FOUND)
  add_definitions(-DLIBTIFF_FOUND)
  include_directories(${TIFF_INCLUDE_DIR})
endif()

find_package(OpenAL)
if(OPENAL_FOUND)
  add_definitions(-DLIBOPENAL_FOUND)
  include_directories(${OPENAL_INCLUDE_DIR})
endif()

# includes
set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(INCLUDE_TPL "${CMAKE_CURRENT_SOURCE_DIR}/include/impl")
set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(INCLUDE_DIRECTORIES "${INCLUDE}"
                        "${INCLUDE}/algorithms"
                        "${INCLUDE}/algorithms/analyzer"
                        "${INCLUDE}/algorithms/converter"
                        "${INCLUDE}/algorithms/filter"
                        "${INCLUDE}/algorithms/generator"
                        "${INCLUDE}/base"
                        "${INCLUDE}/containers"
                        "${INCLUDE}/context"
                        "${INCLUDE}/image"
                        "${INCLUDE}/math"
                        "${INCLUDE}/media"
                        "${INCLUDE}/media/manipulator"
                        "${INCLUDE}/memory"
                        "${INCLUDE}/persistance"
                        "${CMAKE_CURRENT_BINARY_DIR}/src")

foreach(INCLUDE_DIR IN LISTS INCLUDE_DIRECTORIES)
  include_directories(${INCLUDE_DIR})
endforeach()

# source files
if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)

add_subdirectory(src)

gul_create_cdash_target()
