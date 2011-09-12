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
#include "Map.h"

namespace {

int testSize(void)
{
  /*gul::Map<int,int> map;
  TEST_TRUE(map.IsEmpty());
  TEST_EQUAL(map.Size(), 0);

  for(int i = 0; i<5; ++i)
  {
    map.Add(i, i+10);
    TEST_FALSE(map.IsEmpty());
    TEST_EQUAL(map.Size(), i+1);
  }

  return EXIT_SUCCESS;
  */
  return EXIT_FAILURE;
}

int testAdd(void)
{
    return EXIT_FAILURE;
}

int testInsert(void)
{
    return EXIT_FAILURE;
}

int testRemoveIndex(void)
{
    return EXIT_FAILURE;
}

int testRemoveElement(void)
{
    return EXIT_FAILURE;
}

int testClear(void)
{
    return EXIT_FAILURE;
}

int testIndexOf(void)
{
    return EXIT_FAILURE;
}

}

int TestMap(const std::string& rTestName)
{
    if(rTestName == "Size") return testSize();
    if(rTestName == "Add") return testAdd();
    if(rTestName == "Insert") return testInsert();
    if(rTestName == "RemoveIndex") return testRemoveIndex();
    if(rTestName == "RemoveElement") return testRemoveElement();
    if(rTestName == "Clear") return testClear();
    if(rTestName == "IndexOf") return testIndexOf();

    TEST_END();
}
