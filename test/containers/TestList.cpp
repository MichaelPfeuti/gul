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
#include "List.h"

namespace {

int testSizeAndIsEmpty(void)
{
  gul::List<int> list;
  TEST_EQUAL(list.Size(), 0);
  TEST_TRUE(list.IsEmpty());

  list.Add(0);
  TEST_EQUAL(list.Size(), 1);
  TEST_FALSE(list.IsEmpty());

  list.Add(0);
  TEST_EQUAL(list.Size(), 2);
  TEST_FALSE(list.IsEmpty());

  list.Remove(0);
  TEST_EQUAL(list.Size(), 1);
  TEST_FALSE(list.IsEmpty());

  list.Remove(0);
  TEST_EQUAL(list.Size(), 0);
  TEST_TRUE(list.IsEmpty());

  return EXIT_SUCCESS;
}

int testAdd(void)
{
  gul::List<int> list;
  TEST_EQUAL(list.Size(), 0);
  TEST_TRUE(list.IsEmpty());

  list.Add(0);
  TEST_EQUAL(list.Size(), 1);
  TEST_EQUAL(list.Get(0), 0);

  list.Add(1);
  TEST_EQUAL(list.Size(), 2);
  TEST_EQUAL(list.Get(0), 0);
  TEST_EQUAL(list.Get(1), 1);

  return EXIT_SUCCESS;
}

int testAddIndex(void)
{
  gul::List<int> list;
  TEST_EQUAL(list.Size(), 0);
  TEST_TRUE(list.IsEmpty());

  list.Add(0,10);
  TEST_EQUAL(list.Size(), 1);
  TEST_EQUAL(list.Get(0), 0);

  list.Add(1,1);
  TEST_EQUAL(list.Size(), 2);
  TEST_EQUAL(list.Get(0), 0);
  TEST_EQUAL(list.Get(1), 1);

  list.Add(2,10);
  TEST_EQUAL(list.Size(), 3);
  TEST_EQUAL(list.Get(0), 0);
  TEST_EQUAL(list.Get(1), 1);
  TEST_EQUAL(list.Get(2), 2);

  list.Add(3,1);
  TEST_EQUAL(list.Size(), 4);
  TEST_EQUAL(list.Get(0), 0);
  TEST_EQUAL(list.Get(1), 3);
  TEST_EQUAL(list.Get(2), 1);
  TEST_EQUAL(list.Get(3), 2);

  list.Add(4,1);
  TEST_EQUAL(list.Size(), 5);
  TEST_EQUAL(list.Get(0), 4);
  TEST_EQUAL(list.Get(1), 0);
  TEST_EQUAL(list.Get(2), 3);
  TEST_EQUAL(list.Get(3), 1);
  TEST_EQUAL(list.Get(4), 2);

  return EXIT_SUCCESS;
}

int testAddIndexAssertion(void)
{
  gul::List<int> list;
  TEST_ASSERTION(list.Add(5, -1));

  return EXIT_SUCCESS;
}

int testRemoveIndex(void)
{
  gul::List<int> list;
  for(int i = 0; i < 5; ++i) list.Add(i+1);

  TEST_EQUAL(list.Size(), 5);

  list.RemoveAt(0);
  TEST_EQUAL(list.Size(), 4);
  TEST_EQUAL(list.Get(0), 1);
  TEST_EQUAL(list.Get(1), 2);
  TEST_EQUAL(list.Get(2), 3);
  TEST_EQUAL(list.Get(3), 4);

  list.RemoveAt(2);
  TEST_EQUAL(list.Size(), 3);
  TEST_EQUAL(list.Get(0), 1);
  TEST_EQUAL(list.Get(1), 2);
  TEST_EQUAL(list.Get(2), 4);

  list.RemoveAt(2);
  TEST_EQUAL(list.Size(), 2);
  TEST_EQUAL(list.Get(0), 1);
  TEST_EQUAL(list.Get(1), 2);

  return EXIT_SUCCESS;
}

int testRemoveIndexAssertion(void)
{
  gul::List<int> list;

  TEST_ASSERTION(list.RemoveAt(0));

  list.add(0);
  list.add(1);

  TEST_ASSERTION(list.RemoveAt(2));
  TEST_ASSERTION(list.RemoveAt(-1));

  return EXIT_SUCCESS;
}

int testRemoveElement(void)
{
  gul::List<int> list;
  for(int i = 0; i < 5; ++i) list.Add(i+1);

  TEST_EQUAL(list.Size(), 5);

  list.RemoveElement(0);
  TEST_EQUAL(list.Size(), 4);
  TEST_EQUAL(list.Get(0), 1);
  TEST_EQUAL(list.Get(1), 2);
  TEST_EQUAL(list.Get(2), 3);
  TEST_EQUAL(list.Get(3), 4);

  list.RemoveElement(2);
  TEST_EQUAL(list.Size(), 3);
  TEST_EQUAL(list.Get(0), 1);
  TEST_EQUAL(list.Get(1), 3);
  TEST_EQUAL(list.Get(2), 4);

  list.Remove(4);
  TEST_EQUAL(list.Size(), 2);
  TEST_EQUAL(list.Get(0), 1);
  TEST_EQUAL(list.Get(1), 2);

  return EXIT_SUCCESS;
}

int testRemoveElementAssertion(void)
{
  gul::List<int> list;

  TEST_ASSERTION(list.RemoveElemet(0));

  list.add(0);
  list.add(1);

  TEST_ASSERTION(list.RemoveElement(2));
  TEST_ASSERTION(list.RemoveElement(-1));

  return EXIT_SUCCESS;
}

int testClear(void)
{
  gul::List<int> list;
  for(int i = 0; i < 5; ++i) list.Add(i);

  TEST_EQUAL(list.Size(), 5);

  list.Clear();

  TEST_EQUAL(list.Size(), 0);
  TEST_TRUE(list.IsEmpty());

  return EXIT_SUCCESS;
}

int testIndexOf(void)
{
  gul::List<int> list;
  for(int i = 0; i < 5; ++i) list.Add(i+1);

  for(int i = 0; i < 5; ++i)
  {
    TEST_EQUAL(list.IndexOf(i+1), i);
  }

  TEST_EQUAL(list.IndexOf(5), gul::NotFound);
  TEST_EQUAL(list.IndexOf(-1), gul::NotFound);

  return EXIT_SUCCESS;
}

int testContains(void)
{
  gul::List<int> list;
  for(int i = 0; i < 5; ++i) list.Add(i+1);

  for(int i = 0; i < 5; ++i)
  {
    TEST_TRUE(list.Contains(i+1));
  }

  TEST_FALSE(list.Contains(5));
  TEST_FALSE(list.Contains(-1));

  return EXIT_SUCCESS;
}

}

int TestList(const std::string& rTestName)
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
