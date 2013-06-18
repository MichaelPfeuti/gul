# Locate the OpenCL library
# This module defines the following variables:
# OPENCL_LIBRARY, the name of the library;
# OPENCL_INCLUDE_DIR, where to find glfw include files.
# OPENCL_FOUND, true if both the OPENCL_LIBRARY and OPENCL_INCLUDE_DIR have been found.
#

#Search for the include file...
FIND_PATH(OPENCL_INCLUDE_DIR OpenCL/cl.h CL/cl.h
  PATHS
  /usr/include/
  /usr/local/include/
  /opt/AMDAPP/include/
)

FIND_LIBRARY(OPENCL_LIBRARY
  NAMES OpenCL
  PATHS
  /usr/local/lib/
  /usr/lib/
)

# handle the QUIETLY and REQUIRED arguments and set OPENCL_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OpenCL DEFAULT_MSG OPENCL_LIBRARY OPENCL_INCLUDE_DIR)

mark_as_advanced(OPENCL_LIBRARY OPENCL_INCLUDE_DIR)
