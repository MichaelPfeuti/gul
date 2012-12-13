#pragma once
#ifndef _GUL_BASE_CLASS_FACTORY_H_
#define _GUL_BASE_CLASS_FACTORY_H_
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

#include "ClassFactoryBase.h"

namespace gul
{
  class String;
}


namespace gul
{

  template<typename T>
  class ClassFactory : public ClassFactoryBase
  {
    public:
      ClassFactory(void);
      static T* CreateInstance(const gul::String& rClassName);
      void dummy(void) const {}

    private:
      class ClassCreatorFunctorSpecific : public ClassCreatorFunctor
      {
        public:
          virtual void* operator()(void) const
          {
            return new T();
          }
      };
  };

  template<typename T>
  class ClassFactory<T*> : public ClassFactoryBase
  {
    public:
      static T** CreateInstance(const gul::String& rClassName)
      {
        return new T*(ClassFactory<T>::CreateInstance(rClassName));
      }
  };


  /**
    * The ClassRegisterer is needed to enusre that templates are
    * correctly registered. Because template instantiate code lazily we need
    * to call dummy to guarantee that classFactory creation code is instantiated.
    * This is only the case for tempaltes regular classes would not need that.
    * but for consistency every class should be registered through the ClassRegisterer
    */
  template<typename T>
  class ClassRegisterer
  {
    public:
      ClassRegisterer(void)
      {
        classFactory.dummy();
      }
    private:
      static const gul::ClassFactory<T> classFactory;
  };

  template<typename T>
  const gul::ClassFactory<T> ClassRegisterer<T>::classFactory = gul::ClassFactory<T>();
}

#define REGISTER_FACTORY(classname) \
  private gul::ClassRegisterer<classname>


// to prevent cyclic inclusion we register the string class here
namespace
{
  class gul::ClassFactory<gul::String> a;
}

#include "impl/base/ClassFactory.hpp"

#endif
