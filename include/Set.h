#pragma once
#ifndef _GUL_CONTAINERS_SET_H_
#define _GUL_CONTAINERS_SET_H_
/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011 Michael Pfeuti.
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
** FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
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

#include "RTTI.h"
#include "Container.h"
#include "List.h"

namespace gul
{

  template<typename T>
  class Set : public Container<T>
  {
    DECLARE_RTTI(Set)

    public:
      Set(void);
      virtual ~Set(void);

      int Size(void) const;
      bool IsEmpty(void) const ;
      bool Contains(const T& rElement) const;
      void Add(const T& rElement);
      void Remove(const T& rElement);
      void Clear(void);

    private:
      virtual void Save(pugi::xml_node& node, bool resetMode) const;
      virtual void* Load(const pugi::xml_node& node, bool resetMode) const;
      friend class XMLSerializable;

    private:
      List<T> list;
  };

}

DEFINE_TPL_RTTI(gul::Set)

#include "impl/containers/Set.hpp"

#endif
