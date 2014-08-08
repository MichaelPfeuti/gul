#pragma once
#ifndef _GUL_CONTEXT_CL_WORKGROUP_H_
#define _GUL_CONTEXT_CL_WORKGROUP_H_
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

namespace gul
{

  class GUL_EXPORT CLWorkgroup
  {
    public:
      explicit CLWorkgroup(size_t sizeX, size_t sizeY = 0, size_t sizeZ = 0)
        : m_dim(0)
      {
        setNextSize(sizeX);
        setNextSize(sizeY);
        setNextSize(sizeZ);
      }

      size_t GetDimension(void) const
      {
        return m_dim;
      }
      const size_t* GetSize(void) const
      {
        return m_size;
      }

    private:
      void setNextSize(size_t size)
      {
        if(size > 0)
        {
          ++m_dim;
          m_size[m_dim - 1] = size;
        }
      }

    private:
      // hard coded maximal dimension
      // No expected the OpenCL will
      // support 4 and more dimension any time soon
      size_t m_size[3];
      size_t m_dim;
  };

}

#endif
