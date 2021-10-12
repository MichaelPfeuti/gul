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
#include "StackBasic.h"
#include "XMLManager.h"

namespace TestStackBasic
{

  int SizeAndIsEmpty(void)
  {
    gul::StackBasic<int> stack;

    TEST_EQUAL(stack.Size(), 0);
    TEST_TRUE(stack.IsEmpty());
    stack.Push(0);
    TEST_EQUAL(stack.Size(), 1);
    TEST_FALSE(stack.IsEmpty());
    stack.Push(1);
    TEST_EQUAL(stack.Size(), 2);
    TEST_FALSE(stack.IsEmpty());
    stack.Push(2);
    TEST_EQUAL(stack.Size(), 3);
    TEST_FALSE(stack.IsEmpty());

    stack.Top();
    TEST_EQUAL(stack.Size(), 3);
    TEST_FALSE(stack.IsEmpty());

    stack.Pop();
    TEST_EQUAL(stack.Size(), 2);
    TEST_FALSE(stack.IsEmpty());
    stack.Pop();
    TEST_EQUAL(stack.Size(), 1);
    TEST_FALSE(stack.IsEmpty());
    stack.Pop();
    TEST_EQUAL(stack.Size(), 0);
    TEST_TRUE(stack.IsEmpty());


    return EXIT_SUCCESS;
  }

  int Push(void)
  {
    gul::StackBasic<int> stack;

    stack.Push(0);
    TEST_EQUAL(stack.Size(), 1);
    TEST_EQUAL(stack.Top(), 0);
    stack.Push(1);
    TEST_EQUAL(stack.Size(), 2);
    TEST_EQUAL(stack.Top(), 1);
    stack.Push(2);
    TEST_EQUAL(stack.Size(), 3);
    TEST_EQUAL(stack.Top(), 2);

    stack.Pop();
    TEST_EQUAL(stack.Top(), 1);
    stack.Pop();
    TEST_EQUAL(stack.Top(), 0);

    return EXIT_SUCCESS;
  }

  int TopAssertion(void)
  {
    gul::StackBasic<int> stack;
    TEST_ASSERTION(stack.Top());

    stack.Push(0);
    stack.Top();
    stack.Pop();

    TEST_ASSERTION(stack.Top());

    return EXIT_SUCCESS;
  }

  int Top(void)
  {
    gul::StackBasic<int> stack;

    stack.Push(0);
    TEST_EQUAL(stack.Top(), 0);
    stack.Push(1);
    TEST_EQUAL(stack.Top(), 1);
    stack.Push(2);
    TEST_EQUAL(stack.Top(), 2);
    stack.Push(3);
    TEST_EQUAL(stack.Top(), 3);

    stack.Pop();
    TEST_EQUAL(stack.Top(), 2);
    stack.Pop();
    TEST_EQUAL(stack.Top(), 1);
    stack.Pop();
    TEST_EQUAL(stack.Top(), 0);

    return EXIT_SUCCESS;
  }

  int Pop(void)
  {
    gul::StackBasic<int> stack;

    stack.Push(0);
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    TEST_EQUAL(stack.Pop(), 3);
    TEST_EQUAL(stack.Size(), 3);
    TEST_EQUAL(stack.Pop(), 2);
    TEST_EQUAL(stack.Size(), 2);
    TEST_EQUAL(stack.Pop(), 1);
    TEST_EQUAL(stack.Size(), 1);
    TEST_EQUAL(stack.Pop(), 0);
    TEST_EQUAL(stack.Size(), 0);

    return EXIT_SUCCESS;
  }

  int PopAssertion(void)
  {
    gul::StackBasic<int> stack;
    TEST_ASSERTION(stack.Pop());

    stack.Push(0);
    stack.Pop();

    TEST_ASSERTION(stack.Pop());

    return EXIT_SUCCESS;
  }

  int Clear(void)
  {
    gul::StackBasic<int> stack;
    stack.Push(0);
    stack.Push(1);
    stack.Push(2);

    TEST_EQUAL(stack.Size(), 3);
    TEST_FALSE(stack.IsEmpty());
    stack.Clear();
    TEST_EQUAL(stack.Size(), 0);
    TEST_TRUE(stack.IsEmpty());

    return EXIT_SUCCESS;
  }

  int Assignment(void)
  {
    gul::StackBasic<int> stack;
    for(int i = 0; i < 5; ++i) stack.Push(i + 1);

    gul::StackBasic<int> copy;
    for(int i = 0; i < 50; ++i) copy.Push(i + 50);

    TEST_EQUAL(copy.Size(), 50);

    copy = stack;
    TEST_EQUAL(copy.Size(), 5);
    for(int i = 5; i > 0; --i)
    {
      TEST_EQUAL(copy.Pop(), i);
    }

    return EXIT_SUCCESS;
  }

  int CopyConstructor(void)
  {
    gul::StackBasic<int> stack;
    for(int i = 0; i < 5; ++i) stack.Push(i + 1);

    gul::StackBasic<int> copy(stack);
    TEST_EQUAL(copy.Size(), 5);
    for(int i = 5; i > 0; --i)
    {
      TEST_EQUAL(copy.Pop(), i);
    }

    return EXIT_SUCCESS;
  }

  int Contains(void)
  {
    gul::StackBasic<int> stack;
    for(int i = 0; i < 5; ++i) stack.Push(i + 1);
    for(int i = 0; i < 5; ++i) TEST_TRUE(stack.Contains(i + 1));

    stack.Pop();
    for(int i = 0; i < 4; ++i) TEST_TRUE(stack.Contains(i + 1));
    TEST_FALSE(stack.Contains(5));

    stack.Push(5);
    TEST_TRUE(stack.Contains(5));

    for(int i = 0; i < 5; ++i) stack.Pop();
    for(int i = 0; i < 5; ++i) TEST_FALSE(stack.Contains(i + 1));

    return EXIT_SUCCESS;
  }

  int Iterator(void)
  {
    gul::StackBasic<int> stack;
    for(int i = 0; i < 5; ++i) stack.Push(i + 1);

    gul::StackBasic<int>::Iterator it = stack.GetIterator();
    TEST_TRUE(it.HasNext());
    while(it.HasNext())
    {
      int& itElement = it.Next();

      TEST_EQUAL(itElement, it.Get());
      TEST_EQUAL(itElement, stack.Pop());
    }
    TEST_EQUAL(0, stack.Size());

    return EXIT_SUCCESS;
  }

  int IteratorConst(void)
  {
    gul::StackBasic<int> stack;
    for(int i = 0; i < 5; ++i) stack.Push(i + 1);

    const gul::StackBasic<int>& constRef = stack;
    const gul::StackBasic<int>::Iterator it = constRef.GetIterator();
    TEST_TRUE(it.HasNext());
    while(it.HasNext())
    {
      const int& itElement = it.Next();

      TEST_EQUAL(itElement, it.Get());
      TEST_EQUAL(itElement, stack.Pop());
    }
    TEST_EQUAL(0, stack.Size());

    return EXIT_SUCCESS;
  }

}
