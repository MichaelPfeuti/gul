add_library(base STATIC
		Assert.cpp
    ClassFactory.cpp
		String.cpp

    ${INCLUDE}/Assert.h
    ${INCLUDE}/ClassFactory.h
    ${INCLUDE}/String.h
    ${INCLUDE}/Misc.h
    ${INCLUDE}/NonCopyable.h
		)

target_link_libraries(base memory)
