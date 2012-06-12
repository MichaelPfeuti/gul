/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012 Michael Pfeuti.
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
#include "Assert.h"
#include "String.h"

/**
  * The template argument must be a concrete class such that we can create
  * an instance from it when requested.
  */
template<typename T>
gul::ClassFactory<T>::ClassFactory(void)
{
  // TODO: Caution with multithreading
  if(ClassFactoryBase::pNameToFactoryMap == nullptr)
  {
    ClassFactoryBase::pNameToFactoryMap = new ClassNameToFactoryMap();
  }
  ClassFactoryBase::pNameToFactoryMap->Add(gul::Traits<T>::GetName().GetData(), new ClassCreatorFunctorSpecific());
}

/**
  * The tempalte argument doesn't need to be a concrete class. It can be an abstract class as
  * well. It only matters the the rClassName represents a concrete class.
  */
template<typename T>
T* gul::ClassFactory<T>::CreateInstance(const gul::String& rClassName)
{
  ASSERT(ClassFactoryBase::pNameToFactoryMap != nullptr);

  const gul::ClassFactoryBase::ClassCreatorFunctor* function = gul::ClassFactoryBase::pNameToFactoryMap->Get(rClassName.GetData());
  if(function != nullptr)
  {
    return static_cast<T*>((*function)());
  }
  else
  {
    FAIL(gul::String("ClassFactory cannot create Instance of %").Arg(rClassName).GetData());
    return nullptr;
  }
  return nullptr;
}
