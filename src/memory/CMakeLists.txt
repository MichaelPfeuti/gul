####################
#### Memory Lib ####
####################
add_library(memory STATIC
		ScopedPtr.cpp
		SharedPtr.cpp
		UniquePtr.cpp
		WeakPtr.cpp

    ${INCLUDE}/ScopedPtr.h
    ${INCLUDE}/SharedPtr.h
    ${INCLUDE}/UniquePtr.h
    ${INCLUDE}/WeakPtr.h
)
