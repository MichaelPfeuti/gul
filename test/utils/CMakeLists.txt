add_library(gulTestUtils SHARED

              UtilsCDash.h
              UtilsImage.h

              UtilsCDash.cpp
              UtilsImage.cpp
            )

target_link_libraries(gulTestUtils gul)
