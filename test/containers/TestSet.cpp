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
#include "Set.h"

namespace TestSet
{

  int SizeAndIsEmpty(void)
  {
    gul::Set<int> set;
    TEST_EQUAL(set.Size(), 0);
    TEST_TRUE(set.IsEmpty());

    for(int i = 0; i < 10; ++i)
    {
      set.Add(i);
      TEST_EQUAL(set.Size(), i + 1);
      TEST_FALSE(set.IsEmpty());
    }

    set.Add(0);
    set.Add(0);
    set.Add(5);
    TEST_EQUAL(set.Size(), 10);
    TEST_FALSE(set.IsEmpty());

    for(int i = 0; i < 9; ++i)
    {
      set.Remove(i);
    }

    TEST_EQUAL(set.Size(), 1);
    TEST_FALSE(set.IsEmpty());

    set.Remove(9);
    TEST_EQUAL(set.Size(), 0);
    TEST_TRUE(set.IsEmpty());

    return EXIT_SUCCESS;
  }

  int Add(void)
  {
    gul::Set<int> set;
    set.Add(0);
    TEST_EQUAL(set.Size(), 1);
    TEST_TRUE(set.Contains(0));
    TEST_FALSE(set.Contains(1));
    TEST_FALSE(set.Contains(2));

    set.Add(1);
    TEST_EQUAL(set.Size(), 2);
    TEST_TRUE(set.Contains(0));
    TEST_TRUE(set.Contains(1));
    TEST_FALSE(set.Contains(2));

    set.Add(2);
    TEST_EQUAL(set.Size(), 3);
    TEST_TRUE(set.Contains(0));
    TEST_TRUE(set.Contains(1));
    TEST_TRUE(set.Contains(2));

    set.Add(0);
    TEST_EQUAL(set.Size(), 3);
    TEST_TRUE(set.Contains(0));
    TEST_TRUE(set.Contains(1));
    TEST_TRUE(set.Contains(2));

    set.Add(2);
    TEST_EQUAL(set.Size(), 3);
    TEST_TRUE(set.Contains(0));
    TEST_TRUE(set.Contains(1));
    TEST_TRUE(set.Contains(2));

    set.Add(-1);
    TEST_EQUAL(set.Size(), 4);
    TEST_TRUE(set.Contains(0));
    TEST_TRUE(set.Contains(1));
    TEST_TRUE(set.Contains(2));
    TEST_TRUE(set.Contains(-1));

    return EXIT_SUCCESS;
  }

  int Remove(void)
  {
    gul::Set<int> set;
    set.Add(0);
    TEST_EQUAL(set.Size(), 1);
    TEST_TRUE(set.Contains(0));

    set.Remove(0);
    TEST_EQUAL(set.Size(), 0);
    TEST_FALSE(set.Contains(0));

    set.Add(0);
    TEST_EQUAL(set.Size(), 1);
    TEST_TRUE(set.Contains(0));

    set.Add(1);
    set.Add(2);
    TEST_EQUAL(set.Size(), 3);
    TEST_TRUE(set.Contains(0));
    TEST_TRUE(set.Contains(1));
    TEST_TRUE(set.Contains(2));
    TEST_FALSE(set.Contains(3));

    set.Remove(0);
    TEST_EQUAL(set.Size(), 2);
    TEST_FALSE(set.Contains(0));
    TEST_TRUE(set.Contains(1));
    TEST_TRUE(set.Contains(2));

    set.Remove(2);
    TEST_EQUAL(set.Size(), 1);
    TEST_FALSE(set.Contains(0));
    TEST_TRUE(set.Contains(1));
    TEST_FALSE(set.Contains(2));

    set.Remove(1);
    TEST_EQUAL(set.Size(), 0);
    TEST_FALSE(set.Contains(0));
    TEST_FALSE(set.Contains(1));
    TEST_FALSE(set.Contains(2));

    return EXIT_SUCCESS;
  }

  int RemoveAssertion(void)
  {
    gul::Set<int> set;
    TEST_ASSERTION(set.Remove(0));
    set.Add(0);
    set.Remove(0);
    TEST_ASSERTION(set.Remove(0));

    return EXIT_SUCCESS;
  }

  int Clear(void)
  {
    gul::Set<int> set;
    for(int i = 0; i < 10; ++i)
    {
      set.Add(i);
    }

    TEST_EQUAL(set.Size(), 10);
    set.Clear();
    TEST_EQUAL(set.Size(), 0);

    set.Add(0);
    TEST_EQUAL(set.Size(), 1);

    return EXIT_SUCCESS;
  }

  int Contains(void)
  {
    gul::Set<int> set;
    TEST_FALSE(set.Contains(0));

    set.Add(0);
    set.Add(1);

    TEST_TRUE(set.Contains(0));
    TEST_TRUE(set.Contains(1));
    TEST_FALSE(set.Contains(2));

    return EXIT_SUCCESS;
  }

  int Assignment(void)
  {
    gul::Set<int> set;
    for(int i = 0; i < 5; ++i) set.Add(i + 1);

    gul::Set<int> copy;
    for(int i = 0; i < 50; ++i) copy.Add(i + 50);

    TEST_EQUAL(copy.Size(), 50);

    copy = set;
    TEST_EQUAL(copy.Size(), 5);
    for(int i = 0; i < 5; ++i)
    {
      TEST_TRUE(copy.Contains(i + 1));
    }

    return EXIT_SUCCESS;
  }

  int CopyConstructor(void)
  {
    gul::Set<int> set;
    for(int i = 0; i < 5; ++i) set.Add(i + 1);

    gul::Set<int> copy(set);
    TEST_EQUAL(copy.Size(), 5);
    for(int i = 0; i < 5; ++i)
    {
      TEST_TRUE(copy.Contains(i + 1));
    }

    return EXIT_SUCCESS;
  }

  int Traits(void)
  {
    TEST_EQUAL(gul::Traits<gul::Set<gul::String>>::GetName(), gul::String("gul::Set<gul::String>"));
    TEST_EQUAL(gul::Traits<gul::Set<gul::Set<gul::String>>>::GetName(), gul::String("gul::Set<gul::Set<gul::String>>"));
    TEST_EQUAL(gul::Traits<gul::Set<gul::Set<gul::String>*>>::GetName(), gul::String("gul::Set<gul::Set<gul::String>*>"));

    return EXIT_SUCCESS;
  }

  int RTTI(void)
  {
    gul::Set<gul::String*> stringSet;
    TEST_EQUAL(stringSet.GetRTTI().GetName(), gul::Traits<gul::Set<gul::String*>>::GetName());

    return EXIT_SUCCESS;
  }

}
