#pragma once
#ifndef _GUL_BASE_CLASSFACTORY_H_
#define _GUL_BASE_CLASSFACTORY_H_

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
#include "Map.h"

namespace gul {


class ClassFactory
{
    typedef void* (*creatorFunction)();
    typedef gul::Map<gul::String, creatorFunction> ClassNameToFactoryMap;
public:
    ClassFactory(const gul::String& rClassName, creatorFunction);
    ~ClassFactory();
    static void  AddClassCreator(const gul::String& rClassName, creatorFunction);
    static void* CreateInstance(const gul::String& rClassName);

private:
    // must be a pointer. this way we can control when the map is created.
    // if this is on the stack we get a runtime error
    static ClassNameToFactoryMap* pNameToFactoryMap;
};

}

#define REGISTER_CLASS_FACTORY(className) \
\
namespace { \
static void* className##__Factory() \
{ \
return new className(); \
} \
\
static gul::ClassFactory className##__dummy(gul::String(#className), &className## __Factory); \
}


#define REGISTER_NAMESPACE_CLASS_FACTORY(namespaceName, className) \
\
namespace { \
void* namespaceName##__##className##__Factory() \
{ \
return new namespaceName::className(); \
} \
\
gul::ClassFactory namespaceName##__##className##__dummy(gul::String(#namespaceName) + gul::String("::") + gul::String(#className), &namespaceName##__##className##__Factory);\
}

#endif
