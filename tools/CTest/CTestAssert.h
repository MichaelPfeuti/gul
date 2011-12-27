#pragma once
#ifndef _GUL_TOOLS_CTEST_ASSERT_H_
#define _GUL_TOOLS_CTEST_ASSERT_H_

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

#include <cstdlib>
#include <cstdio>
#include <string>

#define TEST_ASSERTION(test) \
  try { \
    test; \
    fprintf(stderr, "Test in file %s on line %d failed!\n", __FILE__, __LINE__); \
    return EXIT_FAILURE; \
  } \
  catch(gul::ExceptionAssertionViolated& ex) {}

#define TEST_EQUAL(test, groundTruth) \
  if(test != groundTruth) \
  { \
    fprintf(stderr, "Test in file %s on line %d failed!\n", __FILE__, __LINE__); \
    return EXIT_FAILURE; \
  }


#define TEST_NOT_EQUAL(test, groundTruth) \
  if(test == groundTruth) \
  { \
    fprintf(stderr, "Test in file %s on line %d failed!\n", __FILE__, __LINE__); \
    return EXIT_FAILURE; \
  }

#define TEST_TRUE(test) \
  if(!test) \
  { \
    fprintf(stderr, "Test in file %s on line %d failed!\n", __FILE__, __LINE__); \
    return EXIT_FAILURE; \
  }

#define TEST_FALSE(test) \
  if(test) \
  { \
    fprintf(stderr, "Test in file %s on line %d failed!\n", __FILE__, __LINE__); \
    return EXIT_FAILURE; \
  }

#define TEST_NULL(test) \
  if(test == nullptr) \
  { \
    fprintf(stderr, "Test in file %s on line %d failed!\n", __FILE__, __LINE__); \
    return EXIT_FAILURE; \
  }

#define TEST_NOT_NULL(test) \
  if(test == nullptr) \
  { \
    fprintf(stderr, "Test in file %s on line %d failed!\n", __FILE__, __LINE__); \
    return EXIT_FAILURE; \
  }

#endif
