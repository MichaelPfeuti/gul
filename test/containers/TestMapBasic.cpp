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
#include "MapBasic.h"
#include "XMLManager.h"

namespace TestMapBasic
{

  int CopyConstructor(void)
  {
    gul::MapBasic<int, int> map;
    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
    }

    gul::MapBasic<int, int> mapCopy(map);
    for(int i = 0; i < 5; ++i)
    {
      TEST_EQUAL(mapCopy.Get(i), i + 10);
      TEST_TRUE(mapCopy.Contains(i));
    }
    TEST_EQUAL(mapCopy.Size(), map.Size());

    return EXIT_SUCCESS;
  }

  int Assignment(void)
  {
    gul::MapBasic<int, int> map;
    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
    }

    gul::MapBasic<int, int> mapWithElements;
    for(int i = 10; i < 15; ++i)
    {
      map.Add(i, i + 10);
    }

    gul::MapBasic<int, int> mapEmpty;

    mapWithElements = map;
    mapEmpty = map;

    for(int i = 0; i < 5; ++i)
    {
      TEST_EQUAL(mapWithElements.Get(i), i + 10);
      TEST_TRUE(mapWithElements.Contains(i));

      TEST_EQUAL(mapEmpty.Get(i), i + 10);
      TEST_TRUE(mapEmpty.Contains(i));
    }
    TEST_EQUAL(mapWithElements.Size(), map.Size());
    TEST_EQUAL(mapEmpty.Size(), map.Size());

    return EXIT_SUCCESS;
  }

  int SizeAndIsEmpty(void)
  {
    gul::MapBasic<int, int> map;
    TEST_TRUE(map.IsEmpty());
    TEST_EQUAL(map.Size(), 0);

    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
      TEST_FALSE(map.IsEmpty());
      TEST_EQUAL(map.Size(), i + 1);
    }

    for(int i = 0; i < 4; ++i)
    {
      map.Remove(i);
      TEST_FALSE(map.IsEmpty());
      TEST_EQUAL(map.Size(), 4 - i);
    }

    map.Remove(4);
    TEST_TRUE(map.IsEmpty());
    TEST_EQUAL(map.Size(), 0);

    return EXIT_SUCCESS;
  }

  int Add(void)
  {
    gul::MapBasic<int, int> map;
    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
      TEST_EQUAL(map.Get(i), i + 10);
      TEST_TRUE(map.Contains(i));
    }

    map.Remove(4);
    TEST_FALSE(map.Contains(4));

    map.Add(4, 40);
    TEST_EQUAL(map.Get(4), 40);
    TEST_TRUE(map.Contains(4));

    map.Add(4, 41);
    TEST_EQUAL(map.Get(4), 41);
    TEST_TRUE(map.Contains(4));

    return EXIT_SUCCESS;
  }

  int Remove(void)
  {
    gul::MapBasic<int, int> map;
    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
      TEST_EQUAL(map.Get(i), i + 10);
    }

    TEST_EQUAL(map.Size(), 5);
    for(int i = 0; i < 5; ++i)
    {
      map.Remove(i);
      TEST_FALSE(map.Contains(i));
      TEST_EQUAL(map.Size(), 4 - i);
    }

    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
      TEST_EQUAL(map.Get(i), i + 10);
    }
    TEST_EQUAL(map.Size(), 5);

    return EXIT_SUCCESS;
  }

  int RemoveAssertion(void)
  {
    gul::MapBasic<int, int> map;

    TEST_ASSERTION(map.Remove(0));
    map.Add(0, 10);
    map.Remove(0);
    TEST_ASSERTION(map.Remove(0));

    return EXIT_SUCCESS;
  }

  int Clear(void)
  {
    gul::MapBasic<int, int> map;
    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
      TEST_EQUAL(map.Get(i), i + 10);
    }

    TEST_EQUAL(map.Size(), 5);
    map.Clear();
    TEST_EQUAL(map.Size(), 0);

    for(int i = 0; i < 5; ++i)
    {
      TEST_FALSE(map.Contains(i));
    }

    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
      TEST_EQUAL(map.Get(i), i + 10);
    }
    TEST_EQUAL(map.Size(), 5);

    return EXIT_SUCCESS;
  }

  int Contains(void)
  {
    gul::MapBasic<int, int> map;

    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
      TEST_TRUE(map.Contains(i));
    }

    TEST_FALSE(map.Contains(10));
    map.Add(10, 20);
    TEST_TRUE(map.Contains(10));
    map.Add(10, 20);
    TEST_TRUE(map.Contains(10));
    map.Remove(10);
    TEST_FALSE(map.Contains(10));

    return EXIT_SUCCESS;
  }

  int Get(void)
  {
    gul::MapBasic<int, int> map;

    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
      TEST_EQUAL(map.Get(i), i + 10);
    }

    map.Remove(0);
    map.Add(0, 50);
    TEST_EQUAL(map.Get(0), 50);

    return EXIT_SUCCESS;
  }

  int GetAssertion(void)
  {
    gul::MapBasic<int, int> map;

    TEST_ASSERTION(map.Get(0));
    map.Add(0, 10);
    map.Get(0);
    map.Remove(0);
    TEST_ASSERTION(map.Get(0));

    return EXIT_SUCCESS;
  }


  int Iterator(void)
  {
    gul::MapBasic<int, int> map;
    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
      TEST_EQUAL(map.Get(i), i + 10);
      TEST_TRUE(map.Contains(i));
    }

    gul::MapBasic<int, int>::Iterator it = map.GetIterator();
    TEST_TRUE(it.HasNext());
    int i = 0;
    while(it.HasNext())
    {
      gul::MapBasic<int, int>::Pair itPair = it.Next();

      TEST_EQUAL(itPair.GetKey(), it.Get().GetKey());
      TEST_EQUAL(itPair.GetValue(), it.Get().GetValue());
      TEST_TRUE(map.Contains(itPair.GetKey()));
      TEST_EQUAL(itPair.GetValue(), map.Get(itPair.GetKey()));
      ++i;
    }
    TEST_EQUAL(i, map.Size());

    return EXIT_SUCCESS;
  }

  int IteratorConst(void)
  {
    gul::MapBasic<int, int> map;
    for(int i = 0; i < 5; ++i)
    {
      map.Add(i, i + 10);
      TEST_EQUAL(map.Get(i), i + 10);
      TEST_TRUE(map.Contains(i));
    }

    const gul::MapBasic<int, int>& constRef = map;
    const gul::MapBasic<int, int>::Iterator it = constRef.GetIterator();

    TEST_TRUE(it.HasNext());
    int i = 0;
    while(it.HasNext())
    {
      gul::MapBasic<int, int>::Pair itPair = it.Next();

      TEST_EQUAL(itPair.GetKey(), it.Get().GetKey());
      TEST_EQUAL(itPair.GetValue(), it.Get().GetValue());
      TEST_TRUE(map.Contains(itPair.GetKey()));
      TEST_EQUAL(itPair.GetValue(), map.Get(itPair.GetKey()));
      ++i;
    }
    TEST_EQUAL(i, map.Size());

    return EXIT_SUCCESS;

//    gul::ListBasic<int> list;
//    for(int i = 0; i < 5; ++i) list.Add(i + 1);


//    int i = 0;
//    TEST_TRUE(it.HasNext());
//    while(it.HasNext())
//    {
//      const int& itElement = it.Next();

//      TEST_EQUAL(itElement, it.Get());
//      TEST_EQUAL(itElement, constRef.Get(i));
//      ++i;
//    }
//    TEST_EQUAL(i, list.Size());

//    return EXIT_SUCCESS;
    return EXIT_FAILURE;
  }
}

