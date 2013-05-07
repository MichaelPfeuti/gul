#######################
####### PUGIXML #######
#######################
set(XMLLIB_PATH "${CMAKE_HOME_DIRECTORY}/libs/pugixml/src")

include_directories("${XMLLIB_PATH}")

string(REPLACE "-Wshadow"         " " PUGIXML_FLAGS "${CMAKE_CXX_FLAGS}")
string(REPLACE "-Wswitch-default" " " PUGIXML_FLAGS "${PUGIXML_FLAGS}")
string(REPLACE "-Weffc++"         " " PUGIXML_FLAGS "${PUGIXML_FLAGS}")

#set(LOCAL_CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

#set(CMAKE_CXX_FLAGS "")

set_source_files_properties(${XMLLIB_PATH}/pugixml.cpp PROPERTIES COMPILE_FLAGS "${PUGIXML_FLAGS}")


###########################
##### Persistance Lib #####
###########################
add_library(persistance OBJECT
    SettingsManager.cpp
    XMLSerializable.cpp
    XMLNode.cpp
    XMLDocument.cpp
    XMLAttribute.cpp

    ${INCLUDE_TPL}/persistance/XMLManager.hpp


    ${INCLUDE}/persistance/SettingsManager.h
    ${INCLUDE}/persistance/XMLSerializable.h
    ${INCLUDE}/persistance/XMLManager.h
    ${INCLUDE}/persistance/XMLMacros.h
    ${INCLUDE}/persistance/XMLNode.h
    ${INCLUDE}/persistance/XMLDocument.h
    ${INCLUDE}/persistance/XMLAttribute.h

    ${XMLLIB_PATH}/pugixml.cpp
)

#set_target_properties(persistance PROPERTIES COMPILE_FLAGS "${LOCAL_CMAKE_CXX_FLAGS}")
