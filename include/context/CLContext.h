#pragma once
#ifndef _GUL_CONTEXT_CL_CONTEXT_H_
#define _GUL_CONTEXT_CL_CONTEXT_H_
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

#include "ListBasic.h"

namespace gul
{

  class GUL_EXPORT CLContext
  {
    public:
      CLContext(void);
      ~CLContext(void);

      bool Initialize(void);
      void MakeCurrent(void);

      cl_context& GetCLContext(void);
      cl_device_id& GetDevice(int index = 0);
      cl_command_queue& GetCurrentQueue(void);

      static CLContext* GetCurrentContext(void);

    private:
      cl_context m_context;
      ListBasic<cl_device_id> m_devices;
      cl_command_queue m_currentQueue;

      static CLContext* s_pCurrentContext;
  };

}

#endif
