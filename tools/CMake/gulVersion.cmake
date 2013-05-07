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

set(_gul_version_path ${CMAKE_CURRENT_LIST_DIR})

function(gul_create_version)
	find_package(Git)

	execute_process(COMMAND "${GIT_EXECUTABLE}"	describe --dirty 
		              WORKING_DIRECTORY	"${PROJECT_SOURCE_DIR}"
		              OUTPUT_VARIABLE	VERSION_STRING
		              OUTPUT_STRIP_TRAILING_WHITESPACE)

	message(STATUS "${PROJECT_NAME} version: ${VERSION_STRING}")

	string(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR ${VERSION_STRING})
	string(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR ${VERSION_STRING})
	string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\-([0-9]+).*" "\\1" VERSION_PATCH ${VERSION_STRING})
	string(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\-[0-9]+-(.*)" "\\1" VERSION_SHA1 ${VERSION_STRING})

	set(${PROJECT_NAME}_VERSION_MAJOR  ${VERSION_MAJOR}  PARENT_SCOPE)
	set(${PROJECT_NAME}_VERSION_MINOR  ${VERSION_MINOR}  PARENT_SCOPE)
	set(${PROJECT_NAME}_VERSION_PATCH  ${VERSION_PATCH}  PARENT_SCOPE)
	set(${PROJECT_NAME}_VERSION_SHA1   ${VERSION_SHA1}   PARENT_SCOPE)
	set(${PROJECT_NAME}_VERSION_STRING ${VERSION_STRING} PARENT_SCOPE)

	configure_file(${_gul_version_path}/version.h.in
		             ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Version.h
                 @ONLY)
	include_directories(${CMAKE_CURRENT_BINARY_DIR})
endfunction()