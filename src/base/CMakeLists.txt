add_library(base OBJECT
    Assert.cpp
    ClassFactoryBase.cpp
    Dir.cpp
    File.cpp
    Log.cpp
    RTTI.cpp
    SharedResource.cpp
    String.cpp
    Timing.cpp
    Traits.cpp

    ${INCLUDE_TPL}/base/ClassFactory.hpp
    ${INCLUDE_TPL}/base/Traits.hpp

    ${INCLUDE}/base/Assert.h
    ${INCLUDE}/base/ClassFactoryBase.h
    ${INCLUDE}/base/ClassFactory.h
    ${INCLUDE}/base/Cloneable.h
    ${INCLUDE}/base/Dir.h
    ${INCLUDE}/base/File.h
    ${INCLUDE}/base/Log.h
    ${INCLUDE}/base/Misc.h
    ${INCLUDE}/base/NonCopyable.h
    ${INCLUDE}/base/NonCreatable.h
    ${INCLUDE}/base/NullObject.h
    ${INCLUDE}/base/RTTI.h
    ${INCLUDE}/base/SharedResource.h
    ${INCLUDE}/base/String.h
    ${INCLUDE}/base/Timing.h
    ${INCLUDE}/base/Traits.h
    )
