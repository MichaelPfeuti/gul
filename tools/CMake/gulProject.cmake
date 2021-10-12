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

set(_gul_project_path ${CMAKE_CURRENT_LIST_DIR})

macro(gul_add_define VARIABLE)
  if(${VARIABLE})
    add_definitions(-D${VARIABLE})
  endif()
endmacro()

macro(gul_setup_project)

  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                        ${_gul_project_path})
  include(gulVersion)
  include(gulDoxygen)
  include(gulAStyle)
  include(gulTesting)
  include(gulCDash)
  include(gulResource)
  include(GenerateExportHeader)
  include(CMakeDependentOption)
  add_compiler_export_flags()

  # Default Build Type
  if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
  endif()

  # Common Build Settings
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -W ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wswitch-default ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-variable -Wunused-parameter -Wunused-function -Wunused ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-system-headers ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-strict-overflow ")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual ")


  # Debug Build Settings
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")

  # Assertion options
  option(GUL_ASSERTION "Enable Assertion also in non Debug builds. When BUILD_TESTING assert is always enabled." OFF)
  gul_add_define(GUL_ASSERTION)

  set(GUL_ASSERTION_MODE "ABORT" CACHE STRING "Assertion mode (ABORT, EXCEPTION, GUI)")
  set_property(CACHE GUL_ASSERTION_MODE PROPERTY STRINGS "ABORT" "EXCEPTION" "GUI")
  add_definitions(-DGUL_ASSERTION_${GUL_ASSERTION_MODE})

  # Logging options
  option(GUL_LOGGING "Enable Logging." ON)
  gul_add_define(GUL_LOGGING)

  if(GUL_LOGGING)
    set(GUL_LOGGING_LEVEL "WARNING" CACHE STRING "Logging level (DEBUG, INFO, WARNING, ERROR)")
    set_property(CACHE GUL_LOGGING_LEVEL PROPERTY STRINGS "DEBUG" "INFO" "WARNING" "ERROR")
    add_definitions(-DGUL_LOGGING_${GUL_LOGGING_LEVEL})

    set(GUL_LOGGING_MODE "CLI" CACHE STRING "Assertion mode (FILE, CLI, GUI)")
    set_property(CACHE GUL_LOGGING_MODE PROPERTY STRINGS "FILE" "CLI" "GUI")
    add_definitions(-DGUL_LOGGING_${GUL_LOGGING_MODE})
  else()
    unset(GUL_LOGGING_LEVEL CACHE)
    unset(GUL_LOGGING_MODE CACHE)
  endif()

endmacro()
