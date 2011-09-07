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

#include "String.h"
#include "CTestAssert.h"

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

}


int TestString(const std::string& rTestName)
{
  if(rTestName == "Concatenation") return testConcatenation();

  TEST_END();
}



