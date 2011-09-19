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
#include "String.h"

namespace TestString
{

int Concatenation(void)
{
  gul::String string1("Test");
  gul::String string2("String");

  TEST_EQUAL(string1+string2, gul::String("TestString"));
  TEST_NOT_EQUAL(string1+string2, gul::String("Test"));

  return EXIT_SUCCESS;
}

int PlaceHolder(void)
{
  TEST_EQUAL(gul::String("Test%").Arg(1), gul::String("Test1"));
  TEST_EQUAL(gul::String("Test%").Arg(99), gul::String("Test99"));
  TEST_EQUAL(gul::String("Test%").Arg(1.2345), gul::String("Test1.2345"));

  TEST_EQUAL(gul::String("Test%Test").Arg(1), gul::String("Test1Test"));
  TEST_EQUAL(gul::String("Test%Test").Arg(99), gul::String("Test99Test"));
  TEST_EQUAL(gul::String("Test%Test").Arg(1.2345), gul::String("Test1.2345Test"));

  TEST_EQUAL(gul::String("%Test").Arg(1), gul::String("1Test"));
  TEST_EQUAL(gul::String("%Test").Arg(99), gul::String("99Test"));
  TEST_EQUAL(gul::String("%Test").Arg(1.2345), gul::String("1.2345Test"));

  TEST_EQUAL(gul::String("Test%Test%").Arg(99).Arg(1.2345), gul::String("Test99Test1.2345"));
  TEST_EQUAL(gul::String("%Test%Test").Arg(99).Arg(1.2345), gul::String("99Test1.2345Test"));

  TEST_EQUAL(gul::String("Test%%Test").Arg(1).Arg(1.2345), gul::String("Test11.2345Test"));
  TEST_EQUAL(gul::String("%%TestTest").Arg(1.2345).Arg(1), gul::String("1.23451TestTest"));
  TEST_EQUAL(gul::String("TestTest%%").Arg(99).Arg(1.2345), gul::String("TestTest991.2345"));

  return EXIT_SUCCESS;
}

int ReplaceRange(void)
{
  gul::String string("TestStringSearch");

  TEST_EQUAL(string.Replace(gul::String("GONE"), 0, 3), gul::String("GONEStringSearch"));
  TEST_EQUAL(string.Replace(gul::String("GONE"), 4, 9), gul::String("TestGONESearch"));
  TEST_EQUAL(string.Replace(gul::String("GONE"), 10, string.Size()), gul::String("TestStringGONE"));

  return EXIT_SUCCESS;
}

int ReplaceString(void)
{
  gul::String string1("SEARCHTestString");
  gul::String string2("TestSEARCHString");
  gul::String string3("TestStringSEARCH");

  TEST_EQUAL(string1.Replace(gul::String("GONE"), gul::String("SEARCH")), gul::String("GONETestString"));
  TEST_EQUAL(string2.Replace(gul::String("GONE"), gul::String("SEARCH")), gul::String("TestGONEString"));
  TEST_EQUAL(string3.Replace(gul::String("GONE"), gul::String("SEARCH")), gul::String("TestStringGONE"));

  return EXIT_SUCCESS;
}

int CharAt(void)
{
  gul::String string("TestString");

  TEST_EQUAL(string.CharAt(0), 'T');
  TEST_EQUAL(string.CharAt(1), 'e');
  TEST_EQUAL(string.CharAt(2), 's');
  TEST_EQUAL(string.CharAt(3), 't');
  TEST_EQUAL(string.CharAt(4), 'S');
  TEST_EQUAL(string.CharAt(5), 't');
  TEST_EQUAL(string.CharAt(6), 'r');
  TEST_EQUAL(string.CharAt(7), 'i');
  TEST_EQUAL(string.CharAt(8), 'n');
  TEST_EQUAL(string.CharAt(9), 'g');

  return EXIT_SUCCESS;
}

int Find(void)
{
  gul::String string1("SEARCHTestString");
  gul::String string2("TestSEARCHString");
  gul::String string3("TestStringSEARCH");

  TEST_EQUAL(string1.Find(gul::String("SEARCH")), 0);
  TEST_EQUAL(string2.Find(gul::String("SEARCH")), 4);
  TEST_EQUAL(string3.Find(gul::String("SEARCH")), 10);

  return EXIT_SUCCESS;
}

}
