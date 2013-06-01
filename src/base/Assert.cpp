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

#include "Assert.h"
#include <cstdio>
#include <cstdlib>
#include "Misc.h"

#if !defined(NDEBUG) || defined(GUL_ASSERTION)

#if defined(GUL_ASSERTION_ABORT)
  gul::AssertionMode gul::AssertionModeInUse = gul::ASSERT_ABORT;
#elif defined(GUL_ASSERTION_EXCEPTION)
  gul::AssertionMode gul::AssertionModeInUse = gul::ASSERT_EXCEPTION;
#elif defined(GUL_ASSERTION_GUI)
  gul::AssertionMode gul::AssertionModeInUse = gul::ASSERT_GUI;
#endif

static void AssertException(bool condition, const char* pMessage, int lineNumber, const char* pFileName)
{

  if(!condition)
  {
    fprintf(stderr, "%s:%d: Assertion failed: %s\n", pFileName, lineNumber, pMessage);
    fflush(stderr);
    throw gul::ExceptionAssertionViolated();
  }
}

static void AssertExit(bool condition, const char* pMessage, int lineNumber, const char* pFileName)
{

  if(!condition)
  {
    fprintf(stderr, "%s:%d: Assertion failed: %s\n", pFileName, lineNumber, pMessage);
    fflush(stderr);
    exit(EXIT_FAILURE);
  }
}

static void AssertGui(bool condition, const char* pMessage, int lineNumber, const char* pFileName)
{
  GUL_UNUSED_VAR(condition);
  GUL_UNUSED_VAR(pMessage);
  GUL_UNUSED_VAR(lineNumber);
  GUL_UNUSED_VAR(pFileName);
  //@todo
}

void gul::Assert(bool condition, const char* pMessage, int lineNumber, const char* pFileName)
{
  switch(AssertionModeInUse)
  {
    case ASSERT_EXCEPTION:
      AssertException(condition, pMessage, lineNumber, pFileName);
      break;
    case ASSERT_GUI:
      AssertGui(condition, pMessage, lineNumber, pFileName);
      break;
    case ASSERT_ABORT:
    default:
      AssertExit(condition, pMessage, lineNumber, pFileName);
      break;
  }
}

#endif
