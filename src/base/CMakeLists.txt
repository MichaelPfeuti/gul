add_library(base STATIC
		Assert.cpp
		String.cpp

    ${INCLUDE}/Assert.h
    ${INCLUDE}/String.h
    ${INCLUDE}/Misc.h
		)


target_link_libraries(base memory)
