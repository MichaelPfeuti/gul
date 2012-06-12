add_library(math STATIC
    MathConstants.cpp
    Math.cpp

    ${INCLUDE_TPL}/math/Math.hpp

    ${INCLUDE}/math/Math.h
    ${INCLUDE}/math/MathConstants.h
    )
