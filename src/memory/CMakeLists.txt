add_library(memory STATIC
		ScopedPtr.cpp
		SharedPtr.cpp
		UniquePtr.cpp
		WeakPtr.cpp

    ${INCLUDE}/memory/ScopedPtr.h
    ${INCLUDE}/memory/SharedPtr.h
    ${INCLUDE}/memory/UniquePtr.h
    ${INCLUDE}/memory/WeakPtr.h
)
