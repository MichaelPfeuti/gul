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


namespace gul
{

/**
  *
  */
class String
{
public:
  String();
  String(const char*);
  ~String();

  gul::String& operator+=(const gul::String& rString);
};

}

/**
  * Concatenates two Strings
  *
  * For explanation of the implementations see More Effective C++ Item 22
  * by Scott Meyers.
  */
gul::String operator+(const gul::String& rLeft, const gul::String& rRight)
{
  return gul::String(rLeft) += rRight;
}


#endif
