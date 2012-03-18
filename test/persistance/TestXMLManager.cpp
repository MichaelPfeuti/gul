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

#include "CTestAssert.h"

#include "ClassFactory.h"
#include "XMLSerializable.h"
#include "XMLMacros.h"
#include "XMLManager.h"

namespace TestXMLManager
{
class TestClassString;
class TestNestedClass;
class TestClassPrimitives;
}
DEFINE_RTTI(TestXMLManager::TestClassString)
DEFINE_RTTI(TestXMLManager::TestNestedClass)
DEFINE_RTTI(TestXMLManager::TestClassPrimitives)

namespace TestXMLManager
{

  class TestClassString : public gul::XMLSerializationMacroHelper<TestClassString>
  {
    public:
      TestClassString(void)
        : string(nullptr) {}

      virtual ~TestClassString(void) { GUL_DELETE(string); }

      TestClassString& operator= (const TestClassString& other)
      {
         if (this != &other) // protect against invalid self-assignment
         {
           this->string = new gul::String(*other.string);
         }
         // by convention, always return *this
         return *this;
      }

      void fillData(void) { string = new gul::String("TEST String"); }

      bool operator==(const TestClassString& o) const
      {
        return (string == nullptr && o.string == nullptr) ||
               (string != nullptr && o.string != nullptr && *string == *o.string);
      }

      bool operator!=(const TestClassString& o) const
      {
        return !operator ==(o);
      }

    private:
      gul::String* string;

      DECLARE_SERIALIZABLE()
  };

  BEGIN_SAVE(TestClassString)
    SAVE_VARIABLE(string)
  END_SAVE(TestClassString)

  BEGIN_LOAD(TestClassString)
      LOAD_VARIABLE(string)
  END_LOAD(TestClassString)

  class TestClassPrimitives : public gul::XMLSerializationMacroHelper<TestClassPrimitives>
  {
    public:
      TestClassPrimitives(void)
        : integer(0), character(' '), floatingPoint(0.f), doublePrecision(0.), boolean(false)
      {}

      void fillData(void) { integer = -1; character = 'a'; floatingPoint = 1.2345f; doublePrecision = 1.2345; boolean = true;}

      bool operator==(const TestClassPrimitives& o) const
      {
        return  integer == o.integer &&
                character == o.character &&
                floatingPoint == o.floatingPoint &&
                doublePrecision == o.doublePrecision &&
                boolean == o.boolean;
      }

      bool operator!=(const TestClassPrimitives& o) const
      {
        return !operator ==(o);
      }


    private:
      int integer;
      char character;
      float floatingPoint;
      double doublePrecision;
      bool boolean;

      DECLARE_SERIALIZABLE()
  };

  BEGIN_SAVE(TestClassPrimitives)
    SAVE_PRIMITIVE(integer)
    SAVE_PRIMITIVE(character)
    SAVE_PRIMITIVE(floatingPoint)
    SAVE_PRIMITIVE(doublePrecision)
    SAVE_PRIMITIVE(boolean)
  END_SAVE(TestClassPrimitives)

  BEGIN_LOAD(TestClassPrimitives)
    LOAD_PRIMITIVE(integer)
    LOAD_PRIMITIVE(character)
    LOAD_PRIMITIVE(floatingPoint)
    LOAD_PRIMITIVE(doublePrecision)
    LOAD_PRIMITIVE(boolean)
  END_LOAD(TestClassPrimitives)

  class TestNestedClass : public gul::XMLSerializationMacroHelper<TestNestedClass>
  {
    public:
      TestNestedClass(void)
        : integer(0) {}

      void fillData(void) { integer = 20; stringClass.fillData(); primClass.fillData(); }

      bool operator==(const TestNestedClass& o) const
      {
        return  integer == o.integer &&
                stringClass == o.stringClass &&
                primClass == o.primClass;
      }

      bool operator!=(const TestNestedClass& o) const
      {
        return !operator ==(o);
      }

    private:
      int integer;
      TestClassString stringClass;
      TestClassPrimitives primClass;
      DECLARE_SERIALIZABLE()

  };

  BEGIN_SAVE(TestNestedClass)
    SAVE_PRIMITIVE(integer)
    SAVE_VARIABLE(stringClass)
    SAVE_VARIABLE(primClass)
  END_SAVE(TestNestedClass)

  BEGIN_LOAD(TestNestedClass)
    LOAD_PRIMITIVE(integer)
    LOAD_VARIABLE(stringClass)
    LOAD_VARIABLE(primClass)
  END_LOAD(TestNestedClass)

  int SaveAndLoadPrimitivesClass(void)
  {
    TestClassPrimitives primitivesFalseReference;
    TestClassPrimitives primitivesTruth;
    primitivesTruth.fillData();
    gul::XMLManager::Save(gul::String("primitivesTest.xml"), primitivesTruth);
    TestClassPrimitives* pPrimitivesLoaded = gul::XMLManager::Load<TestClassPrimitives>(gul::String("primitivesTest.xml"));

    TEST_NOT_EQUAL(*pPrimitivesLoaded, primitivesFalseReference);
    TEST_EQUAL(*pPrimitivesLoaded, primitivesTruth);
    TEST_FALSE(*pPrimitivesLoaded != primitivesTruth);

    GUL_DELETE(pPrimitivesLoaded);

    return EXIT_SUCCESS;
  }

  int SaveAndLoadNestedClass(void)
  {
    TestNestedClass nestedFalseReference;
    TestNestedClass nestedTruth;
    nestedTruth.fillData();
    gul::XMLManager::Save(gul::String("nestedTest.xml"), nestedTruth);
    TestNestedClass* pNestedLoaded = gul::XMLManager::Load<TestNestedClass>(gul::String("nestedTest.xml"));

    TEST_NOT_EQUAL(*pNestedLoaded, nestedFalseReference);
    TEST_EQUAL(*pNestedLoaded, nestedTruth);
    TEST_FALSE(*pNestedLoaded != nestedTruth);

    GUL_DELETE(pNestedLoaded);

    return EXIT_SUCCESS;
  }

  int SaveAndLoadStringClass(void)
  {
    TestClassString stringFalseReference;
    TestClassString stringTruth;
    stringTruth.fillData();
    gul::XMLManager::Save(gul::String("stringTest.xml"), stringTruth);
    TestClassString* pStringLoaded = gul::XMLManager::Load<TestClassString>(gul::String("stringTest.xml"));

    TEST_NOT_EQUAL(*pStringLoaded, stringFalseReference);
    TEST_EQUAL(*pStringLoaded, stringTruth);
    TEST_FALSE(*pStringLoaded != stringTruth);

    GUL_DELETE(pStringLoaded);

    return EXIT_SUCCESS;
  }
}

