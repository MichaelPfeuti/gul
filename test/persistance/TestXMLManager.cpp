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

  class TestClassString : INHERIT_SERIALIZABLE(TestClassString)
  {
      DECLARE_RTTI(TestClassString)

    public:
      TestClassString(void)
        : string(nullptr) {}

      virtual ~TestClassString(void)
      {
        GUL_DELETE(string);
      }

      TestClassString& operator= (const TestClassString& other)
      {
        if(this != &other)  // protect against invalid self-assignment
        {
          this->string = new gul::String(*other.string);
        }
        // by convention, always return *this
        return *this;
      }

      void fillData(void)
      {
        string = new gul::String("TEST String");
      }

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
}
SPECIALIZE_TRAITS(TestXMLManager::TestClassString)
DEFINE_RTTI(TestXMLManager::TestClassString)


BEGIN_SAVE(TestXMLManager::TestClassString)
SAVE_VARIABLE(string)
END_SAVE(TestXMLManager::TestClassString)

BEGIN_LOAD(TestXMLManager::TestClassString)
LOAD_VARIABLE(string)
END_LOAD(TestXMLManager::TestClassString)

namespace TestXMLManager
{
  class TestClassPrimitives : INHERIT_SERIALIZABLE(TestClassPrimitives)
  {
      DECLARE_RTTI(TestClassPrimitives)

    public:
      TestClassPrimitives(void)
        : integer(0), character(' '), floatingPoint(0.f), doublePrecision(0.), boolean(false)
      {}

      virtual ~TestClassPrimitives(void) {}

      void fillData(void)
      {
        integer = -1;
        character = 'a';
        floatingPoint = 1.2345f;
        doublePrecision = 1.2345;
        boolean = true;
      }

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

}
SPECIALIZE_TRAITS(TestXMLManager::TestClassPrimitives)
DEFINE_RTTI(TestXMLManager::TestClassPrimitives)

BEGIN_SAVE(TestXMLManager::TestClassPrimitives)
SAVE_VARIABLE(integer)
SAVE_VARIABLE(character)
SAVE_VARIABLE(floatingPoint)
SAVE_VARIABLE(doublePrecision)
SAVE_VARIABLE(boolean)
END_SAVE(TestXMLManager::TestClassPrimitives)

BEGIN_LOAD(TestXMLManager::TestClassPrimitives)
LOAD_VARIABLE(integer)
LOAD_VARIABLE(character)
LOAD_VARIABLE(floatingPoint)
LOAD_VARIABLE(doublePrecision)
LOAD_VARIABLE(boolean)
END_LOAD(TestXMLManager::TestClassPrimitives)

namespace TestXMLManager
{
  class TestNestedClass : INHERIT_SERIALIZABLE(TestNestedClass)
  {
      DECLARE_RTTI(TestNestedClass)

    public:
      TestNestedClass(void)
        : integer(0) {}

      virtual ~TestNestedClass(void) {}

      void fillData(void)
      {
        integer = 20;
        stringClass.fillData();
        primClass.fillData();
      }

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
}
SPECIALIZE_TRAITS(TestXMLManager::TestNestedClass)
DEFINE_RTTI(TestXMLManager::TestNestedClass)

BEGIN_SAVE(TestXMLManager::TestNestedClass)
SAVE_VARIABLE(integer)
SAVE_VARIABLE(stringClass)
SAVE_VARIABLE(primClass)
END_SAVE(TestXMLManager::TestNestedClass)

BEGIN_LOAD(TestXMLManager::TestNestedClass)
LOAD_VARIABLE(integer)
LOAD_VARIABLE(stringClass)
LOAD_VARIABLE(primClass)
END_LOAD(TestXMLManager::TestNestedClass)

namespace TestXMLManager
{
  class TestPointerClass : INHERIT_SERIALIZABLE(TestPointerClass)
  {
      DECLARE_RTTI(TestPointerClass)

    public:
      TestPointerClass(void)
        : pointer(nullptr) {}

      virtual ~TestPointerClass(void) {}

      void fillData(void)
      {
        pointer = new TestNestedClass();
        pointer->fillData();
      }

