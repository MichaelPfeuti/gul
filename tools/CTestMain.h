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



// This file is used to create TestDriver executables
// These executables are able to register a function pointer to a string name
// in a lookup table.   By including this file, it creates a main function
// that calls RegisterTests() then looks up the function pointer for the test
// specified on the command line.

#include <map>
#include <string>

// Function pointer to a testing function
typedef int (*TestFunction)(void);

// global map that contains all registered testing functions
// Note: here we rely on the STL map because we assume our map
//       implementation might be erroneous.
std::map<std::string, TestFunction> testFunctionMap;

// Macro to register a testing function
#define REGISTER_TEST(test) \
    extern int test(int, char* [] ); \
    testFunctionMap[#test] = test

// Main calls this function to allow testing functions to be registered.
// This means in an implementation of this function there are usually 
// only REGISTER_TEST statements
int RegisterTests(void);

int main(void)
{
  RegisterTests();
  return -1;
}

#endif
