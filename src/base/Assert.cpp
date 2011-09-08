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

#include <cstdio>
#include <cstdlib>

namespace gul
{

void AssertTerminal(bool condition, const char* pMessage, int lineNumber, const char* pFileName)
{

  if(!(condition))
  {
    fprintf(stderr, "%s:%d: Assertion failed: %s\n", pFileName, lineNumber, pMessage);
    fflush(stderr);
#ifdef _GUL_TESTING_ENABLED_
    throw ExceptionAssertionViolated();
#else
    exit(EXIT_FAILURE);
#endif
  }
}

void AssertGui(bool condition, const char* pMessage, int lineNumber, const char* pFileName)
{
  //@todo
}

}
