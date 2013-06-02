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

#include "Log.h"
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include "Misc.h"

#if defined(GUL_LOGGING)

#if defined(GUL_LOGGING_FILE)
  gul::LoggingMode gul::LoggingModeInUse = gul::LOG_FILE;
#elif defined(GUL_LOGGING_CLI)
  gul::LoggingMode gul::LoggingModeInUse = gul::LOG_CLI;
#elif defined(GUL_LOGGING_GUI)
  gul::LoggingMode gul::LoggingModeInUse = gul::LOG_GUI;
#endif

#if defined(GUL_LOGGING_DEBUG)
  gul::LoggingLevel gul::LoggingLevelInUse = gul::LOG_DEBUG;
#elif defined(GUL_LOGGING_INFO)
  gul::LoggingLevel gul::LoggingLevelInUse = gul::LOG_INFO;
#elif defined(GUL_LOGGING_WARNING)
  gul::LoggingLevel gul::LoggingLevelInUse = gul::LOG_WARNING;
#elif defined(GUL_LOGGING_ERROR)
  gul::LoggingLevel gul::LoggingLevelInUse = gul::LOG_ERROR;
#endif

static const char* LOG_FMT[] = { "%s:%d DEBUG: ",
                                 "%s:%d INFO: ",
                                 "%s:%d WARNING: ",
                                 "%s:%d ERROR: "};

static void LogGui(const int, const char *, ...)
{
  // TODO: implement log gui
}

static FILE* logfile = nullptr;

static void CloseLogFile(void)
{
  if(logfile != nullptr)
  {
    fclose(logfile);
  }
}

static void LogFile(const int level, const char* file, int line, const char * format, va_list& args)
{
  if(logfile == nullptr)
  {
    logfile = fopen("gulLog.txt", "w");
    atexit(CloseLogFile);
  }

  fprintf(logfile, LOG_FMT[level], file, line);
  vfprintf(logfile, format, args);
  fprintf(logfile, "\n");
  if(level >= gul::LoggingLevelInUse && level >= gul::LOG_WARNING)
    fflush(logfile);
}

static void LogCli(const int level, const char* file, int line, const char * format, va_list& args)
{
  if(level >= gul::LoggingLevelInUse && level >= gul::LOG_WARNING)
  {
    fprintf(stderr, LOG_FMT[level], file, line);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
  }
  else if(level >= gul::LoggingLevelInUse)
  {
    fprintf(stdout, LOG_FMT[level], file, line);
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");
  }
}

void gul::Log(const int level, const char* file, int line, ...)
{
  va_list args;
  va_start(args, line);
  const char* format = va_arg(args, const char*);
  switch(LoggingModeInUse)
  {
    case LOG_FILE:
      LogFile(level, file, line, format, args);
      break;
    case LOG_GUI:
      LogGui(level, file, line, format, args);
      break;
    case LOG_CLI:
    default:
      LogCli(level, file, line, format, args);
      break;
  }
  va_end(args);
}

#endif
