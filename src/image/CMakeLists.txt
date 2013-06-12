
set(IMAGE_SOURCES
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
  set(IMAGE_SOURCES ${IMAGE_SOURCES}
                    ImageIO_PNG.cpp
                    ${INCLUDE}/image/ImageIO_PNG.h
  )
endif()

if(JPEG_FOUND)
  set(IMAGE_SOURCES ${IMAGE_SOURCES}
                    ImageIO_JPEG.cpp
                    ${INCLUDE}/image/ImageIO_JPEG.h
  )
endif()

if(TIFF_FOUND)
  set(IMAGE_SOURCES ${IMAGE_SOURCES}
                    ImageIO_TIFF.cpp
                    ${INCLUDE}/image/ImageIO_TIFF.h
  )
endif()


add_library(image OBJECT ${IMAGE_SOURCES})
