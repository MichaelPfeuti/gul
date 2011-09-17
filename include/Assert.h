#pragma once
#ifndef _GUL_BASE_ASSERT_H_
#define _GUL_BASE_ASSERT_H_
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


#ifndef NDEBUG

#include <cassert>

namespace gul
{
class ExceptionAssertionViolated {};
void AssertException(bool condition, const char* pMessage, int lineNumber, const char* pFileName);
void AssertExit(bool condition, const char* pMessage, int lineNumber, const char* pFileName);
void AssertGui(bool condition, const char* pMessage, int lineNumber, const char* pFileName);

}
#  ifdef _GUL_TESTING_ENABLED_
#define ASSERT(condition) gul::AssertException(condition, "", __LINE__, __FILE__);
#define ASSERT_MSG(condition, msg) gul::AssertException(condition, msg, __LINE__, __FILE__);
#define FAIL(msg) gul::AssertException(false, msg, __LINE__, __FILE__);

#  else
#define ASSERT(condition) gul::AssertExit(condition, "", __LINE__, __FILE__);
#define ASSERT_MSG(condition, msg) gul::AssertExit(condition, msg, __LINE__, __FILE__);
#define FAIL(msg) gul::AssertExit(false, msg, __LINE__, __FILE__);

#  endif
#else
#define ASSERT(condition)
#define ASSERT_MSG(condition, msg)
#define FAIL(msg)

#endif

#endif
