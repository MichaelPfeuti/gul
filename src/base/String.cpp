/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012 Michael Pfeuti.
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

#include "String.h"
#include "Assert.h"
#include "Misc.h"
#include "RTTI.h"
#include <cstring>
#include <cstdio>
#include <typeinfo>

const gul::RTTI gul::String::RTTI(gul::String("gul::String"));

gul::String::String(void)
  : pString(nullptr),
    size(0)
{
}

gul::String::String(const gul::String& rString)
  : pString(strcpy(new char[rString.Size() + 1], rString.pString)),
    size(rString.Size())
{
}

gul::String::String(const char* pCString)
  : pString(strcpy(new char[strlen(pCString) + 1], pCString)),
    size(strlen(pCString))
{
}

gul::String::~String()
{
  GUL_DELETE_ARRAY(pString);
}

gul::String& gul::String::operator=(const gul::String& other)
{
  if(this != &other)  // protect against invalid self-assignment
  {
    char* newString = new char[other.size + 1];
    strcpy(newString, other.pString);

    GUL_DELETE_ARRAY(this->pString);
    this->pString = newString;
    this->size = other.size;
  }
  // by convention, always return *this
  return *this;
}

char gul::String::CharAt(int index) const
{
  return this->pString[index];
}

gul::String gul::String::Arg(double value) const
{
  int idx = this->Find(String("%"));
  ASSERT_MSG(idx != -1, "% marker could not be found in this string!");

  const int valueLength = 256;
  char pNewString[this->Size() + valueLength];

  sprintf(pNewString, "%.*s%g%s", idx, this->pString, value, this->pString + idx + 1);
  return String(pNewString);
}

gul::String gul::String::Arg(int value) const
{
  int idx = this->Find(String("%"));
  ASSERT_MSG(idx != -1, "% marker could not be found in this string!");

  const int valueLength = 256;
  char pNewString[this->Size() + valueLength];

  sprintf(pNewString, "%.*s%d%s", idx, this->pString, value, this->pString + idx + 1);
  return String(pNewString);
}

gul::String gul::String::Arg(long value) const
{
  int idx = this->Find(String("%"));
  ASSERT_MSG(idx != -1, "% marker could not be found in this string!");

  const int valueLength = 255;
  char pNewString[this->Size() + valueLength];

  sprintf(pNewString, "%.*s%ld%s", idx, this->pString, value, this->pString + idx + 1);
  return String(pNewString);
}

gul::String gul::String::Arg(const gul::String& rString) const
{
  return this->Replace(rString, gul::String("%"));
}

gul::String gul::String::Replace(const gul::String& rNew, int start, int end) const
{
  ASSERT_MSG(0 <= start, "Start must be larger that 0!");
  ASSERT_MSG(start <= end, "Start must be smaller than end!");
  ASSERT_MSG(end < this->Size(), "End must be smaller than the size of the string!");

  // this includes the null byte
  int newSize = start + rNew.Size() + this->Size() - end;

  char pNewString[newSize];
  strncpy(pNewString                      , this->pString         , start);
  strcpy(pNewString + start               , rNew.pString);
  strcpy(pNewString + start + rNew.Size(), this->pString + end + 1);

  return String(pNewString);
}

gul::String gul::String::Replace(const gul::String& rNew, const gul::String& rSearch) const
{
  int idx = Find(rSearch);
  ASSERT_MSG(idx != -1, "String to replace must occur!");

  //@todo: this generates an unnecessary copy
  return this->Replace(rNew, idx, idx + rSearch.Size() - 1);
}

gul::String gul::String::ReplaceBackward(const gul::String& rNew, const gul::String& rSearch) const
{
  int idx = FindBackward(rSearch);
  ASSERT_MSG(idx != -1, "String to replace must occur!");

  //@todo: this generates an unnecessary copy
  return this->Replace(rNew, idx, idx + rSearch.Size() - 1);
}

gul::String gul::String::ReplaceAll(const gul::String& rNew, const gul::String& rSearch) const
{
  int count = Count(rSearch);

  if(count == 0) return *this;

  gul::String* pOld = new gul::String(*this);
  gul::String* pNew = nullptr;
  for(int i = 0; i < count; ++i)
  {
    GUL_DELETE(pNew);
    pNew = new gul::String(pOld->Replace(rNew, rSearch));
    GUL_DELETE(pOld);
    pOld = new gul::String(*pNew);
  }
  gul::String out = *pNew;
  GUL_DELETE(pNew);
  GUL_DELETE(pOld);

  return out;
}

gul::String gul::String::Substring(int start, int end) const
{
  ASSERT_MSG(start >= 0 && start < this->size, "Start index must be positive and smaller than the strings length");
  ASSERT_MSG(end >= 0 && end <= this->size, "End index must be positive and smaller than the strings length");

  char pSubstring[end - start + 1];
  strncpy(pSubstring, this->pString + start, end - start);
  pSubstring[end - start] = '\0';

  return gul::String(pSubstring);
}

int gul::String::Find(const gul::String& rString) const
{
  const char* pSearchPos = strstr(this->pString, rString.pString);
  for(int i = 0; i < this->size; ++i)
  {
    if(this->pString + i == pSearchPos)
      return i;
  }
  // TODO: use constant here;
  return -1;
}

int gul::String::FindBackward(const gul::String& rString) const
{
  const char* pSearchPos = strstr(this->pString, rString.pString);
  const char* pLastValidPos = pSearchPos;
  while(pSearchPos != nullptr)
  {
    pLastValidPos = pSearchPos;
    pSearchPos = strstr(pLastValidPos + 1, rString.pString);
  }

  for(int i = 0; i < this->size; ++i)
  {
    if(this->pString + i == pLastValidPos)
      return i;
  }
  // TODO: use constant here;
  return -1;
}

int gul::String::Count(const String& rString) const
{
  int count = 0;
  const char* pSearchPos = strstr(this->pString, rString.pString);
  while(pSearchPos != nullptr)
  {
    ++count;
    pSearchPos = strstr(pSearchPos + 1, rString.pString);
  }
  return count;
}

gul::String gul::operator+(const gul::String& rLeft, const gul::String& rRight)
{
  char pNewString[rLeft.Size() + rRight.Size() + 1];
  strcpy(pNewString, rLeft.pString);
  strcat(pNewString, rRight.pString);

  return gul::String(pNewString);
}

bool gul::operator!=(const gul::String& rLeft, const gul::String& rRight)
{
  return !operator==(rLeft, rRight);
}

bool gul::operator==(const gul::String& rLeft, const gul::String& rRight)
{
  return rLeft.Size() == rRight.Size() &&
         strcmp(rLeft.pString, rRight.pString) == 0;
}
