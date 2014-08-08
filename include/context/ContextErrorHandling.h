#pragma once
#ifndef _GUL_CONTEXT_CONTEXT_ERROR_HANDLING_H_
#define _GUL_CONTEXT_CONTEXT_ERROR_HANDLING_H_
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

#include "gul_export.h"

#include <CL/cl.h>

namespace gul
{
  bool GUL_EXPORT alCheckError(const char* message);
  bool GUL_EXPORT clCheckError(cl_int err);
  bool GUL_EXPORT glCheckError(const char* message);
}

#define GUL_AL_CHECK_ERROR(message) \
  if(!alCheckError(message)) \
  {  \
    return false; \
  }

#define GUL_CL_CHECK_ERROR(function) \
  if(!clCheckError(function)) \
  {  \
    return false; \
  }

#define GUL_GL_CHECK_ERROR(message) \
  if(!glCheckError(message)) \
  {  \
    return false; \
  }


#endif
