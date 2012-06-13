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
#include "Set.h"
#include "XMLManager.h"
#include "ClassFactory.h"
#include "RTTI.h"

namespace TestSet
{

  class TestSaveClass : REGISTER_FACTORY(TestSaveClass)
  {
    DECLARE_RTTI(TestSaveClass)

    public:
      TestSaveClass(int i = 0) : _i(i) {}
      virtual ~TestSaveClass(void) {}
      bool operator==(const TestSaveClass& c) const { return c._i == _i; }


      void save(gul::XMLNode& node) const
      {
        node.AppendAttribute(gul::String("i")).SetValue(_i);
      }

      void load(const gul::XMLNode& node)
      {
        _i = node.GetAttribute(gul::String("i")).GetInt();
      }

    private:
      int _i = 0;
  };
}
SPECIALIZE_TRAITS(TestSet::TestSaveClass)
DEFINE_RTTI(TestSet::TestSaveClass)


namespace TestSet
{

  int SaveAndLoadXMLPrimitives(void)
  {
    gul::Set<int> intSet;

    intSet.Add(-5);
    intSet.Add(0);
    intSet.Add(5);
    gul::XMLManager::Save<gul::Set<int> >(gul::String("test.xml"), intSet);
    gul::Set<int>* pLoadedIntSet = gul::XMLManager::Load<gul::Set<int> >(gul::String("test.xml"));


    TEST_EQUAL(pLoadedIntSet->Size(), 3);
    TEST_TRUE(pLoadedIntSet->Contains(-5));
    TEST_TRUE(pLoadedIntSet->Contains(0));
    TEST_TRUE(pLoadedIntSet->Contains(5));

    GUL_DELETE(pLoadedIntSet);

    return EXIT_SUCCESS;
  }

  int SaveAndLoadXML(void)
  {
    gul::Set<TestSaveClass> intClass;

    intClass.Add(TestSaveClass(-5));
    intClass.Add(TestSaveClass(0));
    intClass.Add(TestSaveClass(5));
    gul::XMLManager::Save<gul::Set<TestSaveClass> >(gul::String("test.xml"), intClass);
    gul::Set<TestSaveClass>* pLoadedIntSet = gul::XMLManager::Load<gul::Set<TestSaveClass> >(gul::String("test.xml"));


    TEST_EQUAL(pLoadedIntSet->Size(), 3);
    TEST_TRUE(pLoadedIntSet->Contains(TestSaveClass(-5)));
    TEST_TRUE(pLoadedIntSet->Contains(TestSaveClass(0)));
    TEST_TRUE(pLoadedIntSet->Contains(TestSaveClass(5)));
    TEST_FALSE(pLoadedIntSet->Contains(TestSaveClass(15)));

    GUL_DELETE(pLoadedIntSet);

    return EXIT_SUCCESS;
  }

  int Traits(void)
  {
    TEST_EQUAL(gul::Traits<gul::Set<gul::String>>::GetName(), gul::String("gul::Set<gul::String>"));
    TEST_EQUAL(gul::Traits<gul::Set<gul::Set<gul::String>>>::GetName(), gul::String("gul::Set<gul::Set<gul::String>>"));
    TEST_EQUAL(gul::Traits<gul::Set<gul::Set<gul::String>*>>::GetName(), gul::String("gul::Set<gul::Set<gul::String>*>"));

    return EXIT_SUCCESS;
  }

  int RTTI(void)
  {
    gul::Set<gul::String*> stringSet;
    TEST_EQUAL(stringSet.GetRTTI().GetName(), gul::Traits<gul::Set<gul::String*>>::GetName());

    return EXIT_SUCCESS;
  }

}
