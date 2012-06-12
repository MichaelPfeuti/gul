add_library(containers STATIC
    Array.cpp
    ArrayBasic.cpp
    ContainerConstants.cpp
    List.cpp
    ListBasic.cpp
    Map.cpp
    MapBasic.cpp
    Set.cpp
    SetBasic.cpp
    Stack.cpp
    StackBasic.cpp

    ${INCLUDE_TPL}/containers/Array.hpp
    ${INCLUDE_TPL}/containers/ArrayBasic.hpp
    ${INCLUDE_TPL}/containers/List.hpp
    ${INCLUDE_TPL}/containers/ListBasic.hpp
    ${INCLUDE_TPL}/containers/Map.hpp
    ${INCLUDE_TPL}/containers/MapBasic.hpp
    ${INCLUDE_TPL}/containers/Set.hpp
    ${INCLUDE_TPL}/containers/SetBasic.hpp
    ${INCLUDE_TPL}/containers/Stack.hpp
    ${INCLUDE_TPL}/containers/StackBasic.hpp

    ${INCLUDE}/containers/Array.h
    ${INCLUDE}/containers/ArrayBasic.h
    ${INCLUDE}/containers/ContainerConstants.h
    ${INCLUDE}/containers/List.h
    ${INCLUDE}/containers/ListBasic.h
    ${INCLUDE}/containers/Map.h
    ${INCLUDE}/containers/MapBasic.h
    ${INCLUDE}/containers/Set.h
    ${INCLUDE}/containers/SetBasic.h
    ${INCLUDE}/containers/Stack.h
    ${INCLUDE}/containers/StackBasic.h
		)
