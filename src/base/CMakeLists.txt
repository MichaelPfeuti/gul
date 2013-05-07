add_library(base OBJECT
    Assert.cpp
    ClassFactoryBase.cpp
    String.cpp
    SharedResource.cpp
    File.cpp
    RTTI.cpp
    Traits.cpp

    ${INCLUDE_TPL}/base/ClassFactory.hpp

    ${INCLUDE}/base/Assert.h
    ${INCLUDE}/base/Cloneable.h
    ${INCLUDE}/base/ClassFactory.h
    ${INCLUDE}/base/ClassFactoryBase.h
    ${INCLUDE}/base/String.h
    ${INCLUDE}/base/Misc.h
    ${INCLUDE}/base/NonCopyable.h
    ${INCLUDE}/base/NonCreatable.h
    ${INCLUDE}/base/SharedResource.h
    ${INCLUDE}/base/File.h
    ${INCLUDE}/base/RTTI.h
    ${INCLUDE}/base/Traits.h
    ${INCLUDE}/base/Timing.h
		)
