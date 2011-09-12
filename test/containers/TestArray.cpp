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
#include "Array.h"

namespace {

int testSizeAndIsEmpty(void)
{
  gul::Array<int> array;
  TEST_EQUAL(array.Size(), 0);
  TEST_TRUE(array.IsEmpty());

  array.Add(0);
  TEST_EQUAL(array.Size(), 1);
  TEST_FALSE(array.IsEmpty());

  array.Add(0);
  TEST_EQUAL(array.Size(), 2);
  TEST_FALSE(array.IsEmpty());

  array.Remove(0);
  TEST_EQUAL(array.Size(), 1);
  TEST_FALSE(array.IsEmpty());

  array.Remove(0);
  TEST_EQUAL(array.Size(), 0);
  TEST_TRUE(array.IsEmpty());

  return EXIT_SUCCESS;
}

int testAdd(void)
{
  gul::Array<int> array;
  TEST_EQUAL(array.Size(), 0);
  TEST_TRUE(array.IsEmpty());

  array.Add(0);
  TEST_EQUAL(array.Size(), 1);
  TEST_EQUAL(array.Get(0), 0);

  array.Add(1);
  TEST_EQUAL(array.Size(), 2);
  TEST_EQUAL(array.Get(0), 0);
  TEST_EQUAL(array.Get(1), 1);

  return EXIT_SUCCESS;
}

int testAddIndex(void)
{
  gul::Array<int> array;
  TEST_EQUAL(array.Size(), 0);
  TEST_TRUE(array.IsEmpty());

  array.Add(0,10);
  TEST_EQUAL(array.Size(), 1);
  TEST_EQUAL(array.Get(0), 0);

  array.Add(1,1);
  TEST_EQUAL(array.Size(), 2);
  TEST_EQUAL(array.Get(0), 0);
  TEST_EQUAL(array.Get(1), 1);

  array.Add(2,10);
  TEST_EQUAL(array.Size(), 3);
  TEST_EQUAL(array.Get(0), 0);
  TEST_EQUAL(array.Get(1), 1);
  TEST_EQUAL(array.Get(2), 2);

  array.Add(3,1);
  TEST_EQUAL(array.Size(), 4);
  TEST_EQUAL(array.Get(0), 0);
  TEST_EQUAL(array.Get(1), 3);
  TEST_EQUAL(array.Get(2), 1);
  TEST_EQUAL(array.Get(3), 2);

  array.Add(4,1);
  TEST_EQUAL(array.Size(), 5);
  TEST_EQUAL(array.Get(0), 4);
  TEST_EQUAL(array.Get(1), 0);
  TEST_EQUAL(array.Get(2), 3);
  TEST_EQUAL(array.Get(3), 1);
  TEST_EQUAL(array.Get(4), 2);

  return EXIT_SUCCESS;
}

int testAddIndexAssertion(void)
{
  gul::Array<int> array;
  TEST_ASSERTION(array.Add(5, -1));

  return EXIT_SUCCESS;
}

int testRemoveIndex(void)
{
  gul::Array<int> array;
  for(int i = 0; i < 5; ++i) array.Add(i+1);

  TEST_EQUAL(array.Size(), 5);

  array.Remove(0);
  TEST_EQUAL(array.Size(), 4);
  TEST_EQUAL(array.Get(0), 1);
  TEST_EQUAL(array.Get(1), 2);
  TEST_EQUAL(array.Get(2), 3);
  TEST_EQUAL(array.Get(3), 4);

  array.Remove(2);
  TEST_EQUAL(array.Size(), 3);
  TEST_EQUAL(array.Get(0), 1);
  TEST_EQUAL(array.Get(1), 2);
  TEST_EQUAL(array.Get(2), 4);

  array.Remove(2);
  TEST_EQUAL(array.Size(), 2);
  TEST_EQUAL(array.Get(0), 1);
  TEST_EQUAL(array.Get(1), 2);

  return EXIT_SUCCESS;
}

int testRemoveIndexAssertion(void)
{
  gul::Array<int> array;

  TEST_ASSERTION(array.Remove(0));

  array.Add(0);
  array.Add(1);

  TEST_ASSERTION(array.Remove(2));
  TEST_ASSERTION(array.Remove(-1));

  return EXIT_SUCCESS;
}

int testRemoveElement(void)
{
  gul::Array<int> array;
  for(int i = 0; i < 5; ++i) array.Add(i+1);

  TEST_EQUAL(array.Size(), 5);

  array.RemoveElement(0);
  TEST_EQUAL(array.Size(), 4);
  TEST_EQUAL(array.Get(0), 1);
  TEST_EQUAL(array.Get(1), 2);
  TEST_EQUAL(array.Get(2), 3);
  TEST_EQUAL(array.Get(3), 4);

  array.RemoveElement(2);
  TEST_EQUAL(array.Size(), 3);
  TEST_EQUAL(array.Get(0), 1);
  TEST_EQUAL(array.Get(1), 3);
  TEST_EQUAL(array.Get(2), 4);

  array.Remove(4);
  TEST_EQUAL(array.Size(), 2);
  TEST_EQUAL(array.Get(0), 1);
  TEST_EQUAL(array.Get(1), 2);

  return EXIT_SUCCESS;
}

int testRemoveElementAssertion(void)
{
  gul::Array<int> array;

  TEST_ASSERTION(array.RemoveElement(0));

  array.Add(0);
  array.Add(1);

  TEST_ASSERTION(array.RemoveElement(2));
  TEST_ASSERTION(array.RemoveElement(-1));

  return EXIT_SUCCESS;
}

int testClear(void)
{
  gul::Array<int> array;
  for(int i = 0; i < 5; ++i) array.Add(i);

  TEST_EQUAL(array.Size(), 5);

  array.Clear();

  TEST_EQUAL(array.Size(), 0);
  TEST_TRUE(array.IsEmpty());

  return EXIT_SUCCESS;
}

int testIndexOf(void)
{
  gul::Array<int> array;
  for(int i = 0; i < 5; ++i) array.Add(i+1);

  for(int i = 0; i < 5; ++i)
  {
    TEST_EQUAL(array.IndexOf(i+1), i);
  }

  TEST_EQUAL(array.IndexOf(5), gul::NOT_FOUND);
  TEST_EQUAL(array.IndexOf(-1), gul::NOT_FOUND);

  return EXIT_SUCCESS;
}

int testContains(void)
{
  gul::Array<int> array;
  for(int i = 0; i < 5; ++i) array.Add(i+1);

  for(int i = 0; i < 5; ++i)
  {
    TEST_TRUE(array.Contains(i+1));
  }

  TEST_FALSE(array.Contains(5));
  TEST_FALSE(array.Contains(-1));

  return EXIT_SUCCESS;
}

}

int TestArray(const std::string& rTestName)
{
    if(rTestName == "SizeAndIsEmpty") return testSizeAndIsEmpty();
    if(rTestName == "Add") return testAdd();
    if(rTestName == "AddIndex") return testAddIndex();
    if(rTestName == "AddIndexAssertion") return testAddIndexAssertion();
    if(rTestName == "RemoveIndex") return testRemoveIndex();
    if(rTestName == "RemoveIndexAssertion") return testRemoveIndexAssertion();
    if(rTestName == "RemoveElement") return testRemoveElement();
    if(rTestName == "RemoveElementAssertion") return testRemoveElementAssertion();
    if(rTestName == "Clear") return testClear();
    if(rTestName == "IndexOf") return testIndexOf();
    if(rTestName == "Contains") return testContains();

    TEST_END();
}
