/***************************************************************************
**
** This file is part of gul (Graphic Utility Library).
**
** Copyright (c) 2011-2012 Michael Pfeuti
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

#include "RGBA.h"
#include "Math.h"

gul::RGBA::RGBA(void)
  : red(0),
    green(0),
    blue(0),
    alpha(0)
{
}

gul::RGBA::RGBA(float r, float g, float b, float a)
  : red(r),
    green(g),
    blue(b),
    alpha(a)
{
}

gul::RGBA::RGBA(float r, float g, float b)
  : red(r),
    green(g),
    blue(b),
    alpha(1.f)
{
}

gul::RGBA::RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
  : red(r/255.f),
    green(g/255.f),
    blue(b/255.f),
    alpha(a/255.f)
{
}

gul::RGBA::RGBA(unsigned char r, unsigned char g, unsigned char b)
  : red(r/255.f),
    green(g/255.f),
    blue(b/255.f),
    alpha(1.f)
{
}

bool gul::RGBA::operator==(const RGBA& other) const
{
  return other.red == red &&
      other.green == green &&
      other.blue == blue &&
      other.alpha == alpha;
}

bool gul::RGBA::operator!=(const RGBA& other) const
{
  return ! operator ==(other);
}

float gul::RGBA::GetRed(void) const
{
  return red;
}

float gul::RGBA::GetGreen(void) const
{
  return green;
}

float gul::RGBA::GetBlue(void) const
{
  return blue;
}

float gul::RGBA::GetAlpha(void) const
{
  return alpha;
}

gul::RGBA& gul::RGBA::operator+=(const RGBA& other)
{
  red   = red   + other.red;
  green = green + other.green;
  blue  = blue  + other.blue;
  alpha = alpha + other.alpha;
  return *this;
}

gul::RGBA& gul::RGBA::operator-=(const RGBA& other)
{
  red   = red   - other.red;
  green = green - other.green;
  blue  = blue  - other.blue;
  alpha = alpha - other.alpha;
  return *this;
}

gul::RGBA gul::RGBA::operator+(const RGBA& other) const
{
  gul::RGBA rgba = *this;
  rgba += other;
  return rgba;
}

gul::RGBA gul::RGBA::operator-(const RGBA& other) const
{
  gul::RGBA rgba = *this;
  rgba -= other;
  return rgba;
}

gul::RGBA gul::absoluteDifference(const gul::RGBA& rFirst, const gul::RGBA& rSecond)
{
  return RGBA(absoluteDifference(rFirst.GetRed(), rSecond.GetRed()),
              absoluteDifference(rFirst.GetGreen(), rSecond.GetGreen()),
              absoluteDifference(rFirst.GetBlue(), rSecond.GetBlue()),
              absoluteDifference(rFirst.GetAlpha(), rSecond.GetAlpha()));
}
