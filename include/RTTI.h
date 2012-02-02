#pragma once
#ifndef _GUL_BASE_RTTI_H_
#define _GUL_BASE_RTTI_H_

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

namespace gul {

template<typename T>
class RTTI
{
public:
  static String GetName();
};

}

#define DEFINE_RTTI(classname) \
  namespace gul { \
    template<> \
    class RTTI<classname> \
    { \
    public: \
      static  gul::String GetName() { return gul::String(#classname); } \
    }; \
  }

#define DEFINE_TEMPLATE_RTTI(classname) \
  namespace gul { \
    template<typename T> \
    class RTTI<classname<T>> \
    { \
    public: \
      static  String GetName() { return (String(#classname) + String("<%>").Arg(RTTI<T>::GetName())); } \
    }; \
  }



DEFINE_RTTI(float)
DEFINE_RTTI(double)
DEFINE_RTTI(short)
DEFINE_RTTI(int)
DEFINE_RTTI(long)
DEFINE_RTTI(long long)
DEFINE_RTTI(char)
DEFINE_RTTI(bool)

#endif
