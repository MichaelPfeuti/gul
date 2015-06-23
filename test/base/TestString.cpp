/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2015 Michael Pfeuti.
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
#include "String.h"
#include "RTTI.h"
#include <cstring>

namespace TestString
{

  int Size(void)
  {
    TEST_EQUAL(gul::String("").Size(), 0);
    TEST_EQUAL(gul::String("Test").Size(), 4);
    TEST_EQUAL(gul::String("String").Size(), 6);
    TEST_EQUAL(gul::String("TestStringSearch").Size(), 16);

    return EXIT_SUCCESS;
  }

  int Construction(void)
  {
    gul::String string("");
    gul::String string1("Test");
    gul::String string2("String");

    TEST_TRUE(strcmp(string.GetData(), "") == 0);
    TEST_TRUE(strcmp(string1.GetData(), "Test") == 0);
    TEST_TRUE(strcmp(string2.GetData(), "String") == 0);

    TEST_EQUAL(string, gul::String(""));
    TEST_EQUAL(string1, gul::String("Test"));
    TEST_EQUAL(string2, gul::String("String"));

    return EXIT_SUCCESS;
  }

  int Concatenation(void)
  {
    gul::String string("");
    gul::String string1("Test");
    gul::String string2("String");

    TEST_EQUAL(string + string1, gul::String("Test"));
    TEST_EQUAL(string1 + string, gul::String("Test"));

    TEST_EQUAL(string + string, gul::String(""));
    TEST_EQUAL(string1 + string1, gul::String("TestTest"));
    TEST_EQUAL(string2 + string2, gul::String("StringString"));

    TEST_EQUAL(string1 + string2, gul::String("TestString"));
    TEST_EQUAL(string2 + string1, gul::String("StringTest"));

    TEST_EQUAL(string + string2, gul::String("String"));
    TEST_EQUAL(string2 + string, gul::String("String"));

    TEST_NOT_EQUAL(string1 + string2, gul::String("Test"));

    return EXIT_SUCCESS;
  }

  int PlaceHolder(void)
  {
    TEST_EQUAL(gul::String("Test%").Arg(1), gul::String("Test1"));
    TEST_EQUAL(gul::String("Test%").Arg(99), gul::String("Test99"));
    TEST_EQUAL(gul::String("Test%").Arg(1.2345, 4), gul::String("Test1.2345"));
    TEST_EQUAL(gul::String("Test%").Arg(gul::String("Repl")), gul::String("TestRepl"));

    TEST_EQUAL(gul::String("Test%Test").Arg(1), gul::String("Test1Test"));
    TEST_EQUAL(gul::String("Test%Test").Arg(99), gul::String("Test99Test"));
    TEST_EQUAL(gul::String("Test%Test").Arg(1.2345, 4), gul::String("Test1.2345Test"));
    TEST_EQUAL(gul::String("Test%Test").Arg(gul::String("Repl")), gul::String("TestReplTest"));

    TEST_EQUAL(gul::String("%Test").Arg(1), gul::String("1Test"));
    TEST_EQUAL(gul::String("%Test").Arg(99), gul::String("99Test"));
    TEST_EQUAL(gul::String("%Test").Arg(1.2345, 4), gul::String("1.2345Test"));
    TEST_EQUAL(gul::String("%Test").Arg(gul::String("Repl")), gul::String("ReplTest"));

    TEST_EQUAL(gul::String("Test%Test%").Arg(99).Arg(1.2345, 4), gul::String("Test99Test1.2345"));
    TEST_EQUAL(gul::String("%Test%Test").Arg(99).Arg(1.2345, 4), gul::String("99Test1.2345Test"));

    TEST_EQUAL(gul::String("Test%%Test").Arg(1).Arg(1.2345, 4), gul::String("Test11.2345Test"));
    TEST_EQUAL(gul::String("%%TestTest").Arg(1.2345, 4).Arg(1), gul::String("1.23451TestTest"));
    TEST_EQUAL(gul::String("TestTest%%").Arg(99).Arg(1.2345, 4), gul::String("TestTest991.2345"));

    TEST_EQUAL(gul::String("Test%%Test").Arg(true).Arg(false), gul::String("TesttruefalseTest"));
    TEST_EQUAL(gul::String("%%TestTest").Arg(false).Arg(true), gul::String("falsetrueTestTest"));
    TEST_EQUAL(gul::String("TestTest%%").Arg(true).Arg(false), gul::String("TestTesttruefalse"));

    return EXIT_SUCCESS;
  }

