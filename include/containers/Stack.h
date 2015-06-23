#pragma once
#ifndef _GUL_CONTAINERS_STACK_H_
#define _GUL_CONTAINERS_STACK_H_
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
#include "StackBasic.h"
#include "List.h"
#include "ClassFactory.h"
#include "XMLSerializable.h"

namespace gul
{

  template<typename T>
  class Stack : public StackBasic<T>, REGISTER_FACTORY(Stack<T>), public XMLSerializable
  {
      DECLARE_RTTI(Stack)

    private:
      virtual void save(gul::XMLNode& node) const;
      virtual void load(const gul::XMLNode& node);
      friend class XMLSerializable;

  };
}

SPECIALIZE_TPL_TRAITS(gul::Stack)

#include "impl/containers/Stack.hpp"

#endif
