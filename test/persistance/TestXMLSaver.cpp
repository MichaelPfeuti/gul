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
#include "XMLSaver.h"
#include "XMLLoader.h"

namespace TestXMLSaver
{

class TestClassString : private gul::XMLSerializable
{
public:
  TestClassString(void)
    : string(new gul::String("TEST String")) {}
private:
  gul::String *string;

  DECLARE_SERIALIZABLE()
};
REGISTER_CLASS_FACTORY(TestClassString)

BEGIN_SAVE(TestClassString)
  SAVE_POINTER(string)
END_SAVE(TestClassString)

BEGIN_LOAD(TestClassString)
  LOAD_POINTER(string, gul::String)
END_LOAD(TestClassString)

class TestNestedClass : private gul::XMLSerializable
{
public:
  TestNestedClass(void)
    : integer(20) {}
private:
  int integer;
  TestClassString stringClass;
  DECLARE_SERIALIZABLE()

};
REGISTER_CLASS_FACTORY(TestNestedClass)

BEGIN_SAVE(TestNestedClass)
  SAVE_PRIMITIVE(integer)
  SAVE_VARIABLE(stringClass)
END_SAVE(TestNestedClass)

BEGIN_LOAD(TestNestedClass)
  LOAD_PRIMITIVE(integer)
  LOAD_VARIABLE(stringClass, TestClassString)
END_LOAD(TestNestedClass)


class TestClassPrimitives : private gul::XMLSerializable
{
  public:
    TestClassPrimitives(void)
      : integer(-1), character('a'), floatingPoint(1.2345f), doublePrecision(1.2345), boolean(true)
    {}

  private:
    int integer;
    char character;
    float floatingPoint;
    double doublePrecision;
    bool boolean;

  DECLARE_SERIALIZABLE()
};
REGISTER_CLASS_FACTORY(TestClassPrimitives)

BEGIN_SAVE(TestXMLSaver::TestClassPrimitives)
  SAVE_PRIMITIVE(integer)
  SAVE_PRIMITIVE(character)
  SAVE_PRIMITIVE(floatingPoint)
  SAVE_PRIMITIVE(doublePrecision)
  SAVE_PRIMITIVE(boolean)
END_SAVE(TestXMLSaver::TestClassPrimitives)

BEGIN_LOAD(TestXMLSaver::TestClassPrimitives)
  LOAD_PRIMITIVE(integer)
  LOAD_PRIMITIVE(character)
  LOAD_PRIMITIVE(floatingPoint)
  LOAD_PRIMITIVE(doublePrecision)
  LOAD_PRIMITIVE(boolean)
END_LOAD(TestXMLSaver::TestClassPrimitives)







int SaveXML(void)
{
  TestNestedClass a;
  gul::XMLSaver<TestNestedClass> saver(a);
  saver.Save(gul::String("test.xml"));

  gul::XMLLoader<TestNestedClass> loader;
  TestNestedClass* ab = loader.Load(gul::String("test.xml"));
  a = *ab;

  return EXIT_FAILURE;
}
}
