add_library(algorithms_filter STATIC
    FilterImageToGrayscale.cpp
    FilterImageToBW.cpp

    ${INCLUDE}/algorithms/filter/Filter.h
    ${INCLUDE}/algorithms/filter/FilterImageToBW.h
    ${INCLUDE}/algorithms/filter/FilterImageToGrayscale.h
		)

#target_link_libraries(base)
