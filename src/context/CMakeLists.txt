if(OPENAL_FOUND)
  set(CONTEXT_SOURCES ${CONTEXT_SOURCES}
                    ALContext.cpp
                    ALSource.cpp
                    CLContext.cpp
                    CLProgram.cpp
                    ContextErrorHandling.cpp
                    GLContext.cpp
                    GLProgram.cpp
                    ${INCLUDE}/context/ALContext.h
                    ${INCLUDE}/context/ALSource.h
                    ${INCLUDE}/context/CLContext.h
                    ${INCLUDE}/context/CLProgram.h
                    ${INCLUDE}/context/CLWorkgroup.h
                    ${INCLUDE}/context/ContextErrorHandling.h
                    ${INCLUDE}/context/GLContext.h
                    ${INCLUDE}/context/GLProgram.h
  )
endif()

add_library(context OBJECT ${CONTEXT_SOURCES})
