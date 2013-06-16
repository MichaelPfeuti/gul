############################################################################
##
## This file is part of gul (Graphic Utility Library).
##
## Copyright (c) 2012-2013 Michael Pfeuti.
##
## Contact: Michael Pfeuti (mpfeuti@ganymede.ch)
##
##
## gul is free software: you can redistribute it and/or modify it under the
## terms of the GNU Lesser General Public License as published by the Free
## Software Foundation, either version 3 of the License, or (at your option)
## any later version.
##
## gul is distributed in the hope that it will be useful, but WITHOUT ANY
## WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
## FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
## more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with gul. If not, see <http://www.gnu.org/licenses/>.
##
##
## If you have questions regarding the use of this file, please contact
## Michael Pfeuti at mpfeuti@ganymede.ch.
##
############################################################################

set(_gul_resource_path ${CMAKE_CURRENT_LIST_DIR})

function(gul_create_header FILE)

  if(NOT TARGET textToHeader)
    add_executable(textToHeader "${_gul_resource_path}/../resourceTools/textToHeader.cpp")
  endif()

  get_filename_component(FILENAME ${FILE} NAME_WE)
  get_filename_component(EXTENSION ${FILE} EXT)
  string(REGEX REPLACE "\\." "" EXTENSION ${EXTENSION})

  set(STRUCT_NAME "${FILENAME}_${EXTENSION}")
  set(OUTPUT_FILE "${FILENAME}_${EXTENSION}.h")
  set(OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/${OUTPUT_FILE}")

  add_custom_command(OUTPUT ${OUTPUT_PATH}
                     COMMAND textToHeader ${FILE} ${OUTPUT_PATH} ${STRUCT_NAME}
                     DEPENDS ${FILE}
                     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                     COMMENT "gul_create_header: Built ${OUTPUT_FILE} from ${FILE}")

endfunction()
