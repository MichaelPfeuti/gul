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

#include "Traits.h"
#include "String.h"
#include "CTestAssert.h"

#include <cstdio>

class TestRTTIDummyClass {};
SPECIALIZE_TRAITS(TestRTTIDummyClass)

namespace TestTraits
{

  class NameSpaceDummyClass {};

  template<typename T>
  class TemplateDummyClass {};

  template<typename K, typename V>
  class DualTemplateDummyClass {};
}
SPECIALIZE_TRAITS(TestTraits::NameSpaceDummyClass)
SPECIALIZE_TPL_TRAITS(TestTraits::TemplateDummyClass)
SPECIALIZE_2TPL_TRAITS(TestTraits::DualTemplateDummyClass)

namespace TestTraits
{
  int ClassName(void)
  {
    TEST_EQUAL(gul::Traits<TestRTTIDummyClass>::GetName(), gul::String("TestRTTIDummyClass"));
    TEST_EQUAL(gul::Traits<NameSpaceDummyClass>::GetName(), gul::String("TestTraits::NameSpaceDummyClass"));
    TEST_EQUAL(gul::Traits<TemplateDummyClass<int>>::GetName(), gul::String("TestTraits::TemplateDummyClass<int>"));

    return EXIT_SUCCESS;
  }

  int DualTemplates(void)
  {
    // we cannot put the code directly into the macro, because the comma is
    // regarded as the seperation for the macro argument.
    gul::String test = gul::Traits<DualTemplateDummyClass<int, float>>::GetName();
    gul::String truth("TestTraits::DualTemplateDummyClass<int, float>");
    TEST_EQUAL(test, truth);
    return EXIT_SUCCESS;
  }

  int Primitives(void)
  {
    TEST_EQUAL(gul::Traits<float>::GetName(), gul::String("float"));
    TEST_EQUAL(gul::Traits<double>::GetName(), gul::String("double"));
    TEST_EQUAL(gul::Traits<short>::GetName(), gul::String("short"));
    TEST_EQUAL(gul::Traits<int>::GetName(), gul::String("int"));
    TEST_EQUAL(gul::Traits<long>::GetName(), gul::String("long"));
    TEST_EQUAL(gul::Traits<long long>::GetName(), gul::String("long long"));
    TEST_EQUAL(gul::Traits<char>::GetName(), gul::String("char"));
    TEST_EQUAL(gul::Traits<bool>::GetName(), gul::String("bool"));

    return EXIT_SUCCESS;
  }

  int CompositedTemplates(void)
  {
    // we cannot put the code directly into the macro, because the comma is
    // regarded as the seperation for the macro argument.
    gul::String test1 = gul::Traits<DualTemplateDummyClass<TestRTTIDummyClass, float>>::GetName();
    gul::String truth1("TestTraits::DualTemplateDummyClass<TestRTTIDummyClass, float>");
    TEST_EQUAL(test1, truth1);

    gul::String test2 = gul::Traits<DualTemplateDummyClass<int, NameSpaceDummyClass>>::GetName();
    gul::String truth2("TestTraits::DualTemplateDummyClass<int, TestTraits::NameSpaceDummyClass>");
    TEST_EQUAL(test2, truth2);

    gul::String test3 = gul::Traits<DualTemplateDummyClass<TemplateDummyClass<int>, NameSpaceDummyClass>>::GetName();
    gul::String truth3("TestTraits::DualTemplateDummyClass<TestTraits::TemplateDummyClass<int>, TestTraits::NameSpaceDummyClass>");
    TEST_EQUAL(test3, truth3);

    gul::String test4 = gul::Traits<DualTemplateDummyClass<TemplateDummyClass<int>, DualTemplateDummyClass<TestRTTIDummyClass, NameSpaceDummyClass>>>::GetName();
    gul::String truth4("TestTraits::DualTemplateDummyClass<TestTraits::TemplateDummyClass<int>, TestTraits::DualTemplateDummyClass<TestRTTIDummyClass, TestTraits::NameSpaceDummyClass>>");
    TEST_EQUAL(test4, truth4);

    gul::String test5 = gul::Traits<TemplateDummyClass<TemplateDummyClass<TemplateDummyClass<DualTemplateDummyClass<TestRTTIDummyClass, NameSpaceDummyClass>>>>>::GetName();
    gul::String truth5("TestTraits::TemplateDummyClass<TestTraits::TemplateDummyClass<TestTraits::TemplateDummyClass<TestTraits::DualTemplateDummyClass<TestRTTIDummyClass, TestTraits::NameSpaceDummyClass>>>>");
    TEST_EQUAL(test5, truth5);

    return EXIT_SUCCESS;
  }

  int PointerTypeClassName(void)
  {
    TEST_EQUAL(gul::Traits<TestRTTIDummyClass**>::GetName(), gul::String("TestRTTIDummyClass"));
    TEST_EQUAL(gul::Traits<TestRTTIDummyClass*>::GetName(), gul::String("TestRTTIDummyClass"));

    return EXIT_SUCCESS;
  }

}
