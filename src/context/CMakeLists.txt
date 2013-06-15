if(OPENAL_FOUND)
  set(CONTEXT_SOURCES ${CONTEXT_SOURCES}
                    ALContext.cpp
                    ALSource.cpp
                    CLContext.cpp
                    GLContext.cpp
                    ${INCLUDE}/context/ALContext.h
                    ${INCLUDE}/context/ALSource.h
                    ${INCLUDE}/context/CLContext.h
                    ${INCLUDE}/context/GLContext.h
  )
endif()

add_library(context OBJECT ${CONTEXT_SOURCES})
