#pragma once
#ifndef _GUL_BASE_TRAITS_H_
#define _GUL_BASE_TRAITS_H_

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

#include "String.h"

namespace gul
{

  template<typename T>
  class Traits
  {
    public:
      static gul::String GetName();
  };

  template<typename T>
  class Traits<T*>
  {
    public:
      static gul::String GetName()
      {
        return gul::Traits<T>::GetName() + gul::String("*");
      }
  };

  // TODO: this is wrong. it works for xml saving and loading. but i need to strip the const in the loading/saving not here
  template<typename T>
  class Traits<const T>
  {
    public:
      static gul::String GetName()
      {
        return gul::Traits<T>::GetName();
      }
  };

}

#define SPECIALIZE_TRAITS(classname) \
  namespace gul { \
    template<>  \
    class Traits<classname> \
    { \
      public: \
        static String GetName() { return gul::String(#classname); } \
    }; \
  }

#define SPECIALIZE_TPL_TRAITS(classname) \
  namespace gul { \
    template<> template<typename T> \
    class Traits<classname<T>> \
    { \
      public: \
        static String GetName() { return (String(#classname) + String("<%>").Arg(Traits<T>::GetName())); } \
    }; \
  }

#define SPECIALIZE_2TPL_TRAITS(classname) \
  namespace gul { \
    template<> template<typename T1, typename T2> \
    class Traits<classname<T1, T2>> \
    { \
      public: \
        static String GetName() { return (String(#classname) + String("<%, %>").Arg(Traits<T1>::GetName())).Arg(Traits<T2>::GetName()); } \
    }; \
  }


SPECIALIZE_TRAITS(float)
SPECIALIZE_TRAITS(double)
SPECIALIZE_TRAITS(short)
SPECIALIZE_TRAITS(unsigned short)
SPECIALIZE_TRAITS(int)
SPECIALIZE_TRAITS(unsigned int)
SPECIALIZE_TRAITS(long)
SPECIALIZE_TRAITS(unsigned long)
SPECIALIZE_TRAITS(long long)
SPECIALIZE_TRAITS(unsigned long long)
SPECIALIZE_TRAITS(char)
SPECIALIZE_TRAITS(bool)
SPECIALIZE_TRAITS(void)
SPECIALIZE_TRAITS(gul::String)


#endif
