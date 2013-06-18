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

macro(add_library_if_found NAME)
  if(${NAME}_FOUND)
    set(DEFINITIONS ${DEFINITIONS} LIB${NAME}_FOUND)
    include_directories(${${NAME}_INCLUDE_DIR})
    target_link_libraries(gul ${${NAME}_LIBRARY})
  endif()
endmacro()

macro(add_libraries_if_found NAME)
  if(${NAME}_FOUND)
    set(DEFINITIONS ${DEFINITIONS} LIB${NAME}_FOUND)
    include_directories(${${NAME}_INCLUDE_DIR})
    target_link_libraries(gul ${${NAME}_LIBRARIES})
  endif()
endmacro()

# process found libraries
add_libraries_if_found(FFMPEG)
add_libraries_if_found(PNG)
add_libraries_if_found(JPEG)
add_libraries_if_found(TIFF)
add_library_if_found(OPENAL)
add_library_if_found(OPENCL)
add_libraries_if_found(OPENGL)
add_library_if_found(GLEW)
add_library_if_found(GLFW)

if(OPENMP_FOUND)
  set(DEFINITIONS ${DEFINITIONS} LIBOPENMP_FOUND)
  set(FLAGS ${FLAGS} ${OpenMP_CXX_FLAGS})
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
  foreach(FLAG IN LISTS FLAGS)
    set_target_properties(${MODULE} PROPERTIES COMPILE_FLAGS ${FLAG})
  endforeach()
endforeach()

# cmake bugfix (object libs do not propagate their includes and defines)
foreach(INCLUDE_DIRECTORY IN LISTS INCLUDE_DIRECTORIES)
  target_include_directories(gul PUBLIC ${INCLUDE_DIRECTORY})
endforeach()
foreach(DEFINITION IN LISTS DEFINITIONS)
  target_compile_definitions(gul PUBLIC ${DEFINITION})
endforeach()
foreach(FLAG IN LISTS FLAGS)
  set_target_properties(gul PROPERTIES COMPILE_FLAGS ${FLAG})
endforeach()
