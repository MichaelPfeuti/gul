set(XMLLIB_PATH "${CMAKE_HOME_DIRECTORY}/libs/pugixml-1.0/src")

include_directories("${XMLLIB_PATH}")

add_library(persistance SHARED
		SettingsManager.cpp
    ${XMLLIB_PATH}/pugixml.cpp

    XMLLoader.hpp
    XMLSaver.hpp

    ${INCLUDE}/SettingsManager.h
    ${INCLUDE}/XMLLoader.h
    ${INCLUDE}/XMLSaver.h
		)
