/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2013 Michael Pfeuti.
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
#include "ArrayBasic.h"
#include "XMLManager.h"

namespace TestArrayBasic
{

  int SizeAndIsEmpty(void)
  {
    gul::ArrayBasic<int> array;
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

  int Add(void)
  {
    gul::ArrayBasic<int> array;
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

  int AddIndex(void)
  {
    gul::ArrayBasic<int> array;
    TEST_EQUAL(array.Size(), 0);
    TEST_TRUE(array.IsEmpty());

    array.Add(0, 10);
    TEST_EQUAL(array.Size(), 1);
    TEST_EQUAL(array.Get(0), 0);

    array.Add(1, 1);
    TEST_EQUAL(array.Size(), 2);
    TEST_EQUAL(array.Get(0), 0);
    TEST_EQUAL(array.Get(1), 1);

    array.Add(2, 10);
    TEST_EQUAL(array.Size(), 3);
    TEST_EQUAL(array.Get(0), 0);
    TEST_EQUAL(array.Get(1), 1);
    TEST_EQUAL(array.Get(2), 2);

    array.Add(3, 1);
    TEST_EQUAL(array.Size(), 4);
    TEST_EQUAL(array.Get(0), 0);
    TEST_EQUAL(array.Get(1), 3);
    TEST_EQUAL(array.Get(2), 1);
    TEST_EQUAL(array.Get(3), 2);

    array.Add(4, 0);
    TEST_EQUAL(array.Size(), 5);
    TEST_EQUAL(array.Get(0), 4);
    TEST_EQUAL(array.Get(1), 0);
    TEST_EQUAL(array.Get(2), 3);
    TEST_EQUAL(array.Get(3), 1);
    TEST_EQUAL(array.Get(4), 2);

    return EXIT_SUCCESS;
  }

  int AddIndexAssertion(void)
  {
    gul::ArrayBasic<int> array;
    TEST_ASSERTION(array.Add(5, -1));

    return EXIT_SUCCESS;
  }

  int RemoveIndex(void)
  {
    gul::ArrayBasic<int> array;
    for(int i = 0; i < 5; ++i) array.Add(i + 10);

    TEST_EQUAL(array.Size(), 5);

    array.Remove(0);
    TEST_EQUAL(array.Size(), 4);
    TEST_EQUAL(array.Get(0), 11);
    TEST_EQUAL(array.Get(1), 12);
    TEST_EQUAL(array.Get(2), 13);
    TEST_EQUAL(array.Get(3), 14);

    array.Remove(2);
    TEST_EQUAL(array.Size(), 3);
    TEST_EQUAL(array.Get(0), 11);
    TEST_EQUAL(array.Get(1), 12);
    TEST_EQUAL(array.Get(2), 14);

    array.Remove(2);
    TEST_EQUAL(array.Size(), 2);
    TEST_EQUAL(array.Get(0), 11);
    TEST_EQUAL(array.Get(1), 12);

    return EXIT_SUCCESS;
  }

  int RemoveIndexAssertion(void)
  {
    gul::ArrayBasic<int> array;

    TEST_ASSERTION(array.Remove(0));

    array.Add(0);
    array.Add(1);

    TEST_ASSERTION(array.Remove(2));
    TEST_ASSERTION(array.Remove(-1));

    return EXIT_SUCCESS;
  }

  int RemoveElement(void)
  {
    gul::ArrayBasic<int> array;
    for(int i = 0; i < 5; ++i) array.Add(i + 10);

    TEST_EQUAL(array.Size(), 5);

    array.RemoveElement(10);
    TEST_EQUAL(array.Size(), 4);
    TEST_EQUAL(array.Get(0), 11);
    TEST_EQUAL(array.Get(1), 12);
    TEST_EQUAL(array.Get(2), 13);
    TEST_EQUAL(array.Get(3), 14);

    array.RemoveElement(12);
    TEST_EQUAL(array.Size(), 3);
    TEST_EQUAL(array.Get(0), 11);
    TEST_EQUAL(array.Get(1), 13);
    TEST_EQUAL(array.Get(2), 14);

    array.RemoveElement(14);
    TEST_EQUAL(array.Size(), 2);
    TEST_EQUAL(array.Get(0), 11);
    TEST_EQUAL(array.Get(1), 13);

    return EXIT_SUCCESS;
  }

  int RemoveElementAssertion(void)
  {
    gul::ArrayBasic<int> array;

    TEST_ASSERTION(array.RemoveElement(0));

    array.Add(0);
    array.Add(1);

    TEST_ASSERTION(array.RemoveElement(2));
    TEST_ASSERTION(array.RemoveElement(-1));

    return EXIT_SUCCESS;
  }

  int Clear(void)
  {
    gul::ArrayBasic<int> array;
    for(int i = 0; i < 5; ++i) array.Add(i);

    TEST_EQUAL(array.Size(), 5);

    array.Clear();

    TEST_EQUAL(array.Size(), 0);
    TEST_TRUE(array.IsEmpty());

    return EXIT_SUCCESS;
  }

  int IndexOf(void)
  {
    gul::ArrayBasic<int> array;
    for(int i = 0; i < 5; ++i) array.Add(i + 1);

    for(int i = 0; i < 5; ++i)
    {
      TEST_EQUAL(array.IndexOf(i + 1), i);
    }

    TEST_EQUAL(array.IndexOf(6), gul::NOT_FOUND);
    TEST_EQUAL(array.IndexOf(-1), gul::NOT_FOUND);

    return EXIT_SUCCESS;
  }

  int Contains(void)
  {
    gul::ArrayBasic<int> array;
    for(int i = 0; i < 5; ++i) array.Add(i + 1);

    for(int i = 0; i < 5; ++i)
    {
      TEST_TRUE(array.Contains(i + 1));
    }

    TEST_FALSE(array.Contains(6));
    TEST_FALSE(array.Contains(-1));

    return EXIT_SUCCESS;
  }

  int Assignment(void)
  {
    gul::ArrayBasic<int> array;
    for(int i = 0; i < 5; ++i) array.Add(i + 1);

    gul::ArrayBasic<int> copy;
    for(int i = 0; i < 50; ++i) copy.Add(i + 50);

    TEST_EQUAL(copy.Size(), 50);

    copy = array;
    TEST_EQUAL(copy.Size(), 5);
    for(int i = 0; i < 5; ++i)
    {
      TEST_EQUAL(copy.Get(i), i + 1);
    }

    return EXIT_SUCCESS;
  }

  int CopyConstructor(void)
  {
    gul::ArrayBasic<int> array;
    for(int i = 0; i < 5; ++i) array.Add(i + 1);

    gul::ArrayBasic<int> copy(array);
    TEST_EQUAL(copy.Size(), 5);
    for(int i = 0; i < 5; ++i)
    {
      TEST_EQUAL(copy.Get(i), i + 1);
    }

    return EXIT_SUCCESS;
  }

  int Iterator(void)
  {
    gul::ArrayBasic<int> list;
    for(int i = 0; i < 5; ++i) list.Add(i + 1);

    gul::ArrayBasic<int>::Iterator it = list.GetIterator();
    int i = 0;
    TEST_TRUE(it.HasNext());
    while(it.HasNext())
    {
      int& itElement = it.Next();

      TEST_EQUAL(itElement, it.Get());
      TEST_EQUAL(itElement, list.Get(i));
      ++i;
    }
    TEST_EQUAL(i, list.Size());

    return EXIT_SUCCESS;
  }

  int IteratorConst(void)
  {
    gul::ArrayBasic<int> list;
    for(int i = 0; i < 5; ++i) list.Add(i + 1);

    const gul::ArrayBasic<int>& constRef = list;
    const gul::ArrayBasic<int>::Iterator it = constRef.GetIterator();
    int i = 0;
    TEST_TRUE(it.HasNext());
    while(it.HasNext())
    {
      const int& itElement = it.Next();

      TEST_EQUAL(itElement, it.Get());
      TEST_EQUAL(itElement, constRef.Get(i));
      ++i;
    }
    TEST_EQUAL(i, list.Size());

    return EXIT_SUCCESS;
  }

}
