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

#include "CTestAssert.h"
#include "List.h"
#include "String.h"
#include "XMLManager.h"

namespace TestList
{

  int SaveAndLoadXMLPrimitives(void)
  {
    gul::List<int> intList;

    intList.Add(-5);
    intList.Add(0);
    intList.Add(5);
    intList.Add(5);
    gul::XMLManager::Save<gul::List<int> >(gul::String("test.xml"), intList);
    gul::List<int>* pLoadedIntList = gul::XMLManager::Load<gul::List<int> >(gul::String("test.xml"));


    TEST_EQUAL(pLoadedIntList->Size(), 4);
    TEST_EQUAL(pLoadedIntList->Get(0), -5);
    TEST_EQUAL(pLoadedIntList->Get(1), 0);
    TEST_EQUAL(pLoadedIntList->Get(2), 5);
    TEST_EQUAL(pLoadedIntList->Get(3), 5);

    GUL_DELETE(pLoadedIntList);

    return EXIT_SUCCESS;
  }

  int SaveAndLoadXML(void)
  {
    gul::List<gul::String> stringList;
    stringList.Add(gul::String("-5"));
    stringList.Add(gul::String("0"));
    stringList.Add(gul::String("5"));
    gul::XMLManager::Save<gul::List<gul::String> >(gul::String("stringTest.xml"), stringList);
    gul::List<gul::String>* pLoadedStringList = gul::XMLManager::Load<gul::List<gul::String> >(gul::String("stringTest.xml"));


    TEST_EQUAL(pLoadedStringList->Size(), 3);
    TEST_EQUAL(pLoadedStringList->Get(0), gul::String("-5"));
    TEST_EQUAL(pLoadedStringList->Get(1), gul::String("0"));
    TEST_EQUAL(pLoadedStringList->Get(2), gul::String("5"));

    GUL_DELETE(pLoadedStringList);

    return EXIT_SUCCESS;
  }

  int Traits(void)
  {
    TEST_EQUAL(gul::Traits<gul::List<gul::String>>::GetName(), gul::String("gul::List<gul::String>"));
    TEST_EQUAL(gul::Traits<gul::List<gul::List<gul::String>>>::GetName(), gul::String("gul::List<gul::List<gul::String>>"));
    TEST_EQUAL(gul::Traits<gul::List<gul::List<gul::String>*>>::GetName(), gul::String("gul::List<gul::List<gul::String>*>"));

    return EXIT_SUCCESS;
  }

  int RTTI(void)
  {
    gul::List<gul::String> stringList;
    TEST_EQUAL(stringList.GetRTTI().GetName(), gul::Traits<gul::List<gul::String>>::GetName());

    gul::List<int> intList;
    TEST_EQUAL(intList.GetRTTI().GetName(), gul::Traits<gul::List<int>>::GetName());

    return EXIT_SUCCESS;
  }

}
