#pragma once
#ifndef _GUL_BASE_LOG_H_
#define _GUL_BASE_LOG_H_
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
#include "String.h"

#if defined(GUL_LOGGING)

namespace gul
{
  enum GUL_EXPORT LoggingMode { LOG_FILE,
                                LOG_CLI,
                                LOG_GUI };
  enum GUL_EXPORT LoggingLevel { LOG_DEBUG = 0,
                                 LOG_INFO,
                                 LOG_WARNING,
                                 LOG_ERROR };

  GUL_EXPORT void Log(const int level, const char * format, ...);

  GUL_EXPORT extern LoggingMode  LoggingModeInUse;
  GUL_EXPORT extern LoggingLevel LoggingLevelInUse;
}

#define GUL_LOG_DEBUG(msg, ...)   gul::Log(LOG_DEBUG,   "%s:%d DEBUG: " msg "\n", __FILE__, __LINE__, __VA_ARGS__)
#define GUL_LOG_INFO(msg, ...)    gul::Log(LOG_INFO,    "%s:%d INFO: " msg "\n", __FILE__, __LINE__, __VA_ARGS__)
#define GUL_LOG_WARNING(msg, ...) gul::Log(LOG_WARNING, "%s:%d WARNING: " msg "\n", __FILE__, __LINE__, __VA_ARGS__)
#define GUL_LOG_ERROR(msg, ...)   gul::Log(LOG_ERROR,   "%s:%d ERROR: " msg "\n", __FILE__, __LINE__, __VA_ARGS__)

#else

#define GUL_LOG_DEBUG(msg, ...)
#define GUL_LOG_INFO(msg, ...)
#define GUL_LOG_WARNING(msg, ...)
#define GUL_LOG_ERROR(msg, ...)

#endif

#endif
