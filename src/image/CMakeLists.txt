add_library(image STATIC
    Image.cpp
    
    ${INCLUDE}/image/Image.h
    )

target_link_libraries(image base)
