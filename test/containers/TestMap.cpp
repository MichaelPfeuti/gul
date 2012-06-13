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
#include "Map.h"
#include "XMLManager.h"

namespace TestMap
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
SPECIALIZE_TRAITS(TestMap::TestSaveClass)
DEFINE_RTTI(TestMap::TestSaveClass)

namespace TestMap
{

  int SaveAndLoadXMLPrimitives(void)
  {
    gul::Map<int, float> intFloatMap;

    intFloatMap.Add(-5, 0.5);
    intFloatMap.Add(0, 1.0);
    intFloatMap.Add(5, 2.0);
    gul::XMLManager::Save<gul::Map<int, float> >(gul::String("test.xml"), intFloatMap);
    gul::Map<int, float>* pLoadedIntFloatMap = gul::XMLManager::Load<gul::Map<int, float> >(gul::String("test.xml"));


    TEST_EQUAL(pLoadedIntFloatMap->Size(), 3);
    TEST_EQUAL(pLoadedIntFloatMap->Get(-5), 0.5);
    TEST_EQUAL(pLoadedIntFloatMap->Get(0), 1.0);
    TEST_EQUAL(pLoadedIntFloatMap->Get(5), 2.0);
    TEST_FALSE(pLoadedIntFloatMap->Contains(1));

    GUL_DELETE(pLoadedIntFloatMap);

    return EXIT_SUCCESS;
  }

  int SaveAndLoadXML(void)
  {
    gul::Map<TestSaveClass, float> saveMap;

    TestSaveClass a(-5);
    TestSaveClass b(0);
    TestSaveClass c(5);
    TestSaveClass d(15);
    saveMap.Add(a, 0.5);
    saveMap.Add(b, 1.0);
    saveMap.Add(c, 2.0);
    gul::XMLManager::Save<gul::Map<TestSaveClass, float> >(gul::String("test.xml"), saveMap);
    gul::Map<TestSaveClass, float>* pLoadedMap = gul::XMLManager::Load<gul::Map<TestSaveClass, float> >(gul::String("test.xml"));


    TEST_EQUAL(pLoadedMap->Size(), 3);
    TEST_EQUAL(pLoadedMap->Get(a), 0.5);
    TEST_EQUAL(pLoadedMap->Get(b), 1.0);
    TEST_EQUAL(pLoadedMap->Get(c), 2.0);
    TEST_FALSE(pLoadedMap->Contains(d));

    GUL_DELETE(pLoadedMap);

    return EXIT_SUCCESS;
  }

  int Traits(void)
  {
    gul::String tmp1 = gul::Traits<gul::Map<gul::String, int>>::GetName();
    gul::String tmp2 = gul::Traits<gul::Map<gul::Map<gul::String, int>, int>>::GetName();
    gul::String tmp3 = gul::Traits<gul::Map<gul::Map<gul::String, int>*, int*>>::GetName();

    TEST_EQUAL(tmp1, gul::String("gul::Map<gul::String,int>"));
    TEST_EQUAL(tmp2, gul::String("gul::Map<gul::Map<gul::String,int>,int>"));
    TEST_EQUAL(tmp3, gul::String("gul::Map<gul::Map<gul::String,int>*,int*>"));

    return EXIT_SUCCESS;
  }

  int RTTI(void)
  {
    gul::Map<gul::String*, int> stringMap;
    gul::String truth = gul::Traits<gul::Map<gul::String*, int>>::GetName();
    TEST_EQUAL(stringMap.GetRTTI().GetName(), truth);

    return EXIT_SUCCESS;
  }
}