      bool operator==(const TestPointerClass& o) const
      {
        return (pointer == nullptr && o.pointer == nullptr) ||
               (pointer != nullptr && o.pointer != nullptr && *pointer == *o.pointer);
      }

      bool operator!=(const TestPointerClass& o) const
      {
        return !operator ==(o);
      }

      TestNestedClass* GetPointer(void)
      {
        return pointer;
      }

    private:
      TestNestedClass* pointer;
      DECLARE_SERIALIZABLE()
  };
}

SPECIALIZE_TRAITS(TestXMLManager::TestPointerClass)
DEFINE_RTTI(TestXMLManager::TestPointerClass)

BEGIN_SAVE(TestXMLManager::TestPointerClass)
SAVE_VARIABLE(pointer)
END_SAVE(TestXMLManager::TestPointerClass)

BEGIN_LOAD(TestXMLManager::TestPointerClass)
LOAD_VARIABLE(pointer)
END_LOAD(TestXMLManager::TestPointerClass)

namespace TestXMLManager
{
  class TestSamePointersClass : INHERIT_SERIALIZABLE(TestSamePointersClass)
  {
      DECLARE_RTTI(TestSamePointersClass)

    public:
      TestSamePointersClass(void)
        : nestedPointer(nullptr),
          pointer(nullptr) {}

      virtual ~TestSamePointersClass(void) {}

      void fillData(void)
      {
        pointer = new TestPointerClass();
        pointer->fillData();
        nestedPointer = pointer->GetPointer();
      }

      bool operator==(const TestSamePointersClass& o) const
      {
        return ((pointer == nullptr && o.pointer == nullptr) ||
                (pointer != nullptr && o.pointer != nullptr && *pointer == *o.pointer))
               &&
               ((nestedPointer == nullptr && o.nestedPointer == nullptr) ||
                (nestedPointer != nullptr && o.nestedPointer != nullptr && *nestedPointer == *o.nestedPointer))
               &&
               nestedPointer == pointer->GetPointer();
      }

      bool operator!=(const TestSamePointersClass& o) const
      {
        return !operator ==(o);
      }

    private:
      TestNestedClass* nestedPointer;
      TestPointerClass* pointer;
      DECLARE_SERIALIZABLE()
  };
}

SPECIALIZE_TRAITS(TestXMLManager::TestSamePointersClass)
DEFINE_RTTI(TestXMLManager::TestSamePointersClass)

BEGIN_SAVE(TestXMLManager::TestSamePointersClass)
SAVE_VARIABLE(pointer)
SAVE_VARIABLE(nestedPointer)
END_SAVE(TestXMLManager::TestSamePointersClass)

BEGIN_LOAD(TestXMLManager::TestSamePointersClass)
LOAD_VARIABLE(pointer)
LOAD_VARIABLE(nestedPointer)
END_LOAD(TestXMLManager::TestSamePointersClass)

namespace TestXMLManager
{

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

  int SaveAndLoadPointerClass(void)
  {
    TestPointerClass pointerFalseReference;
    TestPointerClass pointerTruth;
    pointerTruth.fillData();
    gul::XMLManager::Save(gul::String("pointerTest.xml"), pointerTruth);
    TestPointerClass* pPointerLoaded = gul::XMLManager::Load<TestPointerClass>(gul::String("pointerTest.xml"));

    TEST_NOT_EQUAL(*pPointerLoaded, pointerFalseReference);
    TEST_EQUAL(*pPointerLoaded, pointerTruth);
    TEST_FALSE(*pPointerLoaded != pointerTruth);

    GUL_DELETE(pPointerLoaded);

    return EXIT_SUCCESS;
  }

  int SaveAndLoadSamePointers(void)
  {
    TestSamePointersClass falseReference;
    TestSamePointersClass truth;
    truth.fillData();
    gul::XMLManager::Save(gul::String("samePointerTest.xml"), truth);
    TestSamePointersClass* pLoaded = gul::XMLManager::Load<TestSamePointersClass>(gul::String("samePointerTest.xml"));

    TEST_NOT_EQUAL(*pLoaded, falseReference);
    TEST_EQUAL(*pLoaded, truth);
    TEST_FALSE(*pLoaded != truth);

    GUL_DELETE(pLoaded);

    return EXIT_SUCCESS;
  }
}

