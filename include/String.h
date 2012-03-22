#pragma once
#ifndef _GUL_BASE_STRING_H_
#define _GUL_BASE_STRING_H_
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

#include <3rdParty/pugi/pugixml.hpp>
#include "NonCopyable.h"
#include "XMLSerializable.h"

namespace gul
{

  /**
    *
    */
  class String : private NonCopyable, public XMLSerializable
  {


    public:
      String(void);
      String(const String& rString);
      explicit String(const char*);
      ~String();

    public:
      bool IsEmpty(void) const
      {
        return Size() == 0;
      }
      int Size(void) const
      {
        return size;
      }
      char CharAt(int index) const;

      String Arg(double value) const;
      String Arg(long value) const;
      String Arg(int value) const;
      String Arg(const String& rString) const;

      int Find(const String& rString) const;

      String Replace(const String& rNew, int start, int end) const;
      String Replace(const String& rNew, const String& rSearch) const;

      const char* GetData(void) const
      {
        return pString;
      }

    private:
      virtual void Save(pugi::xml_node& node, bool resetMode) const;
      virtual void* Load(const pugi::xml_node& node, bool resetMode) const;
      friend class XMLSerializable;

    private:
      const char* pString;
      const int size;

      friend String operator+(const String&, const String&);
      friend bool operator!=(const String& rLeft, const String& rRight);
      friend bool operator==(const String& rLeft, const String& rRight);
  };


  String operator+(const String& rLeft, const String& rRight);
  bool operator!=(const String& rLeft, const String& rRight);
  bool operator==(const String& rLeft, const String& rRight);

}

#endif
