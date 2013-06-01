#pragma once
#ifndef _GUL_TOOLS_CTEST_MAIN_H_
#define _GUL_TOOLS_CTEST_MAIN_H_

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

#include <map>
#include <string>
#include <cstdlib>
#include <cstdio>

// see comments in main() to see why we include this
#include "Assert.h"
#include "CTestData.h"

// Function pointer to a testing function
// the argument selects the tests to execute
typedef int (*TestFunction)(void);

// global map that contains all registered testing functions
// Note: here we rely on the STL map because we assume our map
//       implementation might be erroneous.
typedef std::map<std::string, TestFunction> FunctionNameMap;
FunctionNameMap g_testFunctionMap;

// Macro to register a testing function
#define DECLARE_TEST(suite, test) \
  namespace suite { \
    int test(void); \
  }

// Macro to register a testing function
#define REGISTER_TEST(test) \
  g_testFunctionMap[#test] = test;

// Main calls this function to allow testing functions to be registered.
// This means in an implementation of this function there are usually
// only REGISTER_TEST statements
void RegisterTests(void);

int main(int argc, char* argv[])
{
  // We switch the assertion mode to exception to detect
  // assertion with an exception in the tests.
  gul::AssertionModeInUse = gul::ASSERT_EXCEPTION;
  // We clear the previous ouputs so the we do not clutter the memroy.
  gul::CTestData::Clear();

  RegisterTests();

  if(argc == 1)
  {
    fprintf(stderr, "No TestSuite was selected!");
    return EXIT_FAILURE;
  }

  // find test to execute
  int i = 0;
  FunctionNameMap::const_iterator end = g_testFunctionMap.end();
  for(FunctionNameMap::iterator iter = g_testFunctionMap.begin(); iter != end; ++iter)
  {
    FunctionNameMap::value_type entry = *iter;
    if(argc > 1 && entry.first == argv[1])
    {
      TestFunction f = entry.second;
      return f();
    }
    ++i;
  }

  fprintf(stderr, "Test %s is not part of the TestCollection!\n", argv[1]); \
  return EXIT_FAILURE;
}

#endif
