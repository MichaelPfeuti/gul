#pragma once
#ifndef _GUL_BASE_ASSERT_H_
#define _GUL_BASE_ASSERT_H_
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


#if !defined(NDEBUG) || defined(GUL_ASSERTION)

#include "gul_export.h"
#include <cassert>

namespace gul
{
  enum GUL_EXPORT AssertionMode { ASSERT_ABORT, ASSERT_EXCEPTION, ASSERT_GUI };
  class GUL_EXPORT  ExceptionAssertionViolated {};
  GUL_EXPORT void Assert(bool condition, const char* pMessage, int lineNumber, const char* pFileName);
  GUL_EXPORT extern AssertionMode AssertionModeInUse;
}

#define GUL_ASSERT(condition) gul::Assert(condition, "", __LINE__, __FILE__)
#define GUL_ASSERT_MSG(condition, msg) gul::Assert(condition, msg, __LINE__, __FILE__)
#define GUL_FAIL(msg) gul::Assert(false, msg, __LINE__, __FILE__)

#else

#define GUL_ASSERT(condition)
#define GUL_ASSERT_MSG(condition, msg)
#define GUL_FAIL(msg)

#endif

#endif
