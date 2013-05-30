add_subdirectory(algorithms)
add_subdirectory(base)
add_subdirectory(containers)
add_subdirectory(image)
add_subdirectory(math)
add_subdirectory(memory)
add_subdirectory(persistance)
add_subdirectory(media)

set_target_properties(algorithms  PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(base        PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(containers  PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(image       PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(math        PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(memory      PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(persistance PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(media       PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

add_library(gul SHARED $<TARGET_OBJECTS:algorithms>
                       $<TARGET_OBJECTS:base>
                       $<TARGET_OBJECTS:containers>
                       $<TARGET_OBJECTS:image>
                       $<TARGET_OBJECTS:math>
                       $<TARGET_OBJECTS:memory>
                       $<TARGET_OBJECTS:persistance>
                       $<TARGET_OBJECTS:media>)
generate_export_header(gul)

if(FFMPEG_FOUND)
  target_link_libraries(gul ${FFMPEG_LIBRARIES})
endif()

if(PNG_FOUND)
  target_link_libraries(gul ${PNG_LIBRARIES})
endif()

if(JPEG_FOUND)
  target_link_libraries(gul ${JPEG_LIBRARIES})
endif()

if(TIFF_FOUND)
  target_link_libraries(gul ${TIFF_LIBRARIES})
endif()


