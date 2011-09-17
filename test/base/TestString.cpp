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

namespace
{

int testConcatenation(void)
{
  gul::String string1("Test");
  gul::String string2("String");

  TEST_EQUAL(string1+string2, gul::String("TestString"));
  TEST_NOT_EQUAL(string1+string2, gul::String("Test"));

  return EXIT_SUCCESS;
}

int testStringPlaceHolder(void)
{
  TEST_EQUAL(gul::String("Test%").Arg(1), gul::String("Test1"));
  TEST_EQUAL(gul::String("Test%").Arg(99), gul::String("Test99"));
  TEST_EQUAL(gul::String("Test%").Arg(1.2345), gul::String("Test1.2345"));

  return EXIT_SUCCESS;
}

int testStringReplaceRange(void)
{
  gul::String string("TestStringSearch");

  TEST_EQUAL(string.Replace(gul::String("GONE"), 0, 3), gul::String("GONEStringSearch"));
  TEST_EQUAL(string.Replace(gul::String("GONE"), 4, 9), gul::String("TestGONESearch"));
  TEST_EQUAL(string.Replace(gul::String("GONE"), 10, string.Size()), gul::String("TestStringGONE"));

  return EXIT_SUCCESS;
}

int testStringReplaceString(void)
{
  gul::String string1("TestSEARCHString");
  gul::String string2("SEARCHTestString");
  gul::String string3("TestStringSEARCH");

  TEST_EQUAL(string1.Replace(gul::String("GONE"), gul::String("SEARCH")), gul::String("TestGONEString"));
  TEST_EQUAL(string2.Replace(gul::String("GONE"), gul::String("SEARCH")), gul::String("GONETestString"));
  TEST_EQUAL(string3.Replace(gul::String("GONE"), gul::String("SEARCH")), gul::String("TestStringGONE"));

  return EXIT_SUCCESS;
}

int TestString(const std::string& rTestName)
{
  if(rTestName == "Concatenation") return testStringConcatenation();
  if(rTestName == "PlaceHolder") return testStringPlaceHolder();
  if(rTestName == "ReplaceString") return testStringReplaceString();
  if(rTestName == "ReplaceRange") return testStringReplaceRange();

  TEST_END();
}




