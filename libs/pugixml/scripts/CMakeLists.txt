project(pugixml)

cmake_minimum_required(VERSION 2.6)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared instead of static library")

set(SOURCES ../src/pugixml.hpp ../src/pugiconfig.hpp ../src/pugixml.cpp)

if(BUILD_SHARED_LIBS)
    add_library(pugixml SHARED ${SOURCES})
else()
    add_library(pugixml STATIC ${SOURCES})
endif()

set_target_properties(pugixml PROPERTIES VERSION 1.0 SOVERSION 1.0)

install(TARGETS pugixml LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(DIRECTORY ../src/ DESTINATION include/pugixml FILES_MATCHING PATTERN *.hpp)
