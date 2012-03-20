############################################################################
##
## This file is part of gul (Graphic Utility Library).
##
## Copyright (c) 2012 Michael Pfeuti.
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

# find AStyle application
find_program(ASTYLE_EXECUTABLE astyle)
if(NOT ASTYLE_EXECUTABLE)
  message(STATUS "ASTYLE_EXECUTABLE was not found. Please set manually for format testing.")
else(NOT ASTYLE_EXECUTABLE)
  set(ASTYLE_FOUND 1)
endif(NOT ASTYLE_EXECUTABLE)

# macro that searches for all c++ files recursively and test if the meet the coding convention
function(astyle_check)
  
  if(ASTYLE_EXECUTABLE)

    # Scan for files to check
    file(GLOB_RECURSE FILES_FOUND_TO_CHECK "*.h")
    set(FILES_TO_SYTLE_CHECK ${FILES_FOUND_TO_CHECK})

    file(GLOB_RECURSE FILES_FOUND_TO_CHECK "*.hpp")
    list(APPEND FILES_TO_SYTLE_CHECK ${FILES_FOUND_TO_CHECK})

    file(GLOB_RECURSE FILES_FOUND_TO_CHECK "*.cpp")
    list(APPEND FILES_TO_SYTLE_CHECK ${FILES_FOUND_TO_CHECK})
    
    # loop over all found file and check them
    set(ASTYLE_ARG "--options=../tools/astyle.conf")
    foreach(CHECK_FILE IN LISTS FILES_TO_SYTLE_CHECK)
      execute_process(COMMAND ${ASTYLE_EXECUTABLE} ${ASTYLE_ARG}
                      INPUT_FILE ${CHECK_FILE}
                      OUTPUT_VARIABLE FORMATED_CODE
                      RESULT_VARIABLE RETVAL)
                    
      if(${RETVAL})
      	message(FATAL_ERROR "Format Checking FAILED!\n\t${ASTYLE_EXECUTABLE} --options=tools/astyle.conf < ${CHECK_FILE}")
      endif(${RETVAL})

      file(READ ${CHECK_FILE} CHECK_FILE_CONTENT)
      
      if(NOT (FORMATED_CODE STREQUAL CHECK_FILE_CONTENT))
      	message("Warning: ${CHECK_FILE} does not meet the Coding Conventions")
      endif(NOT (FORMATED_CODE STREQUAL CHECK_FILE_CONTENT))
    
    endforeach(CHECK_FILE IN LISTS FILES_TO_SYTLE_CHECK)
    
  else(ASTYLE_EXECUTABLE)
  
    message(FATAL_ERROR "ASTYLE_EXECUTABLE was not found. Please specify for format testing.")
  
  endif(ASTYLE_EXECUTABLE)
endfunction(astyle_check)
