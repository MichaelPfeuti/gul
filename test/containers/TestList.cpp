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
#include "String.h"

namespace TestList
{

  int SizeAndIsEmpty(void)
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

  int Add(void)
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

  int AddIndex(void)
  {
    gul::List<int> list;
    TEST_EQUAL(list.Size(), 0);
    TEST_TRUE(list.IsEmpty());

    list.Add(0, 10);
    TEST_EQUAL(list.Size(), 1);
    TEST_EQUAL(list.Get(0), 0);

    list.Add(1, 1);
    TEST_EQUAL(list.Size(), 2);
    TEST_EQUAL(list.Get(0), 0);
    TEST_EQUAL(list.Get(1), 1);

    list.Add(2, 10);
    TEST_EQUAL(list.Size(), 3);
    TEST_EQUAL(list.Get(0), 0);
    TEST_EQUAL(list.Get(1), 1);
    TEST_EQUAL(list.Get(2), 2);

    list.Add(3, 1);
    TEST_EQUAL(list.Size(), 4);
    TEST_EQUAL(list.Get(0), 0);
    TEST_EQUAL(list.Get(1), 3);
    TEST_EQUAL(list.Get(2), 1);
    TEST_EQUAL(list.Get(3), 2);

    list.Add(4, 0);
    TEST_EQUAL(list.Size(), 5);
    TEST_EQUAL(list.Get(0), 4);
    TEST_EQUAL(list.Get(1), 0);
    TEST_EQUAL(list.Get(2), 3);
    TEST_EQUAL(list.Get(3), 1);
    TEST_EQUAL(list.Get(4), 2);

    return EXIT_SUCCESS;
  }

  int AddIndexAssertion(void)
  {
    gul::List<int> list;
    TEST_ASSERTION(list.Add(5, -1));

    return EXIT_SUCCESS;
  }

  int RemoveIndex(void)
  {
    gul::List<int> list;
    for(int i = 0; i < 5; ++i) list.Add(i + 10);

    TEST_EQUAL(list.Size(), 5);

    list.Remove(0);
    TEST_EQUAL(list.Size(), 4);
    TEST_EQUAL(list.Get(0), 11);
    TEST_EQUAL(list.Get(1), 12);
    TEST_EQUAL(list.Get(2), 13);
    TEST_EQUAL(list.Get(3), 14);

    list.Remove(2);
    TEST_EQUAL(list.Size(), 3);
    TEST_EQUAL(list.Get(0), 11);
    TEST_EQUAL(list.Get(1), 12);
    TEST_EQUAL(list.Get(2), 14);

    list.Remove(2);
    TEST_EQUAL(list.Size(), 2);
    TEST_EQUAL(list.Get(0), 11);
    TEST_EQUAL(list.Get(1), 12);

    return EXIT_SUCCESS;
  }

  int RemoveIndexAssertion(void)
  {
    gul::List<int> list;

    TEST_ASSERTION(list.Remove(0));

    list.Add(0);
    list.Add(1);

    TEST_ASSERTION(list.Remove(2));
    TEST_ASSERTION(list.Remove(-1));

    return EXIT_SUCCESS;
  }

  int RemoveElement(void)
  {
    gul::List<int> list;
    for(int i = 0; i < 5; ++i) list.Add(i + 10);

    TEST_EQUAL(list.Size(), 5);

    list.RemoveElement(10);
    TEST_EQUAL(list.Size(), 4);
    TEST_EQUAL(list.Get(0), 11);
    TEST_EQUAL(list.Get(1), 12);
    TEST_EQUAL(list.Get(2), 13);
    TEST_EQUAL(list.Get(3), 14);

    list.RemoveElement(12);
    TEST_EQUAL(list.Size(), 3);
    TEST_EQUAL(list.Get(0), 11);
    TEST_EQUAL(list.Get(1), 13);
    TEST_EQUAL(list.Get(2), 14);

    list.RemoveElement(14);
    TEST_EQUAL(list.Size(), 2);
    TEST_EQUAL(list.Get(0), 11);
    TEST_EQUAL(list.Get(1), 13);

    return EXIT_SUCCESS;
  }

  int RemoveElementAssertion(void)
  {
    gul::List<int> list;

    TEST_ASSERTION(list.RemoveElement(0));

    list.Add(0);
    list.Add(1);

    TEST_ASSERTION(list.RemoveElement(2));
    TEST_ASSERTION(list.RemoveElement(-1));


    return EXIT_SUCCESS;
  }

  int Clear(void)
  {
    gul::List<int> list;
    for(int i = 0; i < 5; ++i) list.Add(i);

    TEST_EQUAL(list.Size(), 5);

    list.Clear();

    TEST_EQUAL(list.Size(), 0);
    TEST_TRUE(list.IsEmpty());

    return EXIT_SUCCESS;
  }

  int IndexOf(void)
  {
    gul::List<int> list;
    for(int i = 0; i < 5; ++i) list.Add(i + 1);

    for(int i = 0; i < 5; ++i)
    {
      TEST_EQUAL(list.IndexOf(i + 1), i);
    }

    TEST_EQUAL(list.IndexOf(6), gul::NOT_FOUND);
    TEST_EQUAL(list.IndexOf(-1), gul::NOT_FOUND);

    return EXIT_SUCCESS;
  }

  int Contains(void)
  {
    gul::List<int> list;
    for(int i = 0; i < 5; ++i) list.Add(i + 1);

    for(int i = 0; i < 5; ++i)
    {
      TEST_TRUE(list.Contains(i + 1));
    }

    TEST_FALSE(list.Contains(6));
    TEST_FALSE(list.Contains(-1));

    return EXIT_SUCCESS;
  }

  int Assignment(void)
  {
    gul::List<int> list;
    for(int i = 0; i < 5; ++i) list.Add(i + 1);

    gul::List<int> copy;
    for(int i = 0; i < 50; ++i) copy.Add(i + 50);

    TEST_EQUAL(copy.Size(), 50);

    copy = list;
    TEST_EQUAL(copy.Size(), 5);
    for(int i = 0; i < 5; ++i)
    {
      TEST_EQUAL(copy.Get(i), i + 1);
    }

    return EXIT_SUCCESS;
  }

  int CopyConstructor(void)
  {
    gul::List<int> list;
    for(int i = 0; i < 5; ++i) list.Add(i + 1);

    gul::List<int> copy(list);
    TEST_EQUAL(copy.Size(), 5);
    for(int i = 0; i < 5; ++i)
    {
      TEST_EQUAL(copy.Get(i), i + 1);
    }

    return EXIT_SUCCESS;
  }

  int Traits(void)
  {
    TEST_EQUAL(gul::Traits<gul::List<gul::String>>::GetName(), gul::String("gul::List<gul::String>"));
    TEST_EQUAL(gul::Traits<gul::List<gul::List<gul::String>>>::GetName(), gul::String("gul::List<gul::List<gul::String>>"));
    TEST_EQUAL(gul::Traits<gul::List<gul::List<gul::String>*>>::GetName(), gul::String("gul::List<gul::List<gul::String>*>"));

    return EXIT_SUCCESS;
  }

  int RTTI(void)
  {
    //gul::List<gul::String*> stringList;
    //TEST_EQUAL(stringList.GetRTTI().GetName(), gul::Traits<gul::List<gul::String*>>::GetName());

    //gul::List<int> intList;
    //TEST_EQUAL(intList.GetRTTI().GetName(), gul::Traits<gul::List<int>>::GetName());

    return EXIT_FAILURE;
  }

}
