#pragma once
#ifndef _GUL_BASE_CLASS_FACTORY_BASE_H_
#define _GUL_BASE_CLASS_FACTORY_BASE_H_
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

#include "RTTI.h"
#include "MapBasic.h"

#include <string>

namespace gul
{

  class GUL_EXPORT ClassFactoryBase
  {
    public:
      virtual ~ClassFactoryBase();

    protected:
      class ClassCreatorFunctor
      {
          DECLARE_RTTI(ClassCreatorFunctor)

        public:
          virtual ~ClassCreatorFunctor(void) {}
          virtual void* operator()(void) const = 0;
      };

      typedef MapBasic<std::string, const ClassCreatorFunctor*> ClassNameToFactoryMap;

      // must be a pointer. this way we can control when the map is created.
      // if this is on the stack we get a runtime error
      static ClassNameToFactoryMap* pNameToFactoryMap;
  };

}

SPECIALIZE_TRAITS(gul::ClassFactoryBase::ClassCreatorFunctor)
#endif
