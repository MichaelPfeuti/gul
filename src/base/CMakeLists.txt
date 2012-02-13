add_library(base STATIC
		Assert.cpp
    ClassFactoryBase.cpp
		String.cpp
    RTTI.cpp

    ${INCLUDE_TPL}/base/ClassFactory.hpp

    ${INCLUDE}/Assert.h
    ${INCLUDE}/ClassFactory.h
    ${INCLUDE}/ClassFactoryBase.h
    ${INCLUDE}/String.h
    ${INCLUDE}/Misc.h
    ${INCLUDE}/NonCopyable.h
    ${INCLUDE}/NonCreatable.h
    ${INCLUDE}/RTTI.h
		)

target_link_libraries(base memory persistance)
