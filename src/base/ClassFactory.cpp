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

#include "ClassFactory.h"

#include "memleak.h"

gul::ClassFactory::ClassNameToFactoryMap* gul::ClassFactory::pNameToFactoryMap = nullptr;

gul::ClassFactory::~ClassFactory()
{
    if(ClassFactory::pNameToFactoryMap != nullptr)
    {
        delete ClassFactory::pNameToFactoryMap;
        ClassFactory::pNameToFactoryMap = nullptr;
    }
}

gul::ClassFactory::ClassFactory(const gul::String& rClassName, void* (*creatorFunction)())
{
    if(ClassFactory::pNameToFactoryMap == nullptr)
        ClassFactory::pNameToFactoryMap = new ClassNameToFactoryMap();
    ClassFactory::AddClassCreator(rClassName, creatorFunction);
}

void gul::ClassFactory::AddClassCreator(const gul::String& rClassName, void* (*creatorFunction)())
{
    pNameToFactoryMap->Add(rClassName, creatorFunction);
}


void* gul::ClassFactory::CreateInstance(const gul::String& rClassName)
{
    if(ClassFactory::pNameToFactoryMap != nullptr && ClassFactory::pNameToFactoryMap->Contains(rClassName))
    {
      creatorFunction function = ClassFactory::pNameToFactoryMap->Get(rClassName);
      return function();
    }
    else
    {
      FAIL("ClassFactory cannot create Instance of desired class");
      return nullptr;
    }
}
