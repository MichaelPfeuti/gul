include_directories("${CMAKE_HOME_DIRECTORY}/tools/CTest")
include("${CMAKE_HOME_DIRECTORY}/tools/CTest/CTestMacros.cmake")

add_subdirectory(base)
add_subdirectory(containers)
add_subdirectory(math)
add_subdirectory(memory)
add_subdirectory(persistance)
