add_library(containers SHARED 
    Array.cpp
    Container.cpp
    ContainerConstants.cpp
    List.cpp
    Map.cpp
    Set.cpp
    Stack.cpp

    ${INCLUDE_TPL}/containers/Array.hpp
    ${INCLUDE_TPL}/containers/List.hpp
    ${INCLUDE_TPL}/containers/Map.hpp
    ${INCLUDE_TPL}/containers/Set.hpp
    ${INCLUDE_TPL}/containers/Stack.hpp

    ${INCLUDE}/Array.h
    ${INCLUDE}/Container.h
    ${INCLUDE}/ContainerConstants.h
    ${INCLUDE}/List.h
    ${INCLUDE}/Map.h
    ${INCLUDE}/Set.h
    ${INCLUDE}/Stack.h
		)
