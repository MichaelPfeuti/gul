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

#include "CTestAssert.h"
#include "Stack.h"
#include "XMLManager.h"

namespace TestStack
{

  int SaveAndLoadXMLPrimitives(void)
  {
    gul::Stack<int> intStack;

    intStack.Push(-5);
    intStack.Push(0);
    intStack.Push(5);
    gul::XMLManager::Save<gul::Stack<int> >(gul::String("test.xml"), intStack);
    gul::Stack<int>* pLoadedIntStack = gul::XMLManager::Load<gul::Stack<int> >(gul::String("test.xml"));


    TEST_EQUAL(pLoadedIntStack->Size(), 3);
    TEST_EQUAL(pLoadedIntStack->Pop(), 5);
    TEST_EQUAL(pLoadedIntStack->Pop(), 0);
    TEST_EQUAL(pLoadedIntStack->Pop(), -5);

    GUL_DELETE(pLoadedIntStack);

    return EXIT_SUCCESS;
  }

  int SaveAndLoadXML(void)
  {
    gul::Stack<gul::String*> stringStack;
    stringStack.Push(new gul::String("-5"));
    stringStack.Push(new gul::String("0"));
    stringStack.Push(new gul::String("5"));
    gul::XMLManager::Save<gul::Stack<gul::String*> >(gul::String("stringTest.xml"), stringStack);
    gul::Stack<gul::String*>* pLoadedStringStack = gul::XMLManager::Load<gul::Stack<gul::String*> >(gul::String("stringTest.xml"));


    TEST_EQUAL(pLoadedStringStack->Size(), 3);
    TEST_EQUAL(*pLoadedStringStack->Pop(), gul::String("5"));
    TEST_EQUAL(*pLoadedStringStack->Pop(), gul::String("0"));
    TEST_EQUAL(*pLoadedStringStack->Pop(), gul::String("-5"));

    GUL_DELETE(pLoadedStringStack);

    return EXIT_SUCCESS;
  }

  int Traits(void)
  {
    TEST_EQUAL(gul::Traits<gul::Stack<gul::String>>::GetName(), gul::String("gul::Stack<gul::String>"));
    TEST_EQUAL(gul::Traits<gul::Stack<gul::Stack<gul::String>>>::GetName(), gul::String("gul::Stack<gul::Stack<gul::String>>"));
    TEST_EQUAL(gul::Traits<gul::Stack<gul::Stack<gul::String>*>>::GetName(), gul::String("gul::Stack<gul::Stack<gul::String>*>"));

    return EXIT_SUCCESS;
  }

  int RTTI(void)
  {
    gul::Stack<gul::String*> stringStack;
    TEST_EQUAL(stringStack.GetRTTI().GetName(), gul::Traits<gul::Stack<gul::String*>>::GetName());

    return EXIT_SUCCESS;
  }
}
