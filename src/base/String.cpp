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
#include "Assert.h"
#include "Misc.h"
#include <cstring>

#include "memleak.h"

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

char gul::String::CharAt(int index) const
{
    return this->pString[index];
}

String String::Arg(float value) const
{
  return String("");
}

String String::Arg(double value) const
{
  return String("");
}

String String::Arg(int value) const
{
  return String("");
}

String String::Arg(long value) const
{
  return String("");
}

String String::Arg(const String& rString) const
{
  return String("");
}

String String::Replace(const String& rNew, int start, int end) const
{
  ASSERT_MSG(0 <= start, "Start must be larger that 0!");
  ASSERT_MSG(start < end, "Start must be smaller than end!");
  ASSERT_MSG(end <= this->Size(), "End must be smalles that the size of the string!");

  int size = start + rNew.Size() + this->Size() - end;

  char pNewString[size];
  strncpy(pNewString                      , this->pString         , start);
  strcpy(pNewString + start               , rNew.pString);
  strncpy(pNewString + start + rNew.Size(), this->pString + end+1 , this->Size() - end);

  return String(pNewString);
}

String String::Replace(const String& rNew, const String& rSearch) const
{
  const char* pSearchPos = strstr(this->pString, rSearch.pString);

  ASSERT_MSG(pSearchPos != nullptr, "String to replace must occur!");

  int idx = 0;
  while(pSearchPos != this->pString + idx) ++idx;

  //@todo: this generates an unnecessary copy
  return this->Replace(rNew, idx, idx+rSearch.Size()-1);
}

String operator+(const String& rLeft, const String& rRight)
{
  char pNewString[rLeft.Size() + rRight.Size()];
  strcpy(pNewString, rLeft.pString);
  strcat(pNewString, rRight.pString);

  return String(pNewString);
}

bool operator!=(const String& rLeft, const String& rRight)
{
  return !operator==(rLeft, rRight);
}

bool operator==(const String& rLeft, const String& rRight)
{
  return rLeft.Size() == rRight.Size() &&
         strcmp(rLeft.pString, rRight.pString) == 0;
}

}
