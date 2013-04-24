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

function(gul_setup_project)

  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} 
                        ${_gul_project_path})
  include(gulVersion)
  include(gulDoxygen)
  include(gulAStyle)
  include(gulTesting)

	# Default Build Type
	if(NOT CMAKE_BUILD_TYPE)
  	set(CMAKE_BUILD_TYPE Release CACHE STRING
  	    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
  	    FORCE)
	endif()

  macro(add_flags var)
    string(REPLACE "\n" " " _flags "${ARGN}")
    set(${var} "${${var}} ${_flags}")
  endmacro(add_flags)

	# Common Build Settings
	add_flags(CMAKE_CXX_FLAGS "-std=c++0x -Wall
		                                    -Wextra
		                                    -W
		                                    -Wswitch-default
		                                    -Wshadow
		                                    -Wunused-variable
		                                    -Wunused-parameter
		                                    -Wunused-function
		                                    -Wunused
		                                    -Wno-system-headers
		                                    -Wno-deprecated
		                                    -Woverloaded-virtual
		                                    -Wwrite-strings")
		                                   #-Weffc++

	# Debug Build Settings
	add_flags(CMAKE_CXX_FLAGS_DEBUG "-fprofile-arcs -ftest-coverage")
	add_flags(CMAKE_C_FLAGS_DEBUG "-fprofile-arcs -ftest-coverage")
	add_flags(CMAKE_EXE_LINKER_FLAGS_DEBUG "-fprofile-arcs -ftest-coverage")

endfunction()
