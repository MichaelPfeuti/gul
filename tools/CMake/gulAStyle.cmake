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

set(_gul_astyle_path ${CMAKE_CURRENT_LIST_DIR})

function(gul_create_astyle_target)
	find_package(AStyle)
	if(NOT TARGET CodingConventions AND  ASTYLE_FOUND)
     if(ARGV1)
       set(ASTYLE_CONFIG ${ARGV1})
     else()
       set(ASTYLE_CONFIG "${_gul_astyle_path}/../astyle.conf")
     endif()
       add_custom_target(CodingConventions 
                   COMMAND cmake -DASTYLE_EXECUTABLE=${ASTYLE_EXECUTABLE}
                   -DASTYLE_CONFIG=${ASTYLE_CONFIG}
                   -P ${_gul_astyle_path}/AStyle.cmake
                   COMMENT "AStyle"
                   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                   )
	endif()
endfunction()