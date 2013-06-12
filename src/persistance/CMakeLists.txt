#######################
####### PUGIXML #######
#######################
set(XMLLIB_PATH "${LIBS_DIR}/pugixml/src")

string(REPLACE "-Wshadow"         " " PUGIXML_FLAGS "${CMAKE_CXX_FLAGS}")
string(REPLACE "-Wswitch-default" " " PUGIXML_FLAGS "${PUGIXML_FLAGS}")
string(REPLACE "-Weffc++"         " " PUGIXML_FLAGS "${PUGIXML_FLAGS}")

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

target_include_directories(persistance PRIVATE ${XMLLIB_PATH})
