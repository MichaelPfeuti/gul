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
#include "String.h"
#include "RTTI.h"
#include "CTestAssert.h"

#include <cstdio>

class DummyClass : REGISTER_FACTORY(DummyClass)
{
  public:
    virtual ~DummyClass(void) {}
    DECLARE_RTTI(DummyClass)
};
DEFINE_RTTI(DummyClass)

namespace TestClassFactory
{

  class NameSpaceDummyClass : public DummyClass,
    REGISTER_FACTORY(NameSpaceDummyClass)
  {
    public:
      virtual ~NameSpaceDummyClass(void) {}
      DECLARE_RTTI(NameSpaceDummyClass)
  };

  template<typename T>
  class TemplateDummyClass : public DummyClass,
    REGISTER_FACTORY(TemplateDummyClass<T>)
  {
    public:
      virtual ~TemplateDummyClass(void) {}
      DECLARE_RTTI(TemplateDummyClass)
  };

}
DEFINE_RTTI(TestClassFactory::NameSpaceDummyClass)
DEFINE_TPL_RTTI(TestClassFactory::TemplateDummyClass)

namespace TestClassFactory
{
  static const DummyClass a;
  static const NameSpaceDummyClass b;
  static const TemplateDummyClass<int> c;

  int CreateClass(void)
  {
    DummyClass* p = gul::ClassFactory<DummyClass>::CreateInstance(gul::String("DummyClass"));
    TEST_NOT_NULL(p);
    GUL_DELETE(p);

    p = gul::ClassFactory<TestClassFactory::NameSpaceDummyClass>::CreateInstance(gul::String("TestClassFactory::NameSpaceDummyClass"));
    TEST_NOT_NULL(p);
    GUL_DELETE(p);

    p = gul::ClassFactory<NameSpaceDummyClass>::CreateInstance(gul::String("TestClassFactory::NameSpaceDummyClass"));
    TEST_NOT_NULL(p);
    GUL_DELETE(p);

    TEST_ASSERTION(gul::ClassFactory<NameSpaceDummyClass>::CreateInstance(gul::String("NameSpaceDummyClass")));
    TEST_ASSERTION(gul::ClassFactory<DummyClass>::CreateInstance(gul::String("TestClassFactory::DummyClass")));

    return EXIT_SUCCESS;
  }

  int CreateTemplateClass(void)
  {
    TemplateDummyClass<int>* p = gul::ClassFactory<TestClassFactory::TemplateDummyClass<int>>::CreateInstance(gul::String("TestClassFactory::TemplateDummyClass<int>"));
    TEST_NOT_NULL(p);
    GUL_DELETE(p);

    return EXIT_SUCCESS;
  }


  int CreateAssertion(void)
  {
    TEST_ASSERTION(gul::ClassFactory<DummyClass>::CreateInstance(gul::String("DummyClassNotPresent")));
    return EXIT_SUCCESS;
  }

  int CreateSuperClass(void)
  {
    DummyClass* p = gul::ClassFactory<DummyClass>::CreateInstance(gul::String("TestClassFactory::NameSpaceDummyClass"));
    TEST_NOT_NULL(p);
    GUL_DELETE(p);

    p = gul::ClassFactory<DummyClass>::CreateInstance(gul::String("TestClassFactory::TemplateDummyClass<int>"));
    TEST_NOT_NULL(p);
    GUL_DELETE(p);

    return EXIT_SUCCESS;
  }
}

