#pragma once
#ifndef _GUL_BASE_RTTI_H_
#define _GUL_BASE_RTTI_H_

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

#include "Traits.h"
#include "String.h"

namespace gul
{

  class GUL_EXPORT RTTI
  {
    public:
      RTTI(const gul::String& classname) : name(classname) {}
      const gul::String& GetName() const
      {
        return name;
      }

    private:
      const gul::String name;
  };

}

#define DECLARE_RTTI(classname) \
  private: \
  static const gul::RTTI RTTI; \
  public: \
  virtual const gul::RTTI& GetRTTI() const { return classname::RTTI; }


#define DEFINE_RTTI(classname) \
  const gul::RTTI classname::RTTI(gul::Traits<classname>::GetName());

#define DEFINE_TPL_RTTI(classname) \
  template<typename T> \
  const gul::RTTI classname<T>::RTTI(gul::Traits<classname<T>>::GetName());

#define DEFINE_2TPL_RTTI(classname) \
  template<typename T1, typename T2> \
  const gul::RTTI classname<T1, T2>::RTTI(gul::Traits<classname<T1, T2>>::GetName());


#endif
