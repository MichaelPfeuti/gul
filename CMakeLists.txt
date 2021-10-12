cmake_minimum_required(VERSION 3.21.0)

project(gul)
include(tools/CMake/gulProject.cmake)

gul_setup_project()
gul_setup_testing("${CMAKE_CURRENT_SOURCE_DIR}/test/data")
gul_create_version()
gul_create_astyle_target()
gul_create_doxygen_target()

# find libraries
find_package(FFMPEG)
find_package(PNG)
find_package(JPEG)
find_package(TIFF)
find_package(OpenAL)
find_package(OpenCL)
find_package(OpenGL)
find_package(OpenMP)
find_package(GLFW)
find_package(GLEW)

# includes
set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")
set(INCLUDE_TPL "${CMAKE_CURRENT_SOURCE_DIR}/include/impl")
set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# source files
if(BUILD_TESTING)
  add_subdirectory(test)
endif(BUILD_TESTING)

add_subdirectory(src)

gul_create_cdash_target()
