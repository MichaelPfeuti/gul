#pragma once
#ifndef _GUL_CONTEXT_CL_PROGRAM_H_
#define _GUL_CONTEXT_CL_PROGRAM_H_
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

#include "gul_export.h"

#include <CL/cl.h>

#include "ContextErrorHandling.h"
#include "MapBasic.h"
#include "String.h"
#include "CLContext.h"
#include "CLWorkgroup.h"
#include "Assert.h"

namespace gul
{

  class GUL_EXPORT CLProgram
  {
    public:
      CLProgram(void);
      ~CLProgram(void);

      void AddSource(const gul::String& source);
      bool Build(void);

      template<typename... ArgTypes>
      bool Run(const gul::String& kernelName, const CLWorkgroup& workGroup, ArgTypes... params)
      {
        CLContext* pCurrentContext = CLContext::GetCurrentContext();
        GUL_ASSERT_MSG(pCurrentContext != nullptr, "No current OpenCL context!");

        cl_kernel& kernel = m_kernels.Get(kernelName);
        if(!SetArgument(kernel, 0, params...))
        {
          return false;
        }

        GUL_CL_CHECK_ERROR(clEnqueueNDRangeKernel(pCurrentContext->GetCurrentQueue(),
                                                  kernel, workGroup.GetDimension(), nullptr,
                                                  workGroup.GetSize(), nullptr,
                                                  0, nullptr, nullptr));
        return true;
      }

    private:
      template<typename T, typename... Tail>
      bool SetArgument(cl_kernel& kernel, cl_uint index, const T& value, Tail... paramsTail)
      {
        GUL_CL_CHECK_ERROR(clSetKernelArg(kernel, index, sizeof(T), &value));
        return SetArgument(kernel, ++index, paramsTail...);
      }

      template<typename T>
      bool SetArgument(cl_kernel&, const T&)
      {
        return true;
      }

    private:
      typedef gul::MapBasic<const gul::String, cl_kernel> KernelMap;

      bool m_isProgramAllocated;
      cl_program m_program;
      KernelMap m_kernels;
      gul::ListBasic<const gul::String> m_sources;
  };

}

#endif
