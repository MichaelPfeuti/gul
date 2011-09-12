add_library(containers SHARED 
    ContainerConstants.cpp

    Array.hpp
    Container.hpp
    List.hpp
    Map.hpp
    Set.hpp
    Stack.hpp

    ${INCLUDE}/Array.h
    ${INCLUDE}/Container.h
    ${INCLUDE}/ContainerConstants.h
    ${INCLUDE}/List.h
    ${INCLUDE}/Map.h
    ${INCLUDE}/Set.h
    ${INCLUDE}/Stack.h
		)
