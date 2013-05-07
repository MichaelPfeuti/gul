
set(image_sources
    ImageFileHandler.cpp
    ImageIO.cpp
    ImageIO_PPM.cpp

    ${INCLUDE_TPL}/image/Image.hpp

    ${INCLUDE}/image/Image.h
    ${INCLUDE}/image/ImageFileHandler.h
    ${INCLUDE}/image/ImageIO.h
    ${INCLUDE}/image/ImageIO_PPM.h
    )

if(PNG_FOUND)
  set(image_sources ${image_sources}
                    ImageIO_PNG.cpp
                    ${INCLUDE}/image/ImageIO_PNG.h
  )
endif(PNG_FOUND)

if(JPEG_FOUND)
  set(image_sources ${image_sources}
                    ImageIO_JPEG.cpp
                    ${INCLUDE}/image/ImageIO_JPEG.h
  )
endif(JPEG_FOUND)

if(TIFF_FOUND)
  set(image_sources ${image_sources}
                    ImageIO_TIFF.cpp
                    ${INCLUDE}/image/ImageIO_TIFF.h
  )
endif(TIFF_FOUND)


add_library(image OBJECT ${image_sources})
