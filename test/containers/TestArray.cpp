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

#include "CTestAssert.h"
#include "Array.h"
#include "XMLManager.h"

namespace TestArray
{
  int SaveAndLoadXMLPrimitives(void)
  {
    gul::Array<int> intArray;

    intArray.Add(-5);
    intArray.Add(0);
    intArray.Add(5);
    gul::XMLManager::Save<gul::Array<int> >(gul::String("test.xml"), intArray);
    gul::Array<int>* pLoadedIntArray = gul::XMLManager::Load<gul::Array<int> >(gul::String("test.xml"));


    TEST_EQUAL(pLoadedIntArray->Size(), 3);
    TEST_EQUAL(pLoadedIntArray->Get(0), -5);
    TEST_EQUAL(pLoadedIntArray->Get(1), 0);
    TEST_EQUAL(pLoadedIntArray->Get(2), 5);

    GUL_DELETE(pLoadedIntArray);

    return EXIT_SUCCESS;
  }

  int SaveAndLoadXML(void)
  {
    gul::Array<gul::String> stringArray;
    stringArray.Add(gul::String("-5"));
    stringArray.Add(gul::String("0"));
    stringArray.Add(gul::String("5"));
    gul::XMLManager::Save<gul::Array<gul::String> >(gul::String("stringTest.xml"), stringArray);
    gul::Array<gul::String>* pLoadedStringArray = gul::XMLManager::Load<gul::Array<gul::String> >(gul::String("stringTest.xml"));


    TEST_EQUAL(pLoadedStringArray->Size(), 3);
    TEST_EQUAL(pLoadedStringArray->Get(0), gul::String("-5"));
    TEST_EQUAL(pLoadedStringArray->Get(1), gul::String("0"));
    TEST_EQUAL(pLoadedStringArray->Get(2), gul::String("5"));

    GUL_DELETE(pLoadedStringArray);

    return EXIT_SUCCESS;
  }

  int Traits(void)
  {
    TEST_EQUAL(gul::Traits<gul::Array<gul::String>>::GetName(), gul::String("gul::Array<gul::String>"));
    TEST_EQUAL(gul::Traits<gul::Array<gul::Array<gul::String>>>::GetName(), gul::String("gul::Array<gul::Array<gul::String>>"));
    TEST_EQUAL(gul::Traits<gul::Array<gul::Array<gul::String>*>>::GetName(), gul::String("gul::Array<gul::Array<gul::String>*>"));

    return EXIT_SUCCESS;
  }

  int RTTI(void)
  {
    gul::Array<gul::String> stringArray;
    TEST_EQUAL(stringArray.GetRTTI().GetName(), gul::Traits<gul::Array<gul::String>>::GetName());

    return EXIT_SUCCESS;
  }

}