  int PlaceHolderPrecision(void)
  {
    double val = 123.456789102345;
    TEST_EQUAL(gul::String("%").Arg(val), gul::String("123.456789"));
    TEST_EQUAL(gul::String("%").Arg(val, 0), gul::String("123"));
    TEST_EQUAL(gul::String("%").Arg(val, 3), gul::String("123.457"));
    TEST_EQUAL(gul::String("%").Arg(val, 12), gul::String("123.456789102345"));

    return EXIT_SUCCESS;
  }

  int ReplaceRange(void)
  {
    gul::String string("TestStringSearch");

    TEST_EQUAL(string.Replace(gul::String("GONE"), 0, 3), gul::String("GONEStringSearch"));
    TEST_EQUAL(string.Replace(gul::String("GONE"), 4, 9), gul::String("TestGONESearch"));
    TEST_EQUAL(string.Replace(gul::String("GONE"), 10, string.Size() - 1), gul::String("TestStringGONE"));

    return EXIT_SUCCESS;
  }

  int ReplaceString(void)
  {
    gul::String string1("SEARCHTestString");
    gul::String string2("TestSEARCHString");
    gul::String string3("TestStringSEARCH");
    gul::String string4("SEARCHStringSEARCH");

    TEST_EQUAL(string1.Replace(gul::String("GONE"), gul::String("SEARCH")), gul::String("GONETestString"));
    TEST_EQUAL(string2.Replace(gul::String("GONE"), gul::String("SEARCH")), gul::String("TestGONEString"));
    TEST_EQUAL(string3.Replace(gul::String("GONE"), gul::String("SEARCH")), gul::String("TestStringGONE"));
    TEST_EQUAL(string4.Replace(gul::String("GONE"), gul::String("SEARCH")), gul::String("GONEStringSEARCH"));

    return EXIT_SUCCESS;
  }

  int ReplaceStringBackward(void)
  {
    gul::String string1("SEARCHTestString");
    gul::String string2("TestSEARCHString");
    gul::String string3("TestStringSEARCH");
    gul::String string4("SEARCHStringSEARCH");

    TEST_EQUAL(string1.ReplaceBackward(gul::String("GONE"), gul::String("SEARCH")), gul::String("GONETestString"));
    TEST_EQUAL(string2.ReplaceBackward(gul::String("GONE"), gul::String("SEARCH")), gul::String("TestGONEString"));
    TEST_EQUAL(string3.ReplaceBackward(gul::String("GONE"), gul::String("SEARCH")), gul::String("TestStringGONE"));
    TEST_EQUAL(string4.ReplaceBackward(gul::String("GONE"), gul::String("SEARCH")), gul::String("SEARCHStringGONE"));

    return EXIT_SUCCESS;
  }

  int ReplaceStringAll(void)
  {
    gul::String string1("SEARCHTestString");
    gul::String string2("TestSEARCHString");
    gul::String string3("TestStringSEARCH");
    gul::String string4("SEARCHStringSEARCH");
    gul::String string5("SEARCHSEARCHSEARCH");

    TEST_EQUAL(string1.ReplaceAll(gul::String("GONE"), gul::String("SEARCH")), gul::String("GONETestString"));
    TEST_EQUAL(string2.ReplaceAll(gul::String("GONE"), gul::String("SEARCH")), gul::String("TestGONEString"));
    TEST_EQUAL(string3.ReplaceAll(gul::String("GONE"), gul::String("SEARCH")), gul::String("TestStringGONE"));
    TEST_EQUAL(string4.ReplaceAll(gul::String("GONE"), gul::String("SEARCH")), gul::String("GONEStringGONE"));
    TEST_EQUAL(string5.ReplaceAll(gul::String("GONE"), gul::String("SEARCH")), gul::String("GONEGONEGONE"));

    return EXIT_SUCCESS;
  }

  int Substring(void)
  {
    gul::String string("StartMiddleEnd");

    TEST_EQUAL(string.Substring(0, 5), gul::String("Start"));
    TEST_EQUAL(string.Substring(5, 11), gul::String("Middle"));
    TEST_EQUAL(string.Substring(11, 14), gul::String("End"));

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
    gul::String string4("TestString");

    TEST_EQUAL(string1.Find(gul::String("SEARCH")), 0);
    TEST_EQUAL(string2.Find(gul::String("SEARCH")), 4);
    TEST_EQUAL(string3.Find(gul::String("SEARCH")), 10);
    TEST_EQUAL(string4.Find(gul::String("SEARCH")), -1);

    return EXIT_SUCCESS;
  }

