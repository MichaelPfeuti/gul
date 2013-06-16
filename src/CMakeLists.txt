set(MODULES algorithms
            base
            containers
            context
            image
            math
            memory
            persistance
            media)

add_library(gul SHARED $<TARGET_OBJECTS:algorithms>
                       $<TARGET_OBJECTS:base>
                       $<TARGET_OBJECTS:containers>
                       $<TARGET_OBJECTS:context>
                       $<TARGET_OBJECTS:image>
                       $<TARGET_OBJECTS:math>
                       $<TARGET_OBJECTS:memory>
                       $<TARGET_OBJECTS:persistance>
                       $<TARGET_OBJECTS:media>)

set(INCLUDE_DIRECTORIES "${INCLUDE}"
                        "${INCLUDE}/algorithms"
                        "${INCLUDE}/algorithms/analyzer"
                        "${INCLUDE}/algorithms/converter"
                        "${INCLUDE}/algorithms/filter"
                        "${INCLUDE}/algorithms/generator"
                        "${INCLUDE}/base"
                        "${INCLUDE}/containers"
                        "${INCLUDE}/context"
                        "${INCLUDE}/image"
                        "${INCLUDE}/math"
                        "${INCLUDE}/media"
                        "${INCLUDE}/media/manipulator"
                        "${INCLUDE}/memory"
                        "${INCLUDE}/persistance"
                        "${CMAKE_CURRENT_BINARY_DIR}")

generate_export_header(gul)

# process found libraries
if(FFMPEG_FOUND)
  set(DEFINITIONS ${DEFINITIONS} LIBFFMPEG_FOUND)
  include_directories(${FFMPEG_INCLUDE_DIR})
  target_link_libraries(gul ${FFMPEG_LIBRARIES})
endif()

if(PNG_FOUND)
  set(DEFINITIONS ${DEFINITIONS} LIBPNG_FOUND)
  include_directories(${PNG_INCLUDE_DIR})
  target_link_libraries(gul ${PNG_LIBRARIES})
endif()

if(JPEG_FOUND)
  set(DEFINITIONS ${DEFINITIONS} LIBJPEG_FOUND)
  include_directories(${JPEG_INCLUDE_DIR})
  target_link_libraries(gul ${JPEG_LIBRARIES})
endif()

if(TIFF_FOUND)
  set(DEFINITIONS ${DEFINITIONS} LIBTIFF_FOUND)
  include_directories(${TIFF_INCLUDE_DIR})
  target_link_libraries(gul ${TIFF_LIBRARIES})
endif()

if(OPENAL_FOUND)
  set(DEFINITIONS ${DEFINITIONS} LIBOPENAL_FOUND)
  include_directories(${OPENAL_INCLUDE_DIR})
  target_link_libraries(gul ${OPENAL_LIBRARY})
endif()

if(OPENGL_FOUND)
  set(DEFINITIONS ${DEFINITIONS} LIBOPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIR})
  target_link_libraries(gul ${OPENGL_LIBRARY})
endif()

if(GLFW_FOUND)
  set(DEFINITIONS ${DEFINITIONS} LIBGLFW_FOUND)
  include_directories(${GLFW_INCLUDE_DIR})
  target_link_libraries(gul ${GLFW_LIBRARY})
endif()

if(GLEW_FOUND)
  set(DEFINITIONS ${DEFINITIONS} LIBGLEW_FOUND)
  include_directories(${GLEW_INCLUDE_DIR})
  target_link_libraries(gul ${GLEW_LIBRARY})
endif()

# process modules (includes, definitions, ...)
foreach(MODULE IN LISTS MODULES)
  add_subdirectory(${MODULE})
  set_target_properties(${MODULE} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
  foreach(INCLUDE_DIRECTORY IN LISTS INCLUDE_DIRECTORIES)
    target_include_directories(${MODULE} PUBLIC ${INCLUDE_DIRECTORY})
  endforeach()
  foreach(DEFINITION IN LISTS DEFINITIONS)
    target_compile_definitions(${MODULE} PUBLIC ${DEFINITION})
  endforeach()
endforeach()

# cmake bugfix (object libs do not propagate their includes and defines)
foreach(INCLUDE_DIRECTORY IN LISTS INCLUDE_DIRECTORIES)
  target_include_directories(gul PUBLIC ${INCLUDE_DIRECTORY})
endforeach()
foreach(DEFINITION IN LISTS DEFINITIONS)
  target_compile_definitions(gul PUBLIC ${DEFINITION})
endforeach()
