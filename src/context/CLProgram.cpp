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

#include "CLProgram.h"
#include "Log.h"
#include "Assert.h"
#include "Misc.h"
#include "ContextErrorHandling.h"
#include "CLContext.h"


gul::CLProgram::CLProgram(void)
  : m_isProgramAllocated(false)
{
}

gul::CLProgram::~CLProgram(void)
{
  KernelMap::Iterator it = m_kernels.GetIterator();
  while(it.HasNext())
  {
    clReleaseKernel(it.Next().GetValue());
  }

  if(m_isProgramAllocated)
  {
   clReleaseProgram(m_program);
  }
}

void gul::CLProgram::AddSource(const gul::String& source)
{
  m_sources.Add(source);
}

bool gul::CLProgram::Build(void)
{
  const char* sources[m_sources.Size()];
  for(int i = 0; i < m_sources.Size(); ++i)
    sources[i] = m_sources.Get(i).GetData();

  CLContext* pCurrentContext = CLContext::GetCurrentContext();
  GUL_ASSERT_MSG(pCurrentContext != nullptr, "No current OpenCL context!");

  cl_int error;
  m_program = clCreateProgramWithSource(pCurrentContext->GetCLContext(),
                                        m_sources.Size(), (const char**)&sources,
                                        nullptr, &error);
  GUL_CL_CHECK_ERROR(error);

  m_isProgramAllocated = true;

  if(clBuildProgram(m_program, 0, nullptr, nullptr, nullptr, nullptr) != CL_SUCCESS)
  {
    size_t bufferSize;
    GUL_CL_CHECK_ERROR(clGetProgramBuildInfo(m_program, pCurrentContext->GetDevice(), CL_PROGRAM_BUILD_LOG, 0, nullptr, &bufferSize));
    char log[bufferSize+1];
    GUL_CL_CHECK_ERROR(clGetProgramBuildInfo(m_program, pCurrentContext->GetDevice(), CL_PROGRAM_BUILD_LOG, bufferSize, log, nullptr));
    log[bufferSize] = '\0';

    GUL_LOG_ERROR(log);
    return false;
  }

  cl_uint counter = 0;
  GUL_CL_CHECK_ERROR(clCreateKernelsInProgram(m_program, 0, nullptr, &counter));
  if(counter == 0)
  {
    GUL_LOG_WARNING("No OpenCL kernels in program found!");
    return false;
  }

  cl_kernel kernels[counter];
  GUL_CL_CHECK_ERROR(clCreateKernelsInProgram(m_program, counter, kernels, nullptr));

  for(cl_uint i = 0; i < counter; ++i)
  {
    size_t bufferSize;
    GUL_CL_CHECK_ERROR(clGetKernelInfo(kernels[i], CL_KERNEL_FUNCTION_NAME, 0, nullptr, &bufferSize));

    char buffer[bufferSize];
    GUL_CL_CHECK_ERROR(clGetKernelInfo(kernels[i], CL_KERNEL_FUNCTION_NAME, bufferSize, buffer, nullptr));

    m_kernels.Add(buffer, kernels[i]);
  }

  return true;
}

bool gul::CLProgram::Run(const gul::String& kernelName)
{
  return false;
}