  int FindBackward(void)
  {
    gul::String string1("SEARCHTestString");
    gul::String string2("TestSEARCHString");
    gul::String string3("TestStringSEARCH");
    gul::String string4("TestString");

    TEST_EQUAL(string1.FindBackward(gul::String("SEARCH")), 0);
    TEST_EQUAL(string2.FindBackward(gul::String("SEARCH")), 4);
    TEST_EQUAL(string3.FindBackward(gul::String("SEARCH")), 10);
    TEST_EQUAL(string4.FindBackward(gul::String("SEARCH")), -1);

    return EXIT_SUCCESS;
  }

  int Count(void)
  {
    gul::String string1("SEARCHTestString");
    gul::String string2("TestSEARCHSEARCH");
    gul::String string3("SEARCHStringSEARCH");
    gul::String string4("SEARCHSEARCHSEARCH");
    gul::String string5("TestString");

    TEST_EQUAL(string1.Count(gul::String("SEARCH")), 1);
    TEST_EQUAL(string2.Count(gul::String("SEARCH")), 2);
    TEST_EQUAL(string3.Count(gul::String("SEARCH")), 2);
    TEST_EQUAL(string4.Count(gul::String("SEARCH")), 3);
    TEST_EQUAL(string5.Count(gul::String("SEARCH")), 0);

    return EXIT_SUCCESS;
  }

  int LowerCase(void)
  {
    gul::String string("This Is A Mixed Case String!");

    TEST_EQUAL(string.LowerCase(), "this is a mixed case string!");

    return EXIT_SUCCESS;
  }

  int Traits(void)
  {
    TEST_EQUAL(gul::Traits<gul::String>::GetName(), gul::String("gul::String"));
    return EXIT_SUCCESS;
  }

  int RTTI(void)
  {
    gul::String string;
    TEST_EQUAL(string.GetRTTI().GetName(), gul::Traits<gul::String>::GetName());

    return EXIT_SUCCESS;
  }

  int Assignment(void)
  {
    gul::String str1("STRING1");
    gul::String str2("STRING2");
    gul::String str3("STRING3");

    TEST_NOT_EQUAL(str1, str2);
    str2 = str1;
    TEST_EQUAL(str1, str2);

    TEST_NOT_EQUAL(str2, str3);
    str2 = str3;
    TEST_NOT_EQUAL(str2, str1);
    TEST_EQUAL(str2, str3);

    return EXIT_SUCCESS;
  }

  int ToLong(void)
  {
    long val = 1234567890123456789;
    gul::String str1("1234567890123456789");
    gul::String str2 = gul::String("%").Arg(val);

    TEST_EQUAL(str1.ToLong(), val);
    TEST_EQUAL(str2.ToLong(), val);

    return EXIT_SUCCESS;
  }

  int ToDouble(void)
  {
    double val = 12345.06789;
    gul::String str1("12345.06789");
    gul::String str2 = gul::String("%").Arg(val);

    TEST_EQUAL(str1.ToDouble(), val);
    TEST_EQUAL(str2.ToDouble(), val);

    return EXIT_SUCCESS;
  }

  int ToBool(void)
  {
    bool valTrue = true;
    bool valFalse = false;
    gul::String str1True("truE");
    gul::String str1False("fAlse");
    gul::String str1Yes("yEs");
    gul::String str1No("nO");
    gul::String str1On("oN");
    gul::String str1Off("oFf");
    gul::String str2True = gul::String("%").Arg(valTrue);
    gul::String str2False = gul::String("%").Arg(valFalse);

    TEST_EQUAL(str1True.ToBool(), valTrue);
    TEST_EQUAL(str1False.ToBool(), valFalse);
    TEST_EQUAL(str1Yes.ToBool(), valTrue);
    TEST_EQUAL(str1No.ToBool(), valFalse);
    TEST_EQUAL(str1On.ToBool(), valTrue);
    TEST_EQUAL(str1Off.ToBool(), valFalse);
    TEST_EQUAL(str2True.ToBool(), valTrue);
    TEST_EQUAL(str2False.ToBool(), valFalse);

    return EXIT_SUCCESS;
  }

}

