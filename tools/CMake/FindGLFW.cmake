# Locate the glfw library
# This module defines the following variables:
# GLFW_LIBRARY, the name of the library;
# GLFW_INCLUDE_DIR, where to find glfw include files.
# GLFW_FOUND, true if both the GLFW_LIBRARY and GLFW_INCLUDE_DIR have been found.
#
# To help locate the library and include file, you could define an environment variable called
# GLFW_ROOT which points to the root of the glfw library installation. This is pretty useful
# on a Windows platform.
#
#
# Usage example to compile an "executable" target to the glfw library:
#
# FIND_PACKAGE (glfw REQUIRED)
# INCLUDE_DIRECTORIES (${GLFW_INCLUDE_DIR})RARY_DIR})
# ADD_EXECUTABLE (executable ${EXECUTABLE_SRCS})
# TARGET_LINK_LIBRARIES (executable ${GLFW_LIBRARY})
#

#Search for the include file...
FIND_PATH(GLFW_INCLUDE_DIR GL/glfw.h
  HINTS
  $ENV{GLFW_ROOT}
  PATH_SUFFIX include
  PATHS
  /usr/include/
  /usr/local/include/
)

FIND_LIBRARY(GLFW_LIBRARY
  NAMES glfw
  HINTS
  $ENV{GLFW_ROOT}
  PATH_SUFFIXES lib/win32
  PATHS
  /usr/local/lib
  /usr/lib
)

# handle the QUIETLY and REQUIRED arguments and set OPENAL_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLFW DEFAULT_MSG GLFW_LIBRARY GLFW_INCLUDE_DIR)

mark_as_advanced(GLFW_LIBRARY GLFW_INCLUDE_DIR)


