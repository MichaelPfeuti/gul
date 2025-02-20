#pragma once
#ifndef _GUL_BASE_STRING_H_
#define _GUL_BASE_STRING_H_
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

#include "gul_export.h"

namespace gul
{
  class RTTI;
}

namespace gul
{

  /**
    *
    */
  class GUL_EXPORT String
  {
    private:
      static const gul::RTTI RTTI;
    public:
      virtual const gul::RTTI& GetRTTI(void) const
      {
        return String::RTTI;
      }

    public:
      String(void);
      String(const String& rString);
      String(const char*);
      virtual ~String();
      String& operator=(const String& other);

    public:
      bool IsEmpty(void) const
      {
        return Size() == 0;
      }
      int Size(void) const
      {
        return m_size;
      }
      char CharAt(int index) const;

      String Arg(bool value) const;
      String Arg(double value, int precision = 6) const;
      String Arg(long value) const;
      String Arg(int value) const;
      String Arg(const String& rString) const;

      int Find(const String& rString) const;
      int FindBackward(const String& rString) const;

      String Replace(const String& rNew, int start, int end) const;
      String Replace(const String& rNew, const String& rSearch) const;
      String ReplaceAll(const String& rNew, const String& rSearch) const;
      String ReplaceBackward(const String& rNew, const String& rSearch) const;

      String Substring(int start, int end) const;

      int Count(const String& rString) const;

      String LowerCase(void) const;

      const char* GetData(void) const
      {
        return m_pString;
      }

      long ToLong(void) const;
      double ToDouble(void) const;
      bool ToBool(void) const;

    private:
      const char* m_pString;
      int m_size;

      friend String operator+(const String&, const String&);
      friend bool operator!=(const String& rLeft, const String& rRight);
      friend bool operator==(const String& rLeft, const String& rRight);
  };


  GUL_EXPORT String operator+(const String& rLeft, const String& rRight);
  GUL_EXPORT bool operator!=(const String& rLeft, const String& rRight);
  GUL_EXPORT bool operator==(const String& rLeft, const String& rRight);

}

#endif
