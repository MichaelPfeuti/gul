if(OPENAL_FOUND)
  set(CONTEXT_SOURCES ${CONTEXT_SOURCES}
                    ContextAL.cpp
                    ${INCLUDE}/context/ContextAL.h
  )
endif()

add_library(context OBJECT ${CONTEXT_SOURCES})
