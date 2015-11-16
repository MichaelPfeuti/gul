add_library(math OBJECT
    MathConstants.cpp
    Math.cpp

    ${INCLUDE_TPL}/math/Math.hpp
    ${INCLUDE_TPL}/math/Matrix.hpp

    ${INCLUDE}/math/Math.h
    ${INCLUDE}/math/Matrix.h
    ${INCLUDE}/math/MathConstants.h
    )
