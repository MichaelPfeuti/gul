#pragma once
#ifndef _GUL_MEMORY_ON_DEMAND_MEMORY_H_
#define _GUL_MEMORY_ON_DEMAND_MEMORY_H_
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

#include <mutex>

namespace gul
{

  template<typename T>
  class OnDemandMemory
  {
    public:
      OnDemandMemory(int size);
      ~OnDemandMemory(void);

      T* GetData(void);
      const T* GetData(void) const;

    private:
      const int m_size;
      mutable T* m_pData;
      mutable std::mutex m_mutex;
  };
}

#include "impl/memory/OnDemandMemory.hpp"

#endif
