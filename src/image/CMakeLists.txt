
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

find_package(PNG)
find_package(JPEG)
find_package(TIFF)

if(PNG_FOUND)
  set(image_sources ${image_sources}
                    ImageIO_PNG.cpp
                    ${INCLUDE}/image/ImageIO_PNG.h
  )
  add_definitions(-DLIBPNG_FOUND)
  include_directories(${PNG_INCLUDE_DIR})
  set(image_libs ${image_libs} ${PNG_LIBRARIES})
endif(PNG_FOUND)

if(JPEG_FOUND)
  set(image_sources ${image_sources}
                    ImageIO_JPEG.cpp
                    ${INCLUDE}/image/ImageIO_JPEG.h
  )
  add_definitions(-DLIBJPEG_FOUND)
  include_directories(${JPEG_INCLUDE_DIR})
set(image_libs ${image_libs} ${JPEG_LIBRARIES})
endif(JPEG_FOUND)

if(TIFF_FOUND)
  set(image_sources ${image_sources}
                    ImageIO_TIFF.cpp
                    ${INCLUDE}/image/ImageIO_TIFF.h
  )
  add_definitions(-DLIBTIFF_FOUND)
  include_directories(${TIFF_INCLUDE_DIR})
set(image_libs ${image_libs} ${TIFF_LIBRARIES})
endif(TIFF_FOUND)


add_library(image STATIC ${image_sources})

target_link_libraries(image base ${image_libs})

