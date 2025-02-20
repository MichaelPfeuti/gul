/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2015 Michael Pfeuti.
**
** Contact: Michael Pfeuti (mpfeuti@ganymede.ch)
**
**
** gul is free software: you can redistribute it and/or modify it under the
** terms of the GNU Lesser General Public License as published by the Free
** Software Foundation, either version 3 of the License, or (at your option)
** any later version.
**
** gul is distributed in the hope that it will be useful, but WITHOUT ANY
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
** more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with gul. If not, see <http://www.gnu.org/licenses/>.
**
**
** If you have questions regarding the use of this file, please contact
** Michael Pfeuti at mpfeuti@ganymede.ch.
**
***************************************************************************/

#include "ContextErrorHandling.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <AL/al.h>
#include "Log.h"

bool gul::alCheckError(const char* message)
{
  ALenum error = alGetError();
  if(error != AL_NO_ERROR)
  {
    \
    GUL_LOG_WARNING("OpenAL Error (code %d): %s", error, message);
    return false;
  }
  return true;
}

bool gul::glCheckError(const char* message)
{
  GLenum glError;
  if((glError = glGetError()) != GL_NO_ERROR)
  {
    GUL_LOG_WARNING("OpenGL Error (code %d: %s): %s", glError, gluErrorString(glError), message);
    return false;
  }
  return true;
}


static const char* clErrorToString(cl_int err)
{
  switch(err)
  {
    case CL_SUCCESS:                         return "Success!";
    case CL_DEVICE_NOT_FOUND:                return "Device not found.";
    case CL_DEVICE_NOT_AVAILABLE:            return "Device not available";
    case CL_COMPILER_NOT_AVAILABLE:          return "Compiler not available";
    case CL_MEM_OBJECT_ALLOCATION_FAILURE:   return "Memory object allocation failure";
    case CL_OUT_OF_RESOURCES:                return "Out of resources";
    case CL_OUT_OF_HOST_MEMORY:              return "Out of host memory";
    case CL_PROFILING_INFO_NOT_AVAILABLE:    return "Profiling information not available";
    case CL_MEM_COPY_OVERLAP:                return "Memory copy overlap";
    case CL_IMAGE_FORMAT_MISMATCH:           return "Image format mismatch";
    case CL_IMAGE_FORMAT_NOT_SUPPORTED:      return "Image format not supported";
    case CL_BUILD_PROGRAM_FAILURE:           return "Program build failure";
    case CL_MAP_FAILURE:                     return "Map failure";
    case CL_INVALID_VALUE:                   return "Invalid value";
    case CL_INVALID_DEVICE_TYPE:             return "Invalid device type";
    case CL_INVALID_PLATFORM:                return "Invalid platform";
    case CL_INVALID_DEVICE:                  return "Invalid device";
    case CL_INVALID_CONTEXT:                 return "Invalid context";
    case CL_INVALID_QUEUE_PROPERTIES:        return "Invalid queue properties";
    case CL_INVALID_COMMAND_QUEUE:           return "Invalid command queue";
    case CL_INVALID_HOST_PTR:                return "Invalid host pointer";
    case CL_INVALID_MEM_OBJECT:              return "Invalid memory object";
    case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR: return "Invalid image format descriptor";
    case CL_INVALID_IMAGE_SIZE:              return "Invalid image size";
    case CL_INVALID_SAMPLER:                 return "Invalid sampler";
    case CL_INVALID_BINARY:                  return "Invalid binary";
    case CL_INVALID_BUILD_OPTIONS:           return "Invalid build options";
    case CL_INVALID_PROGRAM:                 return "Invalid program";
    case CL_INVALID_PROGRAM_EXECUTABLE:      return "Invalid program executable";
    case CL_INVALID_KERNEL_NAME:             return "Invalid kernel name";
    case CL_INVALID_KERNEL_DEFINITION:       return "Invalid kernel definition";
    case CL_INVALID_KERNEL:                  return "Invalid kernel";
    case CL_INVALID_ARG_INDEX:               return "Invalid argument index";
    case CL_INVALID_ARG_VALUE:               return "Invalid argument value";
    case CL_INVALID_ARG_SIZE:                return "Invalid argument size";
    case CL_INVALID_KERNEL_ARGS:             return "Invalid kernel arguments";
    case CL_INVALID_WORK_DIMENSION:          return "Invalid work dimension";
    case CL_INVALID_WORK_GROUP_SIZE:         return "Invalid work group size";
    case CL_INVALID_WORK_ITEM_SIZE:          return "Invalid work item size";
    case CL_INVALID_GLOBAL_OFFSET:           return "Invalid global offset";
    case CL_INVALID_EVENT_WAIT_LIST:         return "Invalid event wait list";
    case CL_INVALID_EVENT:                   return "Invalid event";
    case CL_INVALID_OPERATION:               return "Invalid operation";
    case CL_INVALID_GL_OBJECT:               return "Invalid OpenGL object";
    case CL_INVALID_BUFFER_SIZE:             return "Invalid buffer size";
    case CL_INVALID_MIP_LEVEL:               return "Invalid mip-map level";
    default:                                 return "Unknown Error Code";
  }
}

bool gul::clCheckError(cl_int error)
{
  if(error != CL_SUCCESS)
  {
    GUL_LOG_WARNING("OpenCL Error: %s", clErrorToString(error));
    return false;
  }
  return true;
}
