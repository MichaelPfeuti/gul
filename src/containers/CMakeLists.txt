add_library(containers SHARED 
		Array.cpp
		List.cpp
		Map.cpp
		Set.cpp
		Stack.cpp

    ${INCLUDE}/Array.h
    ${INCLUDE}/List.h
    ${INCLUDE}/Map.h
    ${INCLUDE}/Set.h
    ${INCLUDE}/Stack.h
		)
