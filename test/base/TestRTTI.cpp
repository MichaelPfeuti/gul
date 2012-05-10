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
#include "Misc.h"

#include <cstdio>

class TestRTTIDummyClass
{
  public:
    virtual ~TestRTTIDummyClass(void) {}
    DECLARE_RTTI(TestRTTIDummyClass)
};
DEFINE_RTTI(TestRTTIDummyClass);

namespace TestRTTI
{

  class NameSpaceDummyClass : public TestRTTIDummyClass
  {
    public:
      virtual ~NameSpaceDummyClass(void) {}
      DECLARE_RTTI(NameSpaceDummyClass)
  };

  template<typename T>
  class TemplateDummyClass : public TestRTTIDummyClass
  {
    public:
      virtual ~TemplateDummyClass(void) {}
      DECLARE_RTTI(TemplateDummyClass)
  };

  template<typename K, typename V>
  class DualTemplateDummyClass : public NameSpaceDummyClass
  {
    public:
      virtual ~DualTemplateDummyClass(void) {}
      DECLARE_RTTI(DualTemplateDummyClass)
  };
}
DEFINE_RTTI(TestRTTI::NameSpaceDummyClass)
DEFINE_TPL_RTTI(TestRTTI::TemplateDummyClass)
DEFINE_2TPL_RTTI(TestRTTI::DualTemplateDummyClass)

namespace TestRTTI
{
  int ClassName(void)
  {
    TestRTTIDummyClass dummyClass;
    NameSpaceDummyClass namespaceClass;
    TemplateDummyClass<int> templateClass;

    TEST_EQUAL(dummyClass.GetRTTI().GetName(), gul::Traits<TestRTTIDummyClass>::GetName());
    TEST_EQUAL(namespaceClass.GetRTTI().GetName(), gul::Traits<NameSpaceDummyClass>::GetName());
    TEST_EQUAL(templateClass.GetRTTI().GetName(), gul::Traits<TemplateDummyClass<int>>::GetName());

    return EXIT_SUCCESS;
  }

  int ClassNameInheritance(void)
  {
    TestRTTIDummyClass* p = new TemplateDummyClass<TestRTTIDummyClass>();

    TEST_EQUAL(p->GetRTTI().GetName(), gul::Traits<TemplateDummyClass<TestRTTIDummyClass>>::GetName());
    TEST_NOT_EQUAL(p->GetRTTI().GetName(), gul::Traits<TestRTTIDummyClass>::GetName());

    GUL_DELETE(p);
    return EXIT_SUCCESS;
  }


  int DualTemplates(void)
  {
    DualTemplateDummyClass<int, float> dualTemplateClass;
    gul::String truth1(gul::Traits<DualTemplateDummyClass<int, float>>::GetName());
    TEST_EQUAL(dualTemplateClass.GetRTTI().GetName(), truth1);

    NameSpaceDummyClass* namespacePointer = new DualTemplateDummyClass<TestRTTIDummyClass, TemplateDummyClass<float>>();
    gul::String truth2(gul::Traits<DualTemplateDummyClass<TestRTTIDummyClass, TemplateDummyClass<float>>>::GetName());
    TEST_EQUAL(namespacePointer->GetRTTI().GetName(), truth2);
    TEST_NOT_EQUAL(namespacePointer->GetRTTI().GetName(), gul::Traits<NameSpaceDummyClass>::GetName());

    GUL_DELETE(namespacePointer);

    return EXIT_SUCCESS;
  }

  int CompositedTemplates(void)
  {
    NameSpaceDummyClass* namespacePointer = new DualTemplateDummyClass<DualTemplateDummyClass<TemplateDummyClass<TestRTTIDummyClass>, NameSpaceDummyClass>, TemplateDummyClass<DualTemplateDummyClass<TestRTTIDummyClass, NameSpaceDummyClass>>>();
    gul::String truth(gul::Traits<DualTemplateDummyClass<DualTemplateDummyClass<TemplateDummyClass<TestRTTIDummyClass>, NameSpaceDummyClass>, TemplateDummyClass<DualTemplateDummyClass<TestRTTIDummyClass, NameSpaceDummyClass>>>>::GetName());
    TEST_EQUAL(namespacePointer->GetRTTI().GetName(), truth);
    TEST_NOT_EQUAL(namespacePointer->GetRTTI().GetName(), gul::Traits<NameSpaceDummyClass>::GetName());

    GUL_DELETE(namespacePointer);

    return EXIT_SUCCESS;
  }

}
