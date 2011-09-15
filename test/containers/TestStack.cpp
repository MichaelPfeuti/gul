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
#include "Stack.h"

namespace {

int testSizeAndIsEmpty(void)
{
  gul::Stack<int> stack;

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

int testPush(void)
{
  gul::Stack<int> stack;

  stack.Push(0);
  TEST_EQUAL(stack.Size(), 1);
  TEST_EQUAL(stack.Top(), 0)
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

int testTopAssertion(void)
{
  gul::Stack<int> stack;
  TEST_ASSERTION(stack.Top());

  stack.Push(0);
  stack.Top();
  stack.Pop();

  TEST_ASSERTION(stack.Top());

  return EXIT_SUCCESS;
}

int testTop(void)
{
  gul::Stack<int> stack;

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

int testPop(void)
{
  gul::Stack<int> stack;

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

int testPopAssertion(void)
{
  gul::Stack<int> stack;
  TEST_ASSERTION(stack.Pop());

  stack.Push(0);
  stack.Pop();

  TEST_ASSERTION(stack.Pop());

  return EXIT_SUCCESS;
}

int testClear(void)
{
  gul::Stack<int> stack;
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


}

int TestStack(const std::string& rTestName)
{
    if(rTestName == "SizeAndIsEmpty") return testSizeAndIsEmpty();
    if(rTestName == "Push") return testPush();
    if(rTestName == "Pop") return testPop();
    if(rTestName == "PopAssertion") return testPopAssertion();
    if(rTestName == "Top") return testTop();
    if(rTestName == "TopAssertion") return testTopAssertion();
    if(rTestName == "Clear") return testClear();

    TEST_END();
}
