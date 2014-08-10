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

set(_gul_testing_path ${CMAKE_CURRENT_LIST_DIR})

macro(gul_setup_testing TEST_DATA_FODLER)
  include(CTest)
  include_directories(${_gul_testing_path})
  include(CTestMacros)

  # Header to access the temporary data folder (required by the testing framework)
  set(GUL_TEST_DATA_SET_FOLDER ${TEST_DATA_FODLER})
  set(GUL_TEST_TEMP_FOLDER "${CMAKE_BINARY_DIR}/TestOutput")
  file(MAKE_DIRECTORY ${GUL_TEST_TEMP_FOLDER})
  configure_file(${_gul_testing_path}/CTestData.h.in
                 ${CMAKE_CURRENT_BINARY_DIR}/CTestData.h
                 @ONLY])
  include_directories(${CMAKE_CURRENT_BINARY_DIR})

  # CDash upload code (this is automatically used in the testing framework)
  if(NOT TARGET gulTestingUtils)
    add_library(gulTestingUtils SHARED ${_gul_resource_path}/CTestCDash.cpp)
    target_link_libraries(gulTestingUtils gul)
  endif()

  if(BUILD_TESTING)
    add_definitions("-DGUL_ASSERTION")
  endif()
endmacro()
