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
#include "SettingsManager.h"
#include "File.h"

namespace TestSettingsManager
{
  int Overwrite(void)
  {
    {
      gul::SettingsManager m(gul::File("test.config"));
      m.Write(gul::String("int2"), 2);
      m.Write(gul::String("float-100"), -100.0);
      m.Write(gul::String("string"), gul::String("a String"));
    }
    {
      gul::SettingsManager m(gul::File("test.config"));
      TEST_EQUAL(m.ReadInt(gul::String("int2")), 2);
      TEST_EQUAL(m.ReadFloat(gul::String("float-100")), -100.0);
      TEST_EQUAL(m.ReadString(gul::String("string")), gul::String("a String"));

      m.Write(gul::String("int2"), -2);
      m.Write(gul::String("float-100"), -1.0);
      m.Write(gul::String("string"), gul::String("a new String"));
    }
    {
      gul::SettingsManager m(gul::File("test.config"));
      TEST_EQUAL(m.ReadInt(gul::String("int2")), -2);
      TEST_EQUAL(m.ReadFloat(gul::String("float-100")), -1.0);
      TEST_EQUAL(m.ReadString(gul::String("string")), gul::String("a new String"));
    }

    return EXIT_SUCCESS;
  }

  int Contains(void)
  {
    {
      gul::SettingsManager m(gul::File("test.config"));
      TEST_FALSE(m.Contains(gul::String("int2")));
      m.Write(gul::String("int2"), 2);
    }

    {
      gul::SettingsManager m(gul::File("test.config"));
      TEST_TRUE(m.Contains(gul::String("int2")));
      TEST_FALSE(m.Contains(gul::String("anything")));
    }

    return EXIT_SUCCESS;
  }

  int Clear(void)
  {
    {
      gul::SettingsManager m(gul::File("test.config"));
      m.Write(gul::String("int2"), 2);
      TEST_EQUAL(m.ReadInt(gul::String("int2")), 2);
    }

    {
      gul::SettingsManager m(gul::File("test.config"));
      m.Clear();
    }

    {
      gul::SettingsManager m(gul::File("test.config"));
      TEST_FALSE(m.Contains(gul::String("int2")));
    }

    return EXIT_SUCCESS;
  }

  int ReadWriteNumerics(void)
  {
    {
      gul::SettingsManager m(gul::File("test.config"));
      m.Write(gul::String("int2"), 2);
      m.Write(gul::String("int-100"), -100);
      m.Write(gul::String("int0"), 0);

      m.Write(gul::String("float2"), 2.0);
      m.Write(gul::String("float-100"), -100.0);
      m.Write(gul::String("float0"), 0.0);
    }

    {
      gul::SettingsManager m(gul::File("test.config"));
      TEST_EQUAL(m.ReadInt(gul::String("int2")), 2);
      TEST_EQUAL(m.ReadInt(gul::String("int-100")), -100);
      TEST_EQUAL(m.ReadInt(gul::String("int0")), 0);

      TEST_EQUAL(m.ReadInt(gul::String("float2")), 2.0);
      TEST_EQUAL(m.ReadInt(gul::String("float-100")), -100.0);
      TEST_EQUAL(m.ReadInt(gul::String("float0")), 0.0);
    }

    return EXIT_SUCCESS;
  }

  int ReadWriteStrings(void)
  {
    {
      gul::SettingsManager m(gul::File("test.config"));
      m.Write(gul::String("shortString"), gul::String("short"));
      m.Write(gul::String("longString"), gul::String("this is a long long long long string"));
      m.Write(gul::String("newlineString"), gul::String("one containing a\nnewline"));
      m.Write(gul::String("tabString"), gul::String("another containing a\ttab"));
    }

    {
      gul::SettingsManager m(gul::File("test.config"));
      TEST_EQUAL(m.ReadString(gul::String("shortString")), gul::String("short"));
      TEST_EQUAL(m.ReadString(gul::String("longString")), gul::String("this is a long long long long string"));
      TEST_EQUAL(m.ReadString(gul::String("newlineString")), gul::String("one containing a"));
      TEST_EQUAL(m.ReadString(gul::String("tabString")), gul::String("another containing a\ttab"));
    }
    return EXIT_SUCCESS;
  }
}
