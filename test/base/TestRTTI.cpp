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

#include "RTTI.h"
#include "String.h"
#include "CTestAssert.h"

#include <cstdio>

class TestRTTIDummyClass
{
};

namespace TestRTTI
{

  class NameSpaceDummyClass : public TestRTTIDummyClass
  {
  };

  template<typename T>
  class TemplateDummyClass : public TestRTTIDummyClass
  {
  };
}
DEFINE_RTTI(TestRTTIDummyClass);
DEFINE_RTTI(TestRTTI::NameSpaceDummyClass)
DEFINE_TPL_RTTI(TestRTTI::TemplateDummyClass)

namespace TestRTTI
{
  int ClassName(void)
  {
    TEST_EQUAL(gul::RTTI<TestRTTIDummyClass>::GetName(), gul::String("TestRTTIDummyClass"));
    TEST_EQUAL(gul::RTTI<NameSpaceDummyClass>::GetName(), gul::String("TestRTTI::NameSpaceDummyClass"));
    TEST_EQUAL(gul::RTTI<TemplateDummyClass<int>>::GetName(), gul::String("TestRTTI::TemplateDummyClass<int>"));
    return EXIT_SUCCESS;
  }

  int Primitives(void)
  {
    TEST_EQUAL(gul::RTTI<float>::GetName(), gul::String("float"));
    TEST_EQUAL(gul::RTTI<double>::GetName(), gul::String("double"));
    TEST_EQUAL(gul::RTTI<short>::GetName(), gul::String("short"));
    TEST_EQUAL(gul::RTTI<int>::GetName(), gul::String("int"));
    TEST_EQUAL(gul::RTTI<long>::GetName(), gul::String("long"));
    TEST_EQUAL(gul::RTTI<long long>::GetName(), gul::String("long long"));
    TEST_EQUAL(gul::RTTI<char>::GetName(), gul::String("char"));
    TEST_EQUAL(gul::RTTI<bool>::GetName(), gul::String("bool"));

    return EXIT_SUCCESS;
  }

}
