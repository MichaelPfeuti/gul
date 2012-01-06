#pragma once
#ifndef _GUL_BASE_CLASS_FACTORY_H_
#define _GUL_BASE_CLASS_FACTORY_H_

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
#include "ClassFactoryBase.h"

namespace gul
{

  template<typename T>
  class ClassFactory : public ClassFactoryBase
  {
    public:
      ClassFactory(void);
      ClassFactory(creatorFunction);
      static T* CreateInstance(const gul::String& rClassName);
    private:
      static void* CreateConcreteClass(void);
  };

}


#define DECALRE_CREATE(classname) \
  private: \
    template<typename T_ClassFactory> friend class gul::ClassFactory; \
    static void* CreateInstance(void); \
    static const gul::ClassFactory<classname> classFactory

#define DEFINE_CREATE(classname) \
  void* classname::CreateInstance(void) \
  { \
    return new classname(); \
  } \
  \
  const gul::ClassFactory<classname> classname::classFactory = gul::ClassFactory<classname>(&classname::CreateInstance)

#define DEFINE_TEMPLATE_CREATE(classname) \
  template<typename T> \
  void* classname<T>::CreateInstance(void) \
  { \
    return new classname<T>(); \
  } \
  \
  template<typename T> \
  const gul::ClassFactory<classname<T>> classname<T>::classFactory = gul::ClassFactory<classname<T>>(&classname<T>::CreateInstance) \


#include "impl/base/ClassFactory.hpp"

#endif
