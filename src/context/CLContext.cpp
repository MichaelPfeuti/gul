/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti.
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

#include "CLContext.h"
#include "Log.h"
#include "Assert.h"
#include "Misc.h"
#include "ContextErrorHandling.h"

static void errorCallback(const char *description,
                          const void*, size_t,
                          void*)
{
  GUL_UNUSED_VAR(description);

  GUL_LOG_ERROR("OpenCL Error Callback: %s!", description);
}

gul::CLContext* gul::CLContext::s_pCurrentContext = nullptr;


gul::CLContext::CLContext(void)
{
}

gul::CLContext::~CLContext(void)
{
  //clReleaseCommandQueue(m_queue);
  clReleaseContext(m_context);
}

bool gul::CLContext::Initialize(void)
{
  cl_uint counter = 0;
  GUL_CL_CHECK_ERROR(clGetPlatformIDs(0, nullptr, &counter));
  if(counter == 0)
  {
    GUL_LOG_WARNING("No OpenCL platform found!");
    return false;
  }

  cl_platform_id platform;
  GUL_CL_CHECK_ERROR(clGetPlatformIDs(1, &platform, nullptr));

  counter = 0;
  GUL_CL_CHECK_ERROR(clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 0, nullptr, &counter));
  if(counter == 0)
  {
    GUL_LOG_WARNING("No OpenCL device found!");
    return false;
  }

  cl_device_id devices[counter];
  GUL_CL_CHECK_ERROR(clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, counter, devices, nullptr));

  for(cl_uint i = 0; i < counter; ++i)
  {
    m_devices.Add(devices[i]);
  }

  const cl_context_properties contextProperties [] = {
      CL_CONTEXT_PLATFORM, (cl_context_properties) platform,
      0, 0
  };

  cl_int error;
  m_context = clCreateContext(contextProperties,
                              counter, devices,
                              errorCallback, nullptr,
                              &error);
  GUL_CL_CHECK_ERROR(error);

  m_currentQueue = clCreateCommandQueue(m_context, devices[0], 0, &error);
  GUL_CL_CHECK_ERROR(error);

  return true;
}

cl_command_queue& gul::CLContext::GetCurrentQueue(void)
{
  return m_currentQueue;
}

cl_device_id& gul::CLContext::GetDevice(int index)
{
  return m_devices.Get(index);
}

cl_context& gul::CLContext::GetCLContext(void)
{
  return m_context;
}

void gul::CLContext::MakeCurrent(void)
{
  s_pCurrentContext = this;
}

gul::CLContext* gul::CLContext::GetCurrentContext(void)
{
  return s_pCurrentContext;
}
