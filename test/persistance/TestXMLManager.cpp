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

  class TestClassGUL : private gul::XMLSerializable
  {
    public:
      TestClassGUL(void)
        : string(new gul::String("TEST String")) {}

      bool operator==(const TestClassGUL& o) const
      {
        return  *string == *o.string;
      }

      bool operator!=(const TestClassGUL& o) const
      {
        return !operator ==(o);
      }

    private:
      gul::String* string;

      DECLARE_SERIALIZABLE()
  };
//  REGISTER_CLASS_FACTORY(TestClassGUL)

  BEGIN_SAVE(TestClassGUL)
//  SAVE_POINTER(string)
  END_SAVE(TestClassGUL)

  BEGIN_LOAD(TestClassGUL)
//  LOAD_POINTER(string, gul::String)
  END_LOAD(TestClassGUL)

  class TestClassPrimitives : private gul::XMLSerializable
  {
    public:
      TestClassPrimitives(void)
        : integer(-1), character('a'), floatingPoint(1.2345f), doublePrecision(1.2345), boolean(true)
      {}

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
//  REGISTER_CLASS_FACTORY(TestClassPrimitives)

  BEGIN_SAVE(TestClassPrimitives)
//  SAVE_PRIMITIVE(integer)
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

  class TestNestedClass : private gul::XMLSerializable
  {
    public:
      TestNestedClass(void)
        : integer(20) {}

      bool operator==(const TestNestedClass& o) const
      {
        return  integer == o.integer &&
                gulClass == o.gulClass &&
                primClass == o.primClass;
      }

      bool operator!=(const TestNestedClass& o) const
      {
        return !operator ==(o);
      }

    private:
      int integer;
      TestClassGUL gulClass;
      TestClassPrimitives primClass;
      DECLARE_SERIALIZABLE()

  };
//  REGISTER_CLASS_FACTORY(TestNestedClass)

  BEGIN_SAVE(TestNestedClass)
//  SAVE_PRIMITIVE(integer)
  SAVE_VARIABLE(gulClass)
  SAVE_VARIABLE(primClass)
  END_SAVE(TestNestedClass)

  BEGIN_LOAD(TestNestedClass)
  LOAD_PRIMITIVE(integer)
//  LOAD_VARIABLE(gulClass, TestClassGUL)
//  LOAD_VARIABLE(primClass, TestClassPrimitives)
  END_LOAD(TestNestedClass)





  int SaveAndLoadXML(void)
  {
    TestNestedClass a;
    gul::XMLManager::Save(gul::String("test.xml"), a);
    TestNestedClass* ab = gul::XMLManager::Load<TestNestedClass>(gul::String("test.xml"));

    TEST_EQUAL(a, *ab);

    return EXIT_SUCCESS;
  }
}
