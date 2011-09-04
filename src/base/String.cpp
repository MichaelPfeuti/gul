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

#include "String.h"
#include "Misc.h"
#include <cstring>

namespace gul
{

String::String(void)
  : pString(nullptr),
    size(0)
{
}

String::String(const String& rString)
  : pString(strcpy(new char[rString.Size()], rString.pString)),
    size(rString.Size())
{
}

String::String(const char* pCString)
  : pString(strcpy(new char[strlen(pCString)], pCString)),
    size(strlen(pCString))
{
}

String::~String()
{
  GUL_DELETE_ARRAY(pString);
}


String operator+(const String& rLeft, const String& rRight)
{
  char* pString = new char[rLeft.Size() + rRight.Size()];
  strcpy(pString, rLeft.pString);
  strcat(pString, rRight.pString);

  return String(pString);
}

bool operator!=(const String& rLeft, const String& rRight)
{
  return !operator==(rLeft, rRight);
}

bool operator==(const String& rLeft, const String& rRight)
{
  return strcmp(rLeft.pString, rRight.pString) == 0;
}

}
