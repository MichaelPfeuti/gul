
set(image_sources
    Image.cpp
    ImageFileHandler.cpp
    ImageIO.cpp
    BMP_IO.cpp
    RGBA.cpp

    ${INCLUDE}/image/Image.h
    ${INCLUDE}/image/ImageFileHandler.h
    ${INCLUDE}/image/ImageIO.h
    ${INCLUDE}/image/BMP_IO.h
    ${INCLUDE}/image/PPM_IO.h
    ${INCLUDE}/image/RGBA.h
    )

find_package(PNG)
find_package(JPEG)
find_package(TIFF)

if(PNG_FOUND)
  set(image_sources ${image_sources}
                    PNG_IO.cpp
                    ${INCLUDE}/image/PNG_IO.h
  )
  include_directories(${PNG_INCLUDE_DIR})
  set(image_libs ${image_libs} ${PNG_LIBRARIES})
endif(PNG_FOUND)

if(JPEG_FOUND)
  set(image_sources ${image_sources}
                    JPEG_IO.cpp
                    ${INCLUDE}/image/JPEG_IO.h
  )
  include_directories(${JPEG_INCLUDE_DIR})
set(image_libs ${image_libs} ${JPEG_LIBRARIES})
endif(JPEG_FOUND)

if(TIFF_FOUND)
  set(image_sources ${image_sources}
                    TIFF_IO.cpp
                    ${INCLUDE}/image/TIFF_IO.h
  )
  include_directories(${TIFF_INCLUDE_DIR})
set(image_libs ${image_libs} ${TIFF_LIBRARIES})
endif(TIFF_FOUND)


add_library(image STATIC ${image_sources})

target_link_libraries(image base ${image_libs})

