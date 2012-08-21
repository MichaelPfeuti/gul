add_library(algorithms_converter STATIC
    ConverterImageToGrayscale.cpp
    ConverterImageToBW.cpp

    ${INCLUDE}/algorithms/converter/Converter.h
    ${INCLUDE}/algorithms/converter/ConverterImageToBW.h
    ${INCLUDE}/algorithms/converter/ConverterImageToGrayscale.h
		)

#target_link_libraries(base)
