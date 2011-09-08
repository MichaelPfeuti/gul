include_directories("${CMAKE_HOME_DIRECTORY}/tools/CTest")
add_definitions(-D_GUL_TESTING_ENABLED_)

add_subdirectory(base)
add_subdirectory(containers)
add_subdirectory(math)
add_subdirectory(memory)
add_subdirectory(persistance)
