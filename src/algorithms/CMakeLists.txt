add_library(algorithms OBJECT

    analyzer/AnalyzerImageEquality.cpp

    converter/ConverterImageToSBS.cpp

    filter/FilterImageToGrayscale.cpp
    filter/FilterImageToBW.cpp

    ${INCLUDE}/algorithms/Algorithm.h

    ${INCLUDE}/algorithms/analyzer/Analyzer.h
    ${INCLUDE}/algorithms/analyzer/AnalyzerImageEquality.h

    ${INCLUDE}/algorithms/converter/Converter.h
    ${INCLUDE}/algorithms/converter/ConverterImageToSBS.h

    ${INCLUDE}/algorithms/filter/Filter.h
    ${INCLUDE}/algorithms/filter/FilterImageToBW.h
    ${INCLUDE}/algorithms/filter/FilterImageToGrayscale.h
    )
